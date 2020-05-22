#include <stdio.h>
#include <SPI.h> 
#include <stdint.h>
#include <string.h>

#define RED_DATA 0
#define GREEN_DATA 1
#define BLUE_DATA 2

const int CE = 10; 
const int SCROLL_DELAY = 300;
const int REFRESH_DELAY = 0;
const uint8_t letter[][8] = {
{0, 124, 126, 11, 11, 126, 124, 0 }, // A
{0, 54, 127, 73, 73, 127, 127, 0 }, // B
{0, 34, 99, 65, 65, 127, 62, 0 }, // C
{0, 28, 62, 99, 65, 127, 127, 0}, // D
{0, 65, 65, 73, 73, 127, 127, 0}, // E
{0, 1, 1, 9, 9, 127, 127, 0}, // F
{0, 58, 123, 73, 65, 127, 62, 0}, // G
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
{0, 0, 0, 96, 224, 128, 0, 0},
{0, 8, 8, 62,62, 8, 8, 0},
{8, 42, 62, 28, 28, 62, 42,8},
{0, 8, 8, 8, 8, 8, 8, 0},
{2, 6, 12, 24, 48, 96, 64,0},
{0, 120, 124, 84, 84, 116, 32, 0},
{0, 48, 120, 72, 72, 126,126, 0},
{0, 0, 68, 68, 68, 124, 56, 0}, 
{0, 126, 126, 72, 72, 120, 48, 0},
{0, 24, 28, 84, 84, 124, 56, 0}, 
{0, 10, 10, 126, 124, 8, 0, 0},
{0, 124, 252, 164, 164, 188, 152, 0},
{0, 112, 120, 8, 8, 126, 126, 0}, 
{0, 0, 64, 122, 122, 72, 0, 0},
{0, 122, 250, 128, 128, 128, 0, 0}, 
{0, 64, 104, 56, 16, 126, 126, 0},
{0, 0, 64, 126, 126, 66, 0, 0},
{120, 124, 28, 56, 24, 124, 124, 0}, //m
{0, 120, 124, 4, 4, 124, 124, 0},
{0, 56, 124, 68, 68, 124, 56, 0}, // o
{0, 24, 60, 36, 36, 252, 252, 0}, //p
{0, 252, 252, 36, 36, 60, 24, 0}, // q
{0, 8, 12, 4, 4, 124, 124, 0}, // r
{0, 36, 116, 84, 84, 92, 72, 0}, // s
{0, 68, 68, 126, 62, 4, 4, 0}, 
{0, 124, 124, 64, 64, 124, 60, 0},
{0, 28, 60, 96, 96, 60, 28, 0}, // v
{28, 124, 96, 48, 96, 124, 28, 0}, // w
{0, 68, 108, 56, 56, 108, 68, 0}, // x
{0, 60, 124, 224, 160, 188, 156, 0}, // y
{0, 68, 76, 92, 116, 100, 68, 0}
};
// A-Z, space, !, ", #, $, %, & (32), ', ( (34), ) (35),
// 0 (36), 1, 2, ..., 9 (45)
// : (46), ; (47), ? (48), .(49), ,(50)
// + (51), * (52), -, (53), / (54), 
// a (55), b, c, d, e, herz

static uint8_t data[8] = {0x0,0x0,0x0,0x0, 0x0, 0x0, 0x0, 0x0};
char msgTxt[] = "Ich heisse Noe. Und du? ";
uint8_t msgCode[1000] = {0};
int msgLen;

void encodeMessage(char *string, int strLen, uint8_t *codeArr);

void setup() {
  // translate string to internal character code
  msgLen = strlen(msgTxt);
  encodeMessage(msgTxt, msgLen, msgCode);
  
  // put your setup code here, to run once:
  pinMode(CE, OUTPUT);                          //initialized the pin's mode.
  SPI.begin();                                  // start spi function
}

