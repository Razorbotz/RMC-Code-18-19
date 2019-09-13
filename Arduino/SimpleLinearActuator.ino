#include <Servo.h>

// Pins
int PWM_L = 9;
int PWM_R = 10;
Servo servoL;
Servo servoR;

// Timing
long prevTime = 0;
bool ESTOP = true;

// Constants
#define ADJ_L_F 0.91
#define ADJ_L_B 0.88
#define MSG_TIMEOUT 500 //ms

void setup() {
  servoL.attach(PWM_L);
  servoR.attach(PWM_R);
  Serial.begin(115200);
  Serial.println("START: ");
}

// Sets speed of actuators
//   speedVal - 0 to 255 speed value where 127 is zero
void SetSpeed(float speedVal, int pinForSide) {
  
  if (speedVal > 0 && pinForSide == PWM_L) speedVal = speedVal * ADJ_L_F;
  else if (speedVal < 0 && pinForSide == PWM_L) speedVal = speedVal * ADJ_L_B;
  
  // Servo goes between 0 and 180, where zero is 90
  // Map speedVal (w/ range of [-1, 1]) to this new range by adding 1 (changes range 
  //   to [0, 2]), dividing by 2 (range -> [0, 1]) and multiplying by 180 (range -> [0, 180])
  float adjSpeed = (speedVal + 1) * 180 / 2;
  if (pinForSide == PWM_L) servoL.write(adjSpeed);
  else if (pinForSide == PWM_R) servoR.write(adjSpeed);
}

void loop() {
  //Serial.print("a");
  if (Serial.available() > 0) {
    int c = Serial.read();
    //Serial.print("c = ");
    Serial.print((char)c);
    switch(c) {
      case 'E':
//        prevTime = millis();
        Serial.println(" ESTOP");
        SetSpeed(0, PWM_L);
        SetSpeed(0, PWM_R);
        ESTOP = true;
        break;
      case 'G':
//        prevTime = millis();
        Serial.println(" GO");
        ESTOP = false;
    }
    if(!ESTOP){
      switch(c){
        case 'A':
//          prevTime = millis();
          Serial.println(" A");
          while (Serial.available() < 1) {
            delay(1);
          }
          c = Serial.read();
          SetSpeed((int)c/127.5-1.0, PWM_L);
          SetSpeed((int)c/127.5-1.0, PWM_R);
          break;
        case 'S': //soft stop
          Serial.println(" Stop");
          SetSpeed(0, PWM_R);
          SetSpeed(0, PWM_L);
          break;
        case 'L': //Left exstend
 //         prevTime = millis();
          Serial.println(" Left");
          SetSpeed(0, PWM_R);
          SetSpeed(1, PWM_L);
          break;
        case 'l': //Left retracked
 //         prevTime = millis();
          Serial.println(" left");
          SetSpeed(0, PWM_R);
          SetSpeed(-1, PWM_L);
          break;
        case 'R': //Right exstend
//          prevTime = millis();
          Serial.println(" Right");
          SetSpeed(1, PWM_R);
          SetSpeed(0, PWM_L);
          break;
        case 'r': //Left retracked
//          prevTime = millis();
          Serial.println(" right");
          SetSpeed(-1, PWM_R);
          SetSpeed(0, PWM_L);
          break;
        case 'D': //Down
//          prevTime = millis();
          Serial.println(" Down");
          SetSpeed(1.0, PWM_L);
          SetSpeed(1.0, PWM_R);
          break;
        case 'U': //Up
//          prevTime = millis();
          Serial.println(" Up");
          SetSpeed(-1.0, PWM_L);
          SetSpeed(-1.0, PWM_R);
      }
    }
  }

//  if (millis() - prevTime > MSG_TIMEOUT) {
//    SetSpeed(0, PWM_L);
//    SetSpeed(0, PWM_R);
//  }
  

}
