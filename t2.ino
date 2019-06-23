/* FSR testing sketch.

  Connect one end of FSR to 5V, the other end to Analog 0.
  Then connect one end of a 10K resistor from Analog 0 to ground
  Connect LED from pin 11 through a resistor to ground

  For more information see www.ladyada.net/learn/sensors/fsr.html */

#include "FSR.h"

#include <Adafruit_NeoPixel.h>
#include "VibrationMotor.h"
#include <MsTimer2.h>

#define FSR_1_PIN_1  A10
#define FSR_2_PIN_1 A0
#define FSR_3_PIN_1 A3
#define FSR_4_PIN_1 A13
#define FSR_5_PIN_1 A11
#define FSR_6_PIN_1 A1
//#define FSR_6_PIN_1 A7
#define LEDSTICK_PIN_DATAIN 6
#define VIBRATIONMOTOR1_1_PIN_COIL1 4
#define VIBRATIONMOTOR2_2_PIN_COIL1 3
#define VIBRATIONMOTOR3_3_PIN_COIL1 2
#define VIBRATIONMOTOR4_4_PIN_COIL1 5
int fsrReading;      // the analog reading from the FSR resistor divider
const int NUM_PIXELS = 60;
const int NUM_STRIPS = 6;
const int Pins[NUM_STRIPS] = {31, 32, 33, 34, 35, 36};
// An array of the pin numbers for the strips
Adafruit_NeoPixel strip = Adafruit_NeoPixel(21, LEDSTICK_PIN_DATAIN, NEO_GRB + NEO_KHZ800);


FSR fsr_1(FSR_1_PIN_1);
FSR fsr_2(FSR_2_PIN_1);
FSR fsr_3(FSR_3_PIN_1);
FSR fsr_4(FSR_4_PIN_1);
FSR fsr_5(FSR_5_PIN_1);
FSR fsr_6(FSR_6_PIN_1);
VibrationMotor vibrationMotor1_1(VIBRATIONMOTOR1_1_PIN_COIL1);
VibrationMotor vibrationMotor2_2(VIBRATIONMOTOR2_2_PIN_COIL1);
VibrationMotor vibrationMotor3_3(VIBRATIONMOTOR3_3_PIN_COIL1);
VibrationMotor vibrationMotor4_4(VIBRATIONMOTOR4_4_PIN_COIL1);
Adafruit_NeoPixel Strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUM_PIXELS, Pins[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[5], NEO_GRB + NEO_KHZ800)
};

const uint32_t Blue = Adafruit_NeoPixel::Color(10, 10, 255);
const uint32_t Pink = Adafruit_NeoPixel::Color(255, 0, 100);
const uint32_t Green = Adafruit_NeoPixel::Color(129, 237, 29);
const uint32_t Red = Adafruit_NeoPixel::Color(245, 21, 10);



unsigned long start;
unsigned long time;
unsigned long tmp;

boolean flag = true;

void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  // MsTimer2::set(3000, vibrate);        // 中断设置函数，每 500ms 进入一次中断
  // MsTimer2::start();                //开始计时
  //  for (int strip = 0; strip < NUM_STRIPS; strip++) {
  //    Strips[strip].begin();
  //    Strips[strip].show();
  //  }


  strip.begin();
  strip.show();
  //setAllStrips(Green);


}


