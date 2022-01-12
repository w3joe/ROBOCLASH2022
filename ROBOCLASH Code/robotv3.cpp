//WORKING CODE

#include <Servo.h>
#include <IBusBM.h>
 
// Create iBus Object
IBusBM ibus;

#define RMotorPin1 50
#define RMotorPin2 52
#define RMotorSpeed 2

#define LMotorPin1 51
#define LMotorPin2 53
#define LMotorSpeed 3

Servo servo_arm ,servo_arm_2, servo_claw;
  // Generally, you should use "unsigned long" for variables that hold time
  // The value will quickly become too large for an int to store
  unsigned long previousMillis = 0;        // will store last time LED was updated
  unsigned long previousMillis2 = 0;        // will store last time LED was updated
  
  // constants won't change:
  const long interval = 20;           // interval at which to blink (milliseconds)
int x = 90;
int y = 50;


 
// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


 
void setup() {
  
  // Start serial monitor
  Serial.begin(115200);
 
  // Attach iBus object to serial port
  ibus.begin(Serial1);

  pinMode(RMotorPin1, OUTPUT);
  pinMode(RMotorPin2, OUTPUT);
  pinMode(RMotorSpeed, OUTPUT);
  pinMode(LMotorPin1, OUTPUT);
  pinMode(LMotorPin2, OUTPUT);
  pinMode(LMotorSpeed, OUTPUT);

  servo_arm.attach(5,530,2600);
  servo_arm_2.attach(6,530,2600);
  
}
 
