// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include <stdio.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int receivedDistance =0;
char dir;

//stored values
int dist[4] = {0,0,0,0}; //N,E,S,W
char direc[4] = {'N','E','S','W'};
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //wire event
  Wire.begin(8);
  Wire.onReceive(recieveEvent);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
}

void loop() {
  //topline
  lcd.setCursor(0,0);
  lcd.print("Closest Sensor: ");
  //distance/direction
  lcd.setCursor(0, 1);
  lcd.print(receivedDistance);
  lcd.print(" cm ");
  switch(dir){
    case 'N':
      dist[0] = receivedDistance;
      lcd.print("North");
      break;
    case 'E':
      dist[1] = receivedDistance;
      lcd.print("East ");
      break;
    case 'S':
      dist[2] = receivedDistance;
      lcd.print("South");
      break;
    case 'W':
      dist[3] = receivedDistance;
      lcd.print("West ");
      break;
    default:
      break;
  }
  lcd.print("  ");
  delay(2000);

  //page of sensor values
  lcd.setCursor(0,0);
  for(int i=0;i<4;i++){
    if(i==2){
      lcd.print("   ");
      lcd.setCursor(0,1);
    }
    lcd.print(dist[i]);
    lcd.print("cm ");
    lcd.print(direc[i]);
    lcd.print(" ");
  }
  delay(2000);
}

void recieveEvent(int howMany){
  while(1< Wire.available()){
    receivedDistance = Wire.read();
    Serial.println(receivedDistance);
  }
  dir = Wire.read();
  dirChoice(dir);
  Serial.println(dir);
}

void dirChoice(char direc){
  switch(direc){
    case 'N':
      dist[0] = receivedDistance;
      //lcd.print("North");
      break;
    case 'E':
      dist[1] = receivedDistance;
      //lcd.print("East ");
      break;
    case 'S':
      dist[2] = receivedDistance;
      //lcd.print("South");
      break;
    case 'W':
      dist[3] = receivedDistance;
      //lcd.print("West ");
      break;
    default:
      break;
  }
}

