#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



Servo base;
Servo s1;
Servo s2;
Servo s3;
Servo s4;


int pos = 0;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


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



int posbase=90;
int poss1=90;
int poss2=90;
int poss3=90;
int poss4=80;



void setup() {

base.attach(2);

s1.attach(3);
s2.attach(4);
s3.attach(5);
s4.attach(6);

Serial.begin(9600);

radio.begin();
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MIN);
radio.startListening(); // Set the module as receiver

base.write(posbase);

s1.write(poss1);
s2.write(poss2);
s3.write(poss3);
s4.write(poss4);

}




void loop() {
//printdata();
if (radio.available()) {


radio.read(&data, sizeof(package));
posbase=map(data.vp1,0,1023,170,10);
base.write(posbase);
poss4=map(data.vp2,0,1023,60,110);
s4.write(poss4);



if(data.vj1x<400 && poss1<180){
poss1=poss1+3;
s1.write(poss1);
}

else if(data.vj1x>600 && poss1>10){
poss1=poss1-3;
s1.write(poss1);
}

if(data.vj2x<300 && poss2>20
){
poss2=poss2-5;
s2.write(poss2);
}

else if(data.vj2x>800 && poss2<180){
poss2=poss2+5;
s2.write(poss2);
}

if(data.vj2y>800 && poss3<180){
poss3=poss3+5;
s3.write(poss3);
}

else if(data.vj2y<200 && poss3>0){
poss3=poss3-5;
s3.write(poss3);
}
}}