void loop() {
 
  // Cycle through first 5 channels and determine values
  // Print values to serial monitor
  // Note IBusBM library labels channels starting with "0"

  //Right Stick, Left/Right
  int Ch1value = readChannel(0,-100,100,0);

  //Right Stick, Up/Down
  int Ch2value = readChannel(1,-100,100,0);

  int Ch3value = readChannel(2,-100,100,0);
  int Ch4value = readChannel(3,-100,100,0);
  
 
  if(Ch1value == 0 && Ch2value > 0){
  int forward_Speed =  Ch2value * 3.64285714;
  //Forward
  digitalWrite(RMotorPin1, HIGH);
  digitalWrite(RMotorPin2, LOW);
  analogWrite(RMotorSpeed, forward_Speed);
  digitalWrite(LMotorPin1, HIGH);
  digitalWrite(LMotorPin2, LOW);
  analogWrite(LMotorSpeed, forward_Speed);

  
 }
 else if(Ch1value > 0 && Ch2value > 0){
//forward right
   int forward_Speed =  Ch2value * 3.64285714;
   int ch1speed = Ch1value * 3.64285714;
   double turning_speed = forward_Speed - ch1speed;
   double turning_speed2 = forward_Speed + ch1speed;
   digitalWrite(RMotorPin1, HIGH);
   digitalWrite(RMotorPin2, LOW);
   analogWrite(RMotorSpeed, abs(turning_speed));
   digitalWrite(LMotorPin1, HIGH);
   digitalWrite(LMotorPin2, LOW);
   analogWrite(LMotorSpeed, abs(turning_speed2));
 }
 else if(Ch1value < 0 && Ch2value > 0){
  //forward left
   int forward_Speed =  Ch2value * 3.64285714;
   int ch1speed = Ch1value * -3.64285714;
   double turning_speed = forward_Speed - ch1speed;
   double turning_speed2 = forward_Speed + ch1speed;
   digitalWrite(RMotorPin1, HIGH);
   digitalWrite(RMotorPin2, LOW);
   analogWrite(RMotorSpeed, abs(turning_speed2));
   digitalWrite(LMotorPin1, HIGH);
   digitalWrite(LMotorPin2, LOW);
   analogWrite(LMotorSpeed,abs(turning_speed) );
  
  
   
  
 }
 else if(Ch1value == 0 && Ch2value < 0){
  int reverse_Speed =  Ch2value * -3.64285714;
  //Reverse
  digitalWrite(RMotorPin1, LOW  );
  digitalWrite(RMotorPin2, HIGH);
  analogWrite(RMotorSpeed,  reverse_Speed);
  digitalWrite(LMotorPin1, LOW);
  digitalWrite(LMotorPin2, HIGH);
  analogWrite(LMotorSpeed, reverse_Speed);

 }
 else if(Ch1value > 0 && Ch2value < 0){
  //Reverse right
  int reverse_Speed =  Ch2value * -3.64285714;
  int ch1speed = Ch1value * 3.64285714;
  double turning_speed = reverse_Speed  - ch1speed;
  digitalWrite(RMotorPin1, LOW);
  digitalWrite(RMotorPin2 , HIGH);
  analogWrite(RMotorSpeed, turning_speed);
  digitalWrite(LMotorPin1, LOW);
  digitalWrite(LMotorPin2 , HIGH);
  analogWrite(LMotorSpeed, reverse_Speed);

 }
 else if(Ch1value < 0 && Ch2value < 0){
  //Reverse left
  int reverse_Speed =  Ch2value * -3.64285714;
  int ch1speed = Ch1value * -3.64285714;
  double turning_speed = reverse_Speed  - ch1speed;
  digitalWrite(RMotorPin1, LOW);
  digitalWrite(RMotorPin2 , HIGH);
  analogWrite(RMotorSpeed, reverse_Speed);
  digitalWrite(LMotorPin1, LOW);
  digitalWrite(LMotorPin2 , HIGH);
  analogWrite(LMotorSpeed, turning_speed);

 }
 else if(Ch1value < 0 && Ch2value == 0){
  //turning 
  int ch1speed = Ch1value * -3.64285714;
  digitalWrite(RMotorPin1, HIGH);
  digitalWrite(RMotorPin2 , LOW);
  analogWrite(RMotorSpeed, ch1speed);
  digitalWrite(LMotorPin1, LOW);
  digitalWrite(LMotorPin2 , HIGH);
  analogWrite(LMotorSpeed, ch1speed);

 }
  else if(Ch1value > 0 && Ch2value == 0){
  //turning 
  int ch1speed = Ch1value * 3.64285714;
  digitalWrite(RMotorPin1, LOW);
  digitalWrite(RMotorPin2 , HIGH);
  analogWrite(RMotorSpeed, ch1speed);
  digitalWrite(LMotorPin1, HIGH);
  digitalWrite(LMotorPin2 , LOW);
  analogWrite(LMotorSpeed, ch1speed);

 }
Serial.print(Ch1value);
Serial.print(" | ");\
Serial.print(Ch2value);
Serial.println(" | ");

  //servo motor
  /*if(Ch3value == 0){ 
    servo_arm.write( 190 );
    servo_arm_2.write( 190 );
    
  }
  if(Ch3value > 0){
    int servo_turn = Ch3value * 1.90; 
    servo_arm.write( servo_turn );
    servo_arm_2.write( 190 - servo_turn );
    
  }*/

  //servo_claw
  //close claw
  
  if(Ch4value > 5){
  servo_claw.attach(9,1286,1812); 
  
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= interval) {
  // save the last time you blinked the LED
  previousMillis = currentMillis;

  int max = 70; //change
   if(x<max) x=max;
   x--;
  }
  
  servo_claw.write(x);
  Serial.print(x);
  Serial.print(" | ");
  }
  //claw open
  else if(Ch4value< -5){
  servo_claw.attach(9,1286,1812);
     
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
  // save the last time you blinked the LED
  previousMillis = currentMillis;
  // min = 123
  //max = 72
   int min = 140;
   if(x>min) x=min;
  x++;
  }
  
  servo_claw.write(x);
  }
  else if(Ch4value <= 5 || Ch4value >= -5)
    servo_claw.detach();
 
//move claw arm upwards
   if(Ch3value > 15){
  servo_arm.attach(5); 
  servo_arm_2.attach(6); 
  
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis2 >= interval) {
  // save the last time you blinked the LED
  previousMillis2 = currentMillis;

  int max = 10; //change
   if(y<max) y=max;
   y--;
  }
  
  servo_arm.write(y);
  servo_arm_2.write(y);
  }
  //move claw arm upwards
  else if(Ch3value< -15){
  servo_arm.attach(5); 
  servo_arm_2.attach(6); 
     
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis2 >= interval) {
  // save the last time you blinked the LED
  previousMillis2 = currentMillis;
   int min = 110;
   if(y>min) y=min;
  y++;
  }
  
  servo_arm.write(y);
  servo_arm_2.write(y);
  }
  else if(Ch3value <= 15 || Ch3value >= -15)
    {
      servo_arm.detach(); 
      servo_arm_2.detach();
    }
}
