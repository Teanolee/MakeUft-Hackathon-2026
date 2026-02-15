#include <Wire.h>
#include <string.h>
int trigPin = 2;

int echoPins[4] = {13, 12, 11, 10};
int ledPins[4]  = {3, 4, 5, 6};
//char sensor[10][4]= {"North","East","South","West"};
float sos = 343;

//int pingTime1, pingTime2, pingTime3, pingTime4;
//float distance1, distance2, distance3, distance4;
//float time1, time2, time3, time4;

float threshold = 0.15;

float measureDistance(int echoPin) {
  
  //send triggr pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long pingTime = pulseIn(echoPin, HIGH, 30000);

  float time = pingTime*(pow(10,-6));
  float distance = (sos*time)/2;

  return distance;
}

void setup() {
  // put your setup code here, to run once:
  
  Wire.begin();

  for (int i = 0; i < 4; i++) {
      pinMode(echoPins[i], INPUT);
      pinMode(ledPins[i], OUTPUT);
    }
  
  pinMode(trigPin,OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  for (int i = 0; i < 4; i++) {

    float distance = measureDistance(echoPins[i]);

    //Serial.print("Sensor ");
    //Serial.print(i + 1);
    //Serial.print(": ");
    //Serial.println(distance);
    //int flag = 0;

    if (distance > 0 && distance < threshold) {
      //flag = 1;
      digitalWrite(ledPins[i], HIGH);
      Wire.beginTransmission(8);
      Wire.write(int(distance*100));
      sensorChoice(i);
      //Wire.write(sensor[10][i]);
      //Serial.println(sensor[10][i]);
      Wire.endTransmission();

    } else {
      digitalWrite(ledPins[i], LOW);
    }

    delay(100);  // Critical: prevents ultrasonic overlap
  }
  delay(100);

}

void sensorChoice(int i){
  switch(i){
    case 0:
      Wire.write('N');
      Serial.println("NORTH");
      break;
    case 1:
      Wire.write('E');
      break;
    case 2:
      Wire.write('W');
      break;
    case 3:
      Wire.write('S');
      break;
    default:
      break;
  }
}
