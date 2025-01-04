#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


int tg1=5;
int tg2=6;
int p1=A6;
int p2=A5;
int s1=10;
int s2=9;
int s3=3;
int s4=2;
int j1x=A3;
int j1y=A4;
int j2x=A2;
int j2y=A1;
int j2s=A0;


struct package {
int vp1;
int vp2;
int vj1x;
int vj1y;
int vj2x;
int vj2y;
int vtg1;
int vtg2;
int vj2s;
int vs1;
int vs2;
int vs3;
int vs4;
};
package data;


void setup() {

radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MIN);
radio.stopListening();

Serial.begin(9600);

pinMode(tg1,INPUT);
pinMode(tg2,INPUT);
pinMode(p1,INPUT);
pinMode(p2,INPUT);
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);
pinMode(s4,INPUT);
pinMode(j1x,INPUT);
pinMode(j1y,INPUT);
pinMode(j2y,INPUT);
pinMode(j2s,INPUT);


// Set initial default values
data.vj1x = 512;
data.vj1y = 512;
data.vj2x = 512;
data.vj2y = 512;
data.vp1 = 512;
data.vp2 = 512;
data.vj2s = 1;
data.vtg1 = 1;
data.vtg2 = 1;
data.vs1 = 1;
data.vs2 = 1;
data.vs3 = 1;
data.vs4 = 1;
}


void loop() {
// Read all analog inputs
data.vj1x = analogRead(j1x);
data.vj1y = analogRead(j1y);
data.vj2x = analogRead(j2x);
data.vj2y = analogRead(j2y);
data.vp1 = analogRead(p1);
data.vp2 = analogRead(p2);
// Read all digital inputs
data.vj2s = digitalRead(j2s);
data.vtg1 = digitalRead(tg1);
data.vtg2 = digitalRead(tg2);
data.vs1 = digitalRead(10);
data.vs2 = digitalRead(s2);
data.vs3 = digitalRead(s3);
data.vs4 = digitalRead(s4);
radio.write(&data, sizeof(package));
}