void loop() {
    // loop trhough all letters
    for (int ltr=0;ltr<msgLen;ltr++) {
      // scroll current letter and append following
      for (int pos=0;pos<8;pos++) {
        // {int pos = 0;
        for (int rep=0;rep<SCROLL_DELAY;rep++) {
          // calc followup letter index
          int nxLtr = (ltr+1)%msgLen;
          for (int j=0;j<8;j++) {
            int col1, col2, col3;
            if (j < pos) {
              // paint letter entering the display
              col1 = nxLtr % 3;
              col2 = (nxLtr + 1) % 3;
              col3 = (nxLtr + 2) % 3;
              data[col1] = ~letter[msgCode[nxLtr]][8-pos+j];
              data[col2] = 255;
              data[col3] = ~letter[msgCode[nxLtr]][8-pos+j];
            } else {
              // paint letter leaving the display
              col1 = ltr % 3;
              col2 = (ltr + 1) % 3;
              col3 = (ltr + 2) % 3;
              data[col1] = ~letter[msgCode[ltr]][j-pos];
              data[col2] = 255;
              data[col3] = ~letter[msgCode[ltr]][j-pos];
            }
            data[3] = 0x01 << j ;
            digitalWrite(CE, LOW);
            SPI.transfer(data[RED_DATA]); // pos 1: red
            SPI.transfer(data[BLUE_DATA]); // pos 2: blue
            SPI.transfer(data[GREEN_DATA]); // pos 3: green
            SPI.transfer(data[3]);
            digitalWrite(CE, HIGH);              // send data to SPI channel 0, and the length of the data
            delay(REFRESH_DELAY);
          };
        };
      };
    };
}

void encodeMessage(char *string, int strLen, uint8_t *codeArr) {
  for (uint8_t i=0;i<strLen;i++) {
    if ((int) string[i] >=65 && (int) string[i] <= 90) {
        codeArr[i] = (uint8_t) (string[i] - 65);
    } else if ((int) string[i] >=97 && (int) string[i] <= 122) {
        codeArr[i] = (uint8_t) (string[i] - 42);
    } else {
      switch((int) string[i]) {
        case 33: codeArr[i] = (uint8_t)27; break;
        case 34: codeArr[i] = (uint8_t)28; break;
        case 35: codeArr[i] = (uint8_t)29; break;
        case 36: codeArr[i] = (uint8_t)30; break;
        case 37: codeArr[i] = (uint8_t)31; break;
        case 38: codeArr[i] = (uint8_t)32; break;
        case 39: codeArr[i] = (uint8_t)33; break;
        case 40: codeArr[i] = (uint8_t)34; break;
        case 41: codeArr[i] = (uint8_t)35; break;
        case 48: codeArr[i] = (uint8_t)36; break;
        case 49: codeArr[i] = (uint8_t)37; break;
        case 50: codeArr[i] = (uint8_t)38; break;
        case 51: codeArr[i] = (uint8_t)39; break;
        case 52: codeArr[i] = (uint8_t)40; break;
        case 53: codeArr[i] = (uint8_t)41; break;
        case 54: codeArr[i] = (uint8_t)42; break;
        case 55: codeArr[i] = (uint8_t)43; break;
        case 56: codeArr[i] = (uint8_t)44; break;
        case 57: codeArr[i] = (uint8_t)45; break;
        case 58: codeArr[i] = (uint8_t)46; break;
        case 59: codeArr[i] = (uint8_t)47; break;
        case 63: codeArr[i] = (uint8_t)48; break;
        case 46: codeArr[i] = (uint8_t)49; break;
        case 44: codeArr[i] = (uint8_t)50; break;
        case 43: codeArr[i] = (uint8_t)51; break;
        case 42: codeArr[i] = (uint8_t)52; break;
        case 45: codeArr[i] = (uint8_t)53; break; // -
        case 47: codeArr[i] = (uint8_t)54; break; // /        
        default: codeArr[i] = (uint8_t)26;
      }
    }
  }
  return codeArr;
}
