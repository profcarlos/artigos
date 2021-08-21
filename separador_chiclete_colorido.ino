#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

Servo p;
Servo q;

const int sio = 2;      
const int unused = 255;     
const int sioBaud = 4800;
const int waitDelay = 200;

int red;
int grn;
int blu;

void setup() {
  Serial.begin(9600);
  reset();				  
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("= (00 $ m) !"); 
  serout.end();			  
  serin.begin(sioBaud);	        
  pinMode(sio, INPUT);
  p.attach(8);
  q.attach(9);
}

void loop() {
  readData();
}  

void mexe(){
  if(red==grn==blu){
    delay(500);
  }else{
    if(red>grn){
      if(red>blu){
        p.write(60);
        delay(1000);
      }else{
        p.write(120);
        delay(1000);
      }
    }else{
      if(grn>blu){
        p.write(90);
        delay(1000);
      }else{
        p.write(120);
        delay(1000);
      }
    }
  }
  q.write(170);
  delay(500);
  q.write(10);
  delay(750);
  q.write(90);
  delay(1500);
}


void reset() {
  delay(200);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  pinMode(sio, INPUT);
  while (digitalRead(sio) != HIGH);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  delay(80);
  pinMode(sio, INPUT);
  delay(waitDelay);
}

void readData() {
  char buffer[32];
  if (serin.available() > 0) {
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 9; i++) {
        while (serin.available() == 0);    
        buffer[i] = serin.read();
        if (buffer[i] == '$')              
          return;
      }
      parseAndPrint(buffer);
      delay(10);
    }
  }
}

void parseAndPrint(char * data) {
  sscanf (data, "%3x%3x%3x", &red, &grn, &blu);
  char buffer[32];
  sprintf(buffer, "R%4.4d G%4.4d B%4.4d", red, grn, blu);
  Serial.println(buffer);
  serin.end();
  mexe();
  serin.begin(sioBaud);
}
