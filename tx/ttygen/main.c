// RTTY Encoder/Transmitter
//
// Reads an input ASCII text file (xmit.txt) and generates a corresponding RTTY/Baudot encoded pcm audio file.
//
// FSK and sampling frequencies can be controlled by the #define statements, the baudot rate is controlled by the BURST_LENGTH parameter.
//
// Initial version, Deyan Levski, deyan.levski@gmail.com, 13.07.2014
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358
#endif
#define ZERO_FREQUENCY 1000 // Hz
#define ONE_FREQUENCY 4000 // Hz
#define SAMPLING_FREQUENCY 44100 // Hz
#define BURST_LENGTH 0.01   // sec


#define MAXTEXTLEN 100 // Maximum text length in ASCII input file


/* char getBin(unsigned int x)
{

char bits[] = "00000";

bits[0] = (x & 1) + '0';
x >>= 1;
bits[1] = (x & 1) + '0';
x >>= 1;
bits[2] = (x & 1) + '0';
x >>= 1;
bits[3] = (x & 1) + '0';
x >>= 1;
bits[4] = x + '0';
return bits;
}*/

 const int baudotLookup[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,
                            14,15,16,17,18,19,20,21,22,23,24,25,26}; // Baudot encodung LUT

 inline char baudotEnc(char letter)
 {
       int strLU = baudotLookup[letter-'A'];
       return strLU;
 }

int fskmod(int sk)

{
    FILE* f = fopen("ttyburst.pcm", "a+");
    double t;
  for (t = 0; t < BURST_LENGTH; t += 1./SAMPLING_FREQUENCY) // Fs = defined
  {
    double sample1k = 15000 * sin(2 * M_PI * ZERO_FREQUENCY * t); // logic zero sine wave
    double sample2k = 15000 * sin(2 * M_PI * ONE_FREQUENCY * t); // logic one sine wave
    short s16 = (short)sample1k;
    short d16 = (short)sample2k;
    unsigned char c;

    if (sk == 1) {
    c = (unsigned)d16 % 256;
    fwrite(&c, 1, 1, f);
    c = (unsigned)d16 / 256 % 256;
    fwrite(&c, 1, 1, f);
    }
    else {
    c = (unsigned)s16 % 256;
    fwrite(&c, 1, 1, f);
    c = (unsigned)s16 / 256 % 256;
    fwrite(&c, 1, 1, f);
    }

  }
  fclose(f);
}

int ttyenc(char str[MAXTEXTLEN])
{
    char xmitChar;
    int LUTNr;
    int tp;
    int xmitLength = strnlen(str,MAXTEXTLEN);
//    printf("%i",xmitLength);

    for (tp = 0; tp < xmitLength; tp += 1){

    xmitChar = str[tp]; // fetch single character
    LUTNr = baudotEnc(xmitChar); // LUT number based on fetched single character

    switch(LUTNr)
    {
        case 0 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(1);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 1 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(0);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 2 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(0);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 3 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(1);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 4 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(0);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 5 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(0);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 6 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(1);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 7 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(0);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 8 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(1);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 9 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(1);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 10 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(0);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 11 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(1);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 12 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(0);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 13 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(1);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 14 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(1);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 15 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(0);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 16 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(1);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 17 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(1);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 18 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(0);fskmod(1);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 19 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(1);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 20 :
            fskmod(0); // start bit
            fskmod(0); fskmod(0); fskmod(0);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 21 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(1);fskmod(0);fskmod(0);
            fskmod(1); // stop bit
        break;
        case 22 :
            fskmod(0); // start bit
            fskmod(0); fskmod(1); fskmod(1);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 23 :
            fskmod(0); // start bit
            fskmod(1); fskmod(1); fskmod(0);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 24 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(1);fskmod(1);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 25 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(1);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
        case 26 :
            fskmod(0); // start bit
            fskmod(1); fskmod(0); fskmod(0);fskmod(0);fskmod(1);
            fskmod(1); // stop bit
        break;
    }

//    printf("%i",LUTNr);

    }
//    return out;
}

int main(void)
{
  //FILE* f = fopen("sinewave.pcm", "wb");

  char source[MAXTEXTLEN + 1];

  FILE *fp = fopen("xmit.txt", "r");

    if (fp != NULL) {
        size_t newLen = fread(source, sizeof(char), MAXTEXTLEN, fp);
        if (newLen == 0) {
            fputs("Error reading file", stderr);
        } else {
            source[++newLen] = '\0';
        }

    fclose(fp);
}

//  char transmitString[MAXTEXTLEN + 1] = source;

    printf("File read successfully.\nEncoding... \n");
    ttyenc(source);
    printf("Encoding completed!\n");

//  fclose(f);
  return 0;
}
