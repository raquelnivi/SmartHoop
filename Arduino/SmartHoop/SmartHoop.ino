#include <FastLED.h>
#include <IRLibRecv.h>
#include <IRLibDecodeBase.h>
#include <IRLib_P01_NEC.h>

#define NUM_LEDS     6
#define DATA_PIN     4
#define CLOCK_PIN    3
#define IR_PIN       0

#include "PalettesAndColors.h"
#include "Images.h"

IRrecv irReceiver(IR_PIN);
IRdecodeNEC remoteDecoder;

CRGB leds[NUM_LEDS];
CRGB boardLed[1];
CRGB black =  CRGB(0,0,0);

int lightsMode = 0; //0:Color, 1:Images, 2:Gradient, 3:Palette, 4:Rainbow
int brightness = 30;
int colorIndex = 0;
int chaserIndex = 1;
int imageIndex = 0;
int paletteIndex = 0;
int totalMovingLeds = 0;
int leadingLedIndex = 0;
long movingLedDelay = 80;
long lastMovingTime = 0;
float deltaHue = 255/NUM_LEDS;
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
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
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
    if(movingLedIndex-1<0){
      movingLedIndex = NUM_LEDS-1;
    }    
    else{
      movingLedIndex = movingLedIndex - 1;         
    }                   
    leds[movingLedIndex] = colors[chaserIndex];
  }    
  if(autoCycle){
    leadingLedIndex++;
    if(leadingLedIndex>=NUM_LEDS){
      leadingLedIndex = 0;
    }     
  }
}

void moveChaserBackwards(){
  int movingLedIndex = leadingLedIndex;  
  for(int movingLed=0;movingLed<totalMovingLeds;movingLed++){
    if(movingLedIndex+1>NUM_LEDS-1){
      movingLedIndex = 0;
    }    
    else{
      movingLedIndex = movingLedIndex + 1;         
    }                   
    leds[movingLedIndex] = colors[chaserIndex];
  }  
  if(autoCycle){
    leadingLedIndex--;
    if(leadingLedIndex<0){
      leadingLedIndex = NUM_LEDS-1;
    }    
  }      
}

void moveGradient(){
  if(autoCycle){
    chaserIndex = random(0,(NUM_COLORS-1));
  }
}

void moveForwards(){
  if(autoCycle){
    leadingLedIndex++;
    if(leadingLedIndex>=NUM_LEDS){
      leadingLedIndex = 0;
    }    
  }
}

void moveBackwards(){
  if(autoCycle){
    leadingLedIndex--;
    if(leadingLedIndex<0){
      leadingLedIndex = NUM_LEDS-1;
    }       
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
  else if((millis()-lastMovingTime)>movingLedDelay){   
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

void showGradient(){
  fill_gradient_RGB(leds, NUM_LEDS, colors[colorIndex], colors[chaserIndex], colors[chaserIndex], colors[colorIndex]);
  if(((millis()-lastMovingTime)>movingLedDelay) && autoCycle){   
    moveGradient();
    lastMovingTime = millis(); 
  }  
}

void showPalette(){
  if(((millis()-lastMovingTime)>movingLedDelay) && autoCycle){   
    int firstColor = leadingLedIndex*(255/NUM_LEDS);
    fill_palette(leds, NUM_LEDS, leadingLedIndex, 255/NUM_LEDS, palettes[chaserIndex], chaserIndex, LINEARBLEND);  
    if(forwards){
      moveForwards();
    }
    else{
      moveBackwards();
    }
    lastMovingTime = millis(); 
  }    
}

void showRainbow(){
  if(((millis()-lastMovingTime)>movingLedDelay) && autoCycle){   
    int firstColor = leadingLedIndex*(255/NUM_LEDS);
    fill_rainbow(leds, NUM_LEDS, firstColor, 255/NUM_LEDS);    
    if(forwards){
      moveForwards();
    }
    else{
      moveBackwards();
    }
    lastMovingTime = millis(); 
  }  
}

void lightLeds(){
  if(lightsMode==0){
    showColors();
  }
  if(lightsMode==2){
    showGradient();    
  }
  if(lightsMode==3){
    showPalette();    
  }
  if(lightsMode==4){
    showRainbow();    
  }
}

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
    lightLeds();
  }
  FastLED.show();
  irReceiver.enableIRIn();  
}
