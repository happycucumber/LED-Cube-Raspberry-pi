#include <wiringPi.h>
#include <wiringShift.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "time.h"
//#include "sys/types.h"
//#include "netinet/in.h"
//소켓 프로그래밍에 사용될 헤더파일 선언

#define BUF_LEN 128

#define latchPin 0
#define clockPin 2
#define dataPin  3
#define prev_button 24
#define next_button 25
#define del 1
#define rotation_delay 120
#define kind 7

void updateShiftRegister();
void prev();
void next();
void loadData();

typedef enum {false, true} bool;

//int a = 0;
int d;
int data[8][8];
int i,j,k; //반복문용
int level[] = {254,253,251,247,239,223,191,127};
bool check = false;

FILE *pFile = NULL;
char strPath[] = { "/ramdisk/a" };

void loadData(){
        pFile = fopen( "/home/pi/LedCube/pattern/temp/LedData.txt", "r" );
        if( pFile != NULL ) {
                char strTemp[255];
                char *pStr;
                i = 0;

                while( !feof( pFile ) ) {
                        pStr = fgets( strTemp, sizeof(strTemp), pFile );
                        //printf( "%s", strTemp );
                        //printf( "%s", pStr );

                        char *ptr = strtok(pStr, ","); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

                        j = 0;
                        while (ptr != NULL) { // 자른 문자열이 나오지 않을 때까지 반복
                                data[i][j]=atoi(ptr); // 자른 문자열 출력
                                //printf(ptr);
                                ptr = strtok(NULL, ","); // 다음 문자열을 잘라서 포인터를 반환
                                j++;
                        }
                        i++;
                }
                fclose( pFile );
        }else {
                //에러 처리
        }
}
void loadData2(){
        pFile = fopen( "/home/pi/LedCube/pattern/temp/b", "r" );
        if( pFile != NULL ) {
                int ch,loop;
                while ( (ch = fgetc(pFile)) != EOF ) {
                        data[loop/8][loop%8] = ch;
                        loop++;
                }
                fclose( pFile );
        }else {
                //에러 처리
                //printf("%s\n","error.....fix it!" );
        }
}

void loadData2(){
        pFile = fopen( "/home/pi/LedCube/pattern/temp/b", "r" );
        if( pFile != NULL ) {

                fclose( pFile );
        }else {
                //에러 처리
        }
}