void loop(void) {

  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!
  // LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
  // LED gets brighter the harder you press
  // fsrReading = analogRead(FSR_PIN_1);   Serial.println(fsrReading);
  float fsr_1Force = fsr_1.getForce();
  Serial.print(F("Force1: ")); Serial.print(fsr_1Force); Serial.println(F(" [g]"));
  float fsr_2Force = fsr_2.getForce();
  Serial.print(F("Force2: ")); Serial.print(fsr_2Force); Serial.println(F(" [g]"));
  //float fsr_3Force = fsr_3.getForce();
 // Serial.print(F("Force3: ")); Serial.print(fsr_3Force); Serial.println(F(" [g]"));
  float fsr_4Force = fsr_4.getForce();
  Serial.print(F("Force4: ")); Serial.print(fsr_4Force); Serial.println(F(" [g]"));
  float fsr_5Force = fsr_5.getForce();
  Serial.print(F("Force5: ")); Serial.print(fsr_5Force); Serial.println(F(" [g]"));
   float fsr_6Force = fsr_6.getForce();
     Serial.print(F("Force6: ")); Serial.print(fsr_6Force); Serial.println(F(" [g]"));

  Serial.print("Time:");  Serial.println(millis());
  //   //prints time since program started



  if ( fsr_1Force > 0 || fsr_2Force > 0 || fsr_4Force > 0 || fsr_5Force > 0 || fsr_6Force > 0)
  {
    
    Serial.flush();
    
    
    start = 0;
   Serial.print("Time:"); Serial.println(millis());
    setAllStrips(Green);

    position();
//   Serial.print("Time:"); Serial.println(time);
//    while (millis() - start > 10000 && millis() - start < 20000)
//    {
      delay(3000);
      Serial.print("Time:"); Serial.println(millis());
      crossFade(Green, Red, 10UL);
     // break;
  //  }

    if ( millis() - start == 40000)
    {    Serial.println("stand up 1");
   
      vibrationMotor2_2.on();     // 1. turns on
      delay(2000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
      vibrationMotor2_2.off();    // 3.turns off
       tmp=millis();
      //  vibrationMotor3_3.on();     // 1. turns on
      //  delay(5000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
      //  vibrationMotor3_3.off();
    }
  
 while (millis() -start >= 40000)
    {   Serial.print("Time:"); Serial.println(millis());
        Serial.println("stand up 2");
    
     setAllStrips(Red);
     
if(fsr_1Force <30 &&fsr_2Force <30 && fsr_4Force <30 && fsr_5Force <30  && fsr_6Force <30) {
      setAllStrips(0);
   start= millis();
      
      break;
    }
    }



    //
    //    MsTimer2::set(1000, vibrate); // 中断设置函数，每 500ms 进入一次中断
    //    MsTimer2::start();
    //    delay(3000);
    //    MsTimer2::stop();

    Serial.println("hi");
  }
  //    delay(3000);   //dyy: when people leave (without pressure, stop fading)
  //    crossFade(Red, Green, 10UL);
  //    Serial.println("hiagain");
  // fsrReading = 0;
  // setAllStrips(0);

  //     while(Serial.available()) {
  //    Serial.read();
  //    delay(1);

  // delay(100);

  else {
    Serial.println("illegal input!");
  }


  //analogWrite(Pins[NUM_STRIPS], crossFade);



  //delay(100);
}

void vibrate() {
  vibrationMotor1_1.on();     // 1. turns on
  delay(5000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
  //vibrationMotor1_1.off();    // 3. turns off
  //    delay(500);

  vibrationMotor2_2.on();     // 1. turns on
  delay(5000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
  //vibrationMotor2_2.off();    // 3. turns off

  vibrationMotor3_3.on();     // 1. turns on
  delay(5000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
  //vibrationMotor3_3.off();    // 3. turns off


  vibrationMotor4_4.on();     // 1. turns on
  delay(5000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
  //vibrationMotor4_4.off();    // 3. turns off

}


void position() {
  float fsr_1Force = fsr_1.getForce();
  Serial.print(F("Force1: ")); Serial.print(fsr_1Force); Serial.println(F(" [g]"));
  float fsr_2Force = fsr_2.getForce();
  Serial.print(F("Force2: ")); Serial.print(fsr_2Force); Serial.println(F(" [g]"));
 // float fsr_3Force = fsr_3.getForce();
  //Serial.print(F("Force3: ")); Serial.print(fsr_3Force); Serial.println(F(" [g]"));
  float fsr_4Force = fsr_4.getForce();
  Serial.print(F("Force4: ")); Serial.print(fsr_4Force); Serial.println(F(" [g]"));
  float fsr_5Force = fsr_5.getForce();
  Serial.print(F("Force5: ")); Serial.print(fsr_5Force); Serial.println(F(" [g]"));
  float fsr_6Force = fsr_6.getForce();
     Serial.print(F("Force6: ")); Serial.print(fsr_6Force); Serial.println(F(" [g]"));

  if ( fsr_1Force < 30 || fsr_2Force < 30 ||  fsr_4Force < 30 || fsr_5Force < 30 || fsr_6Force < 30)
  { vibrationMotor2_2.on();     // 1. turns on
    delay(1000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    vibrationMotor2_2.off();    // 3. turns off

      vibrationMotor3_3.on();     // 1. turns on
      delay(1000);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
      vibrationMotor3_3.off();
  }
}
void setAllStrips(const uint32_t color) {
  byte red = (color >> 16) & 0xff;
  byte green = (color >> 8) & 0xff;
  byte blue = color & 0xff;
  float fsr_1Force = fsr_1.getForce();
  Serial.print(F("Force1: ")); Serial.print(fsr_1Force); Serial.println(F(" [g]"));
  float fsr_2Force = fsr_2.getForce();
  Serial.print(F("Force2: ")); Serial.print(fsr_2Force); Serial.println(F(" [g]"));
  //float fsr_3Force = fsr_3.getForce();
  //Serial.print(F("Force3: ")); Serial.print(fsr_3Force); Serial.println(F(" [g]"));
  float fsr_4Force = fsr_4.getForce();
  Serial.print(F("Force4: ")); Serial.print(fsr_4Force); Serial.println(F(" [g]"));
  float fsr_5Force = fsr_5.getForce();
  Serial.print(F("Force5: ")); Serial.print(fsr_5Force); Serial.println(F(" [g]"));
 float fsr_6Force = fsr_6.getForce();
     Serial.print(F("Force6: ")); Serial.print(fsr_6Force); Serial.println(F(" [g]"));
//
 

  setAllStrips(red, green, blue);
 if (fsr_1Force < 30  &&fsr_2Force < 30  && fsr_4Force < 30 && fsr_5Force < 30  && fsr_6Force < 30)
  {
    setAllStrips(0);

   // break;
  }
 
}

void setAllStrips(byte red, byte green, byte blue) {
  //  // for each strip
  //  for (int strip = 0; strip < NUM_STRIPS; strip++) {
  //    // for each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    strip.setPixelColor(pixel, red, green, blue);
  }
  strip.show(); // Output to strip
  // }
}

void crossFade(const uint32_t startColor, const uint32_t endColor, unsigned long speed) {

  float fsr_1Force = fsr_1.getForce();
  Serial.print(F("Force1: ")); Serial.print(fsr_1Force); Serial.println(F(" [g]"));
  float fsr_2Force = fsr_2.getForce();
  Serial.print(F("Force2: ")); Serial.print(fsr_2Force); Serial.println(F(" [g]"));
 // float fsr_3Force = fsr_3.getForce();
  //Serial.print(F("Force3: ")); Serial.print(fsr_3Force); Serial.println(F(" [g]"));
  float fsr_4Force = fsr_4.getForce();
  Serial.print(F("Force4: ")); Serial.print(fsr_4Force); Serial.println(F(" [g]"));
  float fsr_5Force = fsr_5.getForce();
  Serial.print(F("Force5: ")); Serial.print(fsr_5Force); Serial.println(F(" [g]"));
   float fsr_6Force = fsr_6.getForce();
     Serial.print(F("Force6: ")); Serial.print(fsr_6Force); Serial.println(F(" [g]"));
  byte startRed = (startColor >> 16) & 0xff;
  byte startGreen = (startColor >> 8) & 0xff;
  byte startBlue = startColor & 0xff;

  byte endRed = (endColor >> 16) & 0xff;
  byte endGreen = (endColor >> 8) & 0xff;
  byte endBlue = endColor & 0xff;

  // for each step in the cross-fade
  for (int step = 0; step < 256; step++) {

   
    if (fsr_1Force <30  &&fsr_2Force <30  && fsr_4Force <30 && fsr_5Force <30 && fsr_6Force <30) {
      setAllStrips(0);

      break;
    }

    else {
   position();
      byte red = map(step, 0, 255, startRed, endRed);
      byte green = map(step, 0, 255, startGreen, endGreen);
      byte blue = map(step, 0, 255, startBlue, endBlue);
      setAllStrips(red, green, blue);

      delay(speed);
    }

  }
}
