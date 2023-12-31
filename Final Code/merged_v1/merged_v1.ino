#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> 
#include <Sim800l.h>
#include <Timer.h>

/****** Instance Declarations **************/
LiquidCrystal_I2C lcd(0x27,20,4);  
Sim800l Sim800l;
Timer t;
/*******************************************/

/******* Pin Configurations ****************/
int trigPin = 2,
    echoPin = 3,
    led1 = 4, 
    led2 = 5, 
    led3 = 6, 
    led4 = 7;

/*
 *    PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   SIM800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX    
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST 
*/
 
/*******************************************/

/********* Global Variables ****************/
long duration;
int distance;
char* text = "Test";
char* number = "09171550845";;
bool error;
/*******************************************/

void setup() {
  //Define inputs and outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Initialize LCD peripheral
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("APP START");

  //Initialize the GSM peripheral
  Sim800l.begin();
 
  //Initialize UART to 9600 Hz baudrate
  Serial.begin(9600);
  
  t.every(1000, getWaterLevel);
}

void loop() {
  t.update();
  //error=Sim800l.sendSms(number,text);
  //print(error);
}

void getWaterLevel() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance:
  distance = duration*0.034/2;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance >= 0 && distance <= 20) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
    } else if (distance >= 21 && distance <= 40) {
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
    } else if (distance >= 41 && distance <= 60) {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, LOW);
    } else if (distance > 60) {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH);
        text = "Distance is greater than 120";
        //error=Sim800l.sendSms(number,text);
        //print(error);
    } else {
        Serial.println("Invalid distance\n");
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
    }
}
