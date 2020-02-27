#include <stdio.h>
#include <SPI.h> 
#include <stdint.h>

#define RED_DATA 1
#define BLUE_DATA 0
#define GREEN_DATA 2
#define MSGSIZE 17

const int CE = 10; 
const int SCROLL_DELAY = 300;
const int REFRESH_DELAY = 0;
const uint8_t letter[][8] = {
{0, 124, 126, 11, 11, 126, 124, 0 },
{0, 54, 127, 73, 73, 127, 127, 0 },
{0, 34, 99, 65, 65, 127, 62, 0 },
{0, 28, 62, 99, 65, 127, 127, 0},
{0, 65, 65, 73, 73, 127, 127, 0},
{0, 1, 1, 9, 9, 127, 127, 0},
{0, 58, 123, 73, 65, 127, 62, 0},
{0, 127, 127, 8, 8, 127, 127, 0},
{0, 0, 65, 127, 127, 65, 0, 0},
{0, 1, 63, 127, 65, 96, 32, 0},
{0, 65, 99, 54, 28, 127, 127, 0},
{0, 64, 64, 64, 64, 127, 127, 0},
{0, 127, 127, 6, 12, 6, 127, 127},
{0, 127, 127, 28, 14, 127, 127, 0},
{0, 62, 127, 65, 65, 127, 62, 0},
{0, 6, 15, 9, 9, 127, 127, 0},
{0, 94, 127, 97, 33, 63, 30, 0},
{0, 70, 111, 57, 25, 127, 127, 0},
{0, 50, 123, 73, 73, 111, 38, 0},
{0, 1, 1, 127, 127, 1, 1, 0},
{0, 63, 127, 64, 64, 127, 63, 0},
{0, 31, 63, 96, 96, 63, 31, 0},
{0, 127, 127, 48, 24, 48, 127, 127},
{0, 99, 119, 28, 28, 119, 99, 0},
{0, 7, 15, 120, 120, 15, 7, 0},
{0, 67, 71, 77, 89, 113, 97, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 79, 79, 0, 0, 0},
{0, 7, 7, 0, 0, 7, 7, 0},
{20, 127, 127, 20, 20, 127, 127, 20},
{0, 18, 58, 107, 107, 46, 36, 0},
{0, 99, 102, 12, 24, 51, 99, 0},
{80, 114, 119, 77, 77, 127, 50},
{0, 1, 3, 6, 4, 0, 0, 0},
{0, 0, 65, 99, 62, 28, 0, 0},
{0, 0, 28, 62, 99, 65, 0, 0},
{0, 62, 127, 69, 73, 127, 62, 0},
{0, 64, 64, 127, 127, 68, 64, 0},
{0, 70, 79, 73, 81, 115, 98, 0},
{0, 54, 127, 73, 73, 99, 34, 0},
{16, 127, 127, 22, 20,24, 24, 0},
{0, 57, 125, 69, 69, 103, 39, 0},
{0, 50, 123, 73, 73, 127, 62, 0},
{0, 3, 7, 125, 121, 3, 3, 0},
{0, 54, 127, 73, 73, 127, 54, 0},
{0, 62, 127, 73, 73, 111, 38, 0},
{0, 0, 36, 36, 0, 0, 0, 0},
{0, 0, 100, 228, 128, 0, 0, 0},
{0, 6, 15, 89, 81, 3, 2, 0},
{0, 0, 0, 96, 96, 0, 0, 0},
{0, 0, 0, 96, 224, 128, 0, 0}
};
// A-Z, space, !, ", #, $, %, & (32), ', ( (34), ) (35),
// 0 (36), 1, 2, ..., 9 (45)
// : (46), ; (47), ? (48), .(49), ,(50)

static uint8_t data[8] = {0x0,0x0,0x0,0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t message[17] = {0,17,3,20,8,13,14,26,15,17,14,26,12,8,13,8,26};

void setup() {
  // put your setup code here, to run once:
  pinMode(CE, OUTPUT);                          //initialized the pin's mode.
  SPI.begin();                                              // start spi function
}

void loop() {
    // loop trhough all letters
    for (int ltr=0;ltr<MSGSIZE;ltr++) {
      // scroll current letter and append following
      for (int pos=0;pos<8;pos++) {
        for (int rep=0;rep<SCROLL_DELAY;rep++) {
          // calc followup letter index
          int nxLtr = (ltr+1)%MSGSIZE;
          for (int j=0;j<8;j++) {
            if (j < pos) {
              data[BLUE_DATA] = ~letter[message[nxLtr]][8-pos+j];
              data[GREEN_DATA] = 255;
              data[RED_DATA] = 255;
            } else {
              data[BLUE_DATA] = ~letter[message[ltr]][j-pos];
              data[GREEN_DATA] = 255;
              data[RED_DATA] = 255;
            }
            data[3] = 0x01 << j ;
            digitalWrite(CE, LOW);
            SPI.transfer(data[GREEN_DATA]); // pos 1: red
            SPI.transfer(data[BLUE_DATA]); // pos 2: blue
            SPI.transfer(data[RED_DATA]); // pos 3: green
            SPI.transfer(data[3]);
            digitalWrite(CE, HIGH);              // send data to SPI channel 0, and the length of the data
            delay(REFRESH_DELAY);
          };
        };
      };
    };
}
