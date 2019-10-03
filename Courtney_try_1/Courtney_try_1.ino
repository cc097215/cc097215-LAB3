#define IRPin A0
#define LED 13 //Sets LED pin

#include <math.h>

#define LED1 2 // Green
#define LED2 4 // Yellow
#define LED3 6 // Red

#define Off 0
#define On 1

void setup() {
  Serial.begin(9600);
  Serial.println("Courtney IR sensor program");
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); 
  pinMode(IRPin, INPUT); //input from sensor

}
void loop() 
{  
  static bool WasObject = false;
  //static bool LED3On = false;
  static bool TimerOn = false;

  //Distance Math
  float NewRead = ReadValue(); //Read from sensor
  float Distance = FindDistance(NewRead); //Find distance
     /*Serial.print("Distance: ");
     Serial.println(Distance);*/
  static bool timerun = false;

//Decide LED1 & LED2
  if (Distance > 5 && Distance <= 25) {
    Object(); //LED1 & LED2
    WasObject = true;
    //Serial.println("Current: On");
    //Serial.print(Distance);
    if (TimerOn == false){ //Light off
      digitalWrite(LED3, HIGH);
      Serial.println("TimerOn = false");
    }
    else if (TimerOn == true){ //Light on
      digitalWrite(LED3, LOW);
      TimerOn = false;
      Serial.println("TimerOn = true");
    }
      
  }
  else {
    NoObject(); //LED1 & LED2
    if (WasObject == true){ //Start timer
      //Serial.println("Timer Start");
      timerun = timer();
    }
  }
}

bool timer(){
  static bool NewStart = true;
  int CurrentTime = millis();
  static int StopTime = 0;
  bool timerun;
  
  Serial.print("Current Time:");
  Serial.println(CurrentTime);
  
  if (NewStart == true){
    StopTime = CurrentTime + 2000;
    NewStart = false;
    Serial.print("Current Time Stop:");
    Serial.println(StopTime);
    timerun = true;
    Serial.println("Timer = true in Timer");
  }
  
  else if(CurrentTime >= StopTime && StopTime != 0){
    NewStart = true;
    digitalWrite(LED3, LOW); //Turns off LED3
    Serial.println("Timer Reset");
    timerun = false;
    Serial.println("Timer = false in Timer");
  }
  return timerun; 
}

void Object(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}

void NoObject(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
}

float ReadValue() {
  //Referenced from Wilhem's Practice Code
  int A2D = analogRead(IRPin);
  float SensorVolts = double(A2D);  //To double
  SensorVolts *= 5.0/1024;         // To Volts
  /*Serial.print("Read: ");
  Serial.println(SensorVolts);*/
  return SensorVolts;
}
float FindDistance(float ReadValue){
  float V;
  int Distance;
  V = ReadValue; //Sets Volts
  Distance = pow((V/14.475),(1/-0.8118)); //Sensor Calibration Curve
  //Serial.print("Distance: ");
  //Serial.println(Distance);
  return Distance;
}
