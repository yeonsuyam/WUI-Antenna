#include <Servo.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
void setupIMU(){
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
}

Servo myservold; //Left down servo
Servo myservolu; //Left up servo
Servo myservord; //Right down servo
Servo myservoru; //Right up servo

//IMPORTANT: This is only one of the two LED strips, add the other one
#define NUM_LEDS 7   
#define DATA_PIN 14
#define DATA_PIN2 9    
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

int pos = 0, kont, pos2, i, j;

void setup() {
  myservold.attach(4);  //Left down servo
  myservolu.attach(5);  //Left up servo
  myservord.attach(7);  //Right down servo
  myservoru.attach(6);  //Right up servo
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2>(leds2, NUM_LEDS);

  setupIMU();


}

void startled(){
    myservold.write(90);
    myservord.write(90);
    //Turn LEDs blue
    for(i = 0; i < 7; i = i + 1){
      leds[i] = CRGB::Blue;
      leds2[i] = CRGB::Blue;
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
    // for (pos = 0; pos <= 90; pos = pos + 1)
    // for (pos = 90; pos >= 0; pos = pos - 1)
    for(i = 0; i < 7; i = i + 1){
      leds[i] = CRGB::Green;
      leds2[i] = CRGB::Green;
    }
    FastLED.show();


    for (pos = 0; pos <= 90; pos = pos + 1){
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
          leds2[j] = 0;
        }
        leds[i] = CRGB::Green;
        leds2[i] = CRGB::Green;
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
    myservolu.write(90);
    myservoru.write(90);
    //Turn LEDs default color like purple?
    for(i = 0; i < 7; i = i + 1){
      leds[i] = CRGB::Purple;
      leds2[i] = CRGB::Purple;
    }
    FastLED.show();
    //Move upper servos down
}

float dataBefore = 0.0;
void loop() {
  //Write the condition for every state
  sensors_event_t event; 
  accel.getEvent(&event);
  // Serial.println(event.acceleration.);
  // if ((event.acceleration.z - dataBefore) < -2)
  if (event.acceleration.x > 9.5)
  {
    startled();
    Serial.println("startled");
    delay(1000);
  }
  else if (event.acceleration.z > 7)
  {
    angry();
    Serial.println("angry");
    delay(1000);
  }
  else 
  {
    default_state();
    Serial.println("default");
  }
  dataBefore = event.acceleration.z;
}