int main(/*int argc,char *argv[]*/){
        //a= *argv[1]-48;
        wiringPiSetup ();
        pinMode(latchPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        //pinMode(next_button, INPUT);
        //pinMode(prev_button, INPUT);

/*****************************프리셋 정보 가져오는 부분************************************/
        loadData();
//a=49;
        for(;;) {
                if(access( strPath, 0 )==0) {
                        loadData();
                        remove(strPath);
                }
//if(a==49){
                for(i=0; i<8; i++) {
                        digitalWrite(latchPin, LOW);
                        for(j=0; j<8; j++)
                                shiftOut(dataPin, clockPin,MSBFIRST,data[i][7-j]);
                        shiftOut(dataPin, clockPin,MSBFIRST,level[i]);
                        // delay(1000); //한층씩 켜지는지 확인하기위함
                        digitalWrite(latchPin, HIGH);
                        //delay(1);
                        delayMicroseconds(1);
                }


/*}
   else if(a==0){
    digitalWrite(latchPin, LOW);
    for(d = 0;d<9;d++)
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    digitalWrite(latchPin, HIGH);
   }else if(a==1){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,255);
    shiftOut(dataPin, clockPin,MSBFIRST ,255);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    digitalWrite(latchPin, HIGH);
    delay(rotation_delay);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin,MSBFIRST ,128);
    shiftOut(dataPin, clockPin,MSBFIRST ,64);
    shiftOut(dataPin, clockPin,MSBFIRST ,32);
    shiftOut(dataPin, clockPin,MSBFIRST ,16);
    shiftOut(dataPin, clockPin,MSBFIRST ,8);
    shiftOut(dataPin, clockPin,MSBFIRST ,4);
    shiftOut(dataPin, clockPin,MSBFIRST ,2);
    shiftOut(dataPin, clockPin,MSBFIRST ,1);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    digitalWrite(latchPin, HIGH);
    delay(rotation_delay);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,24);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    digitalWrite(latchPin, HIGH);
    delay(rotation_delay);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin,MSBFIRST ,1);
    shiftOut(dataPin, clockPin,MSBFIRST ,2);
    shiftOut(dataPin, clockPin,MSBFIRST ,4);
    shiftOut(dataPin, clockPin,MSBFIRST ,8);
    shiftOut(dataPin, clockPin,MSBFIRST ,16);
    shiftOut(dataPin, clockPin,MSBFIRST ,32);
    shiftOut(dataPin, clockPin,MSBFIRST ,64);
    shiftOut(dataPin, clockPin,MSBFIRST ,128);
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    digitalWrite(latchPin, HIGH);
    delay(rotation_delay);

   }else if(a==2){
      for(i = 0; i<8; i++){
        digitalWrite(latchPin, LOW);

      for(j = 0; j<8-i; j++)
        shiftOut(dataPin, clockPin,MSBFIRST ,0);

      shiftOut(dataPin, clockPin,MSBFIRST ,255);

      for(k = 0; k<i;k++)
        shiftOut(dataPin, clockPin,MSBFIRST ,0);

      shiftOut(dataPin, clockPin,MSBFIRST ,0);
      digitalWrite(latchPin, HIGH);
      delay(1000);
   }
   digitalWrite(latchPin, LOW);

   for(i = 0; i<8; i++){
    digitalWrite(latchPin, LOW);

    for(k = 0; k<i;k++)
      shiftOut(dataPin, clockPin,MSBFIRST ,0);

    shiftOut(dataPin, clockPin,MSBFIRST ,255);

    for(j = 0; j<8-i; j++)
      shiftOut(dataPin, clockPin,MSBFIRST ,0);

   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   delay(1000);
   }
   }else if(a==3){
   digitalWrite(latchPin, LOW);
   for(d=0;d<7;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,127);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   for(d=0;d<6;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,63);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   for(d=0;d<5;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,31);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   for(d=0;d<4;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,15);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   for(d=0;d<4;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,7);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   for(d=0;d<5;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,3);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   for(d=0;d<6;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,1);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   for(d=0;d<7;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   delay(del);
   }else if(a==4){
   digitalWrite(latchPin, LOW);
   for(d=0;d<7;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,24);
   shiftOut(dataPin, clockPin,MSBFIRST ,231);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   for(d=0;d<6;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,60);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,195);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   for(d=0;d<5;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,126);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,129);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   for(d=0;d<5;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,126);for(d=0;d<5;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,129);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,60);
   for(d=0;d<6;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,195);
   digitalWrite(latchPin, HIGH);
   delay(del);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin,MSBFIRST ,24);
   for(d=0;d<7;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,223);
   digitalWrite(latchPin, HIGH);
   delay(del);
   }else if(a==5){
   digitalWrite(latchPin, LOW);
   for(d=0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,129);
   shiftOut(dataPin, clockPin,MSBFIRST ,126);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds (1);
   digitalWrite(latchPin, LOW);
   for(d=0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,66);
   shiftOut(dataPin, clockPin,MSBFIRST ,189);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds (1);
   digitalWrite(latchPin, LOW);
   for(d=0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,36);
   shiftOut(dataPin, clockPin,MSBFIRST ,219);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds (1);
   digitalWrite(latchPin, LOW);
   for(d=0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,24);
   shiftOut(dataPin, clockPin,MSBFIRST ,231);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds (1);
   }else if(a==6){
   digitalWrite(latchPin, LOW);
   for(d=0;d<7;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   shiftOut(dataPin, clockPin,MSBFIRST ,2);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds (100);
   }else if(a==7){
   digitalWrite(latchPin, LOW);
   for(d = 0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,0);
   digitalWrite(latchPin, HIGH);
   a==100;
   }else if(a==8){
   digitalWrite(latchPin, LOW);
   for(d = 0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,24);
   shiftOut(dataPin, clockPin,MSBFIRST ,126);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds(del);

   digitalWrite(latchPin, LOW);
   for(d = 0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,60);
   shiftOut(dataPin, clockPin,MSBFIRST ,189);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds(del);

   digitalWrite(latchPin, LOW);
   for(d = 0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,126);
   shiftOut(dataPin, clockPin,MSBFIRST ,195);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds(del);

   digitalWrite(latchPin, LOW);
   for(d = 0;d<8;d++)
   shiftOut(dataPin, clockPin,MSBFIRST ,255);
   shiftOut(dataPin, clockPin,MSBFIRST ,231);
   digitalWrite(latchPin, HIGH);
   delayMicroseconds(del);
   }else if(a==9){
    digitalWrite(latchPin, LOW);
    for(d = 0;d<7;d++)
    shiftOut(dataPin, clockPin,MSBFIRST ,0);
    shiftOut(dataPin, clockPin,MSBFIRST ,1);
    shiftOut(dataPin, clockPin,MSBFIRST ,254);
    digitalWrite(latchPin, HIGH);
   }
   /*/
        }
        return 0;
}
/*
   void prev(){
   if(a==0)
   a=kind;
   else
   a--;

   delay(50);
   }
   void next(){
   if(a==kind)
   a=0;
   else
   a++;

   delay(50);
   }
 */
