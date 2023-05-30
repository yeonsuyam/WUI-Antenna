#include <Servo.h>
#include <FastLED.h>

Servo myservold; //Left down servo
Servo myservolu; //Left up servo
Servo myservord; //Right down servo
Servo myservoru; //Right up servo

//IMPORTANT: This is only one of the two LED strips, add the other one
#define NUM_LEDS 7   
#define DATA_PIN 12    
CRGB leds[NUM_LEDS];

int pos = 0, kont, pos2, i, j;

void setup() {
  myservold.attach(2);
  myservolu.attach(3);
  myservord.attach(4);
  myservoru.attach(5);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

void startled(){
    myservold.write(90);
    myservord.write(90);
    //Turn LEDs blue
    for(i = 0; i < 7; i = i + 1){
      leds[i] = CRGB::Blue;
    }
    FastLED.show();
    //Move upper servos down
    for (pos = 0; pos <= 180; pos = pos + 1) {
      pos2 = 180 - pos;
      myservolu.write(pos2);
      myservoru.write(pos);
      delay(10);                      
    }
}

void angry(){
    //Put upper servos in vertical
    myservolu.write(180);
    myservoru.write(0);
    //Move lower servos to horizontal
    for (pos = 90; pos >= 0; pos = pos - 1) {
      pos2 = 180 - pos;
        myservold.write(pos2);
        myservord.write(pos);
        delay(15);                      
      }
    //Turn LEDs on in sequence
    for(kont = 2; kont >= 0; kont = kont - 1){//Amount of repetitions
      for(i = 0; i < 7; i = i + 1){
        for(j = 0; j < 7; j = j + 1){
          leds[j] = 0;
        }
        leds[i] = CRGB::Green;
        FastLED.show();
        delay(100);
      }
    }
}
void greeting(){
    myservold.write(90);
    myservord.write(90);
    for (kont = 0; kont <= 2; kont = kont + 1){//Amount of repetitions
      //Move upper servos down
      for (pos = 0; pos <= 180; pos = pos + 1) {
        pos2 = 180 - pos;
        myservolu.write(pos2);
        myservoru.write(pos);
        delay(10);                      
      }
      //Move upper servos up
      for (pos = 180; pos >= 0; pos = pos - 1) {
        pos2 = 0 + pos;
        myservolu.write(pos2);
        myservoru.write(pos);
        delay(10);                      
      }
    }
}
void default_state(){
    myservold.write(90);
    myservord.write(90);
    myservolu.write(180);
    myservoru.write(180);
    //Turn LEDs default color like purple?
    for(i = 0; i < 7; i = i + 1){
      leds[i] = CRGB::Purple;
    }
    FastLED.show();
    //Move upper servos down
}

void loop() {
  //Write the condition for every state
 int imu = 0;
 if (imu == 0){
  startled();
 }
 else if(imu == 1){
  angry();
 }
 else if(imu == 2){
  greeting
 }
 else{
  default_state(),
 }
}
