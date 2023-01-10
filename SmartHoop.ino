#include <FastLED.h>
#include <IRLibRecv.h>
#include <IRLibDecodeBase.h>
#include <IRLib_P01_NEC.h>

#define NUM_LEDS     6
#define DATA_PIN     4
#define CLOCK_PIN    3
#define IR_PIN       0

IRrecv irReceiver(IR_PIN);
IRdecodeNEC remoteDecoder;

CRGB leds[NUM_LEDS];
CRGB boardLed[1];

CRGB black =  CRGB(0,0,0);

const CRGB colors[] PROGMEM = {
  CRGB::White, CRGB::Red, CRGB::Purple, CRGB::Blue, CRGB::Green,
  CRGB::Yellow, CRGB::Orange, CRGB::Pink, CRGB::Teal,
  CRGB::Magenta, CRGB::LimeGreen, CRGB::HotPink, CRGB::SeaGreen
};
#define NUM_COLORS (sizeof(colors) / sizeof(colors[0]))

#define NUM_IMAGES 30

int mode = 0; //0:Color, 1:Images, 2:Gradient, 3:Palette, 4:Rainbow
int brightness = 30;
int colorIndex = 0;
int chaserIndex = 1;
int imageIndex = 0;
int totalMovingLeds = 0;
int leadingLedIndex = 0;
long movingLedDelay = 80;
long lastMovingTime = 0;
bool ledsOff = true;
bool forwards = true;
bool autoCycle = false;

#include "RemoteControl.h"

void setUpBoardLed(){
  FastLED.addLeds<APA102, INTERNAL_DS_DATA, INTERNAL_DS_CLK, BGR>(boardLed, 1);  
  fill_solid(boardLed, 1, black);
}

void setUpStrip(){
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, colors[colorIndex]);
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void setup(){
  irReceiver.enableIRIn();
  setUpBoardLed();
  setUpStrip();
}

void moveChaserForwards(){
  int movingLedIndex = leadingLedIndex;  
  for(int movingLed=0;movingLed<totalMovingLeds;movingLed++){
    if((movingLedIndex-1<0)){
      movingLedIndex = NUM_LEDS-1;
    }    
    else{
      movingLedIndex = movingLedIndex - 1;         
    }                   
    leds[movingLedIndex] = colors[chaserIndex];
  }    
  leadingLedIndex++;
  if(leadingLedIndex>=NUM_LEDS){
    leadingLedIndex = 0;
  }        
}

void moveChaserBackwards(){
  int movingLedIndex = leadingLedIndex;  
  for(int movingLed=0;movingLed<totalMovingLeds;movingLed++){
    if((movingLedIndex+1>NUM_LEDS-1)){
      movingLedIndex = 0;
    }    
    else{
      movingLedIndex = movingLedIndex + 1;         
    }                   
    leds[movingLedIndex] = colors[chaserIndex];
  }    
  leadingLedIndex--;
  if(leadingLedIndex<0){
    leadingLedIndex = NUM_LEDS-1;
  }        
}

void showColors(){
  if(totalMovingLeds==0){
    if(((millis()-lastMovingTime)>movingLedDelay) && autoCycle){
      nextBackground();  
      lastMovingTime = millis(); 
    }
    fill_solid(leds, NUM_LEDS, colors[colorIndex]);
  }
  else if(((millis()-lastMovingTime)>movingLedDelay) && autoCycle){   
    fill_solid(leds, NUM_LEDS, colors[colorIndex]);
    if(forwards){
      moveChaserForwards();
    }
    else{
      moveChaserBackwards();
    }
    lastMovingTime = millis(); 
  }
}

// quan pausem el chaser mode no veiem els canvis de color!!!
void loop(){  
  if(irReceiver.getResults()){
    remoteDecoder.decode();
    generalSignalsController(remoteDecoder.value);
    modeSpecificSignalsController(remoteDecoder.value);
    FastLED.setBrightness(brightness);
  }
  if(ledsOff){
    fill_solid(leds, NUM_LEDS, black);
  }
  else{
    showColors();
  }
  FastLED.show();
  irReceiver.enableIRIn();  
}
