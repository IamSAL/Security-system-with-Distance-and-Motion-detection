
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ECHOPIN 8
#define TRIGPIN 7
int PIR=0;
int distance=0;
int distanceThreshold = 0;
int cm = 0;
int inches = 0;
int duration=0;


long readUltrasonicDistance(int triggerPin, int echoPin)
{
 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); //clear garbage
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}



void setup() {
  //PIR setup
  pinMode(6, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

 
  //calibrating sensors
  Serial.begin(9600);
  Serial.print("Calibrating Sensor...");
  for (int i=0;i<5;i++)
  {
  Serial.print(".");
  delay(1000);
  }
  Serial.println("Calibration done");
  Serial.println("Sensor Activated");

  //Ultrasonic sensor setup
  pinMode(TRIGPIN,OUTPUT);//SetsthetrigPinasanOUTPUT
  pinMode(ECHOPIN,INPUT);//SetstheechoPinasanINPUT  
    

  lcd.begin(16, 2);
 
 
}

void loop() {

  duration=readUltrasonicDistance(TRIGPIN,ECHOPIN);
   delay(100); //delay to ensure sensor returns correctly.
   distance=duration*0.01723;
   //Serial.println("Distance:");
   //Serial.println(distance);
   if(distance>=16 && distance <=335){
   digitalWrite(9,HIGH); 
   delay(150);
   digitalWrite(9,LOW); 
   delay(150);
   digitalWrite(9,HIGH);
   tone(10,(335-distance)*10,200);
   lcd.print("Detected!!");
   lcd.setCursor(0, 1);
   lcd.print(distance);
   lcd.print(" cm away");
   }else{
   //digitalWrite(10,LOW);
   digitalWrite(9,LOW); 
   lcd.print("No intruders.");
   lcd.setCursor(0, 1);
   lcd.print("Room is secured.");
   }
  //------PIR(no effect in TinkerCAD though,so only printing in serial monitor)--------
  PIR=digitalRead(6);
  if(PIR==HIGH)
  {
    //lcd.print("Detected!!");
    Serial.println("Motion Detected in PIR sensor");
  }
   delay(1000); //delay so user can read before message is cleared for next loop.
   lcd.clear();   
}
 