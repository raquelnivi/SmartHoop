#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_

#define IR_00     16753245
#define IR_01     16736925
#define IR_02     16769565
#define IR_03     16720605
#define IR_04     16712445
#define IR_05     16761405
#define IR_06     16769055
#define IR_07     16754775
#define IR_08     16748655
#define IR_09     16738455
#define IR_10     16750695
#define IR_11     16756815
#define IR_12     16724175
#define IR_13     16718055
#define IR_14     16743045
#define IR_15     16716015
#define IR_16     16726215
#define IR_17     16734885
#define IR_18     16728765
#define IR_19     16730805
#define IR_20     16732845
#define IR_NULL   4294967295

void decreaseBrightness(){
  if((brightness-10)>0){
    brightness = brightness - 10;
  }  
}

void increaseBrightness(){
  if((brightness+10)<255){
    brightness = brightness + 10;
  }  
}

void generalSignalsController(uint32_t signal){
  switch(signal){
    case IR_NULL:
      break;    
    case IR_00:
      ledsOff = !ledsOff;
      break;
    case IR_01:
      decreaseBrightness();
      break;
    case IR_02:
      increaseBrightness();
      break;
    case IR_09:
      lightsMode = 0;
      totalMovingLeds = 2;
      autoCycle = true;
      movingLedDelay = 80;
      break;
    case IR_15:
      lightsMode = 0;
      totalMovingLeds = 0;
      autoCycle = false;
      movingLedDelay = 800;
      break;
    case IR_16:
      lightsMode = 1;
      break;
    case IR_18:
      lightsMode = 2;
      autoCycle = false;
      movingLedDelay = 800;
      break;
    case IR_19:
      lightsMode = 3;
      autoCycle = true;
      movingLedDelay = 800;
      break;
    case IR_20:
      lightsMode = 4;
      autoCycle = true;
      movingLedDelay = 80;      
      break;
  }
}

void previousChaserColor(){
  if((chaserIndex-1)<0){
    chaserIndex=NUM_COLORS-1;
    }
  else{
    chaserIndex--;
    }
  if(chaserIndex==colorIndex){
    if((chaserIndex-1)<0){
      chaserIndex=NUM_COLORS-1;
      }
    else{
      chaserIndex--;
      }
  }  
}

void nextChaserColor(){
  if((chaserIndex+1)>=NUM_COLORS){
    chaserIndex=0;
    }
  else{
    chaserIndex++;
    }
  if(chaserIndex==colorIndex){
    if((chaserIndex+1)>=NUM_COLORS){
      chaserIndex=0;
      }
    else{
      chaserIndex++;
      }
  }
}

void decreaseChasers(){
  if((totalMovingLeds-1)>0){
    totalMovingLeds = totalMovingLeds - 1;
  }  
}

void increaseChasers(){
  if((totalMovingLeds+1)<NUM_LEDS){
    totalMovingLeds = totalMovingLeds + 1;
  }  
}

void previousBackground(){
  if((colorIndex+1)>=NUM_COLORS){
    colorIndex=0;
    }
  else{
    colorIndex++;
    }
  if(chaserIndex==colorIndex){
    nextChaserColor();
  }
}

void nextBackground(){
  if((colorIndex-1)<0){
    colorIndex=NUM_COLORS-1;
    }
  else{
    colorIndex--;
    }
  if(chaserIndex==colorIndex){
    nextChaserColor();
  }
}

void randomBackground(){
  colorIndex = random(0,(NUM_COLORS-1));
  if(chaserIndex==colorIndex){
    nextChaserColor();
  }
}

void previousImage(){
  if((imageIndex+1)>=NUM_IMAGES){
    imageIndex=0;
    }
  else{
    imageIndex++;
    }
}

void nextImage(){
  if((imageIndex-1)<0){
    imageIndex=NUM_IMAGES-1;
    }
  else{
    imageIndex--;
    }
}

void randomImage(){
  imageIndex = random(0,(NUM_IMAGES-1));
}

void previousPalette(){
  if((paletteIndex+1)>=NUM_PALETTES){
    paletteIndex=0;
    }
  else{
    paletteIndex++;
    }
}

void nextPalette(){
  if((paletteIndex-1)<0){
    paletteIndex=NUM_PALETTES-1;
    }
  else{
    paletteIndex--;
    }
}

void randomPalette(){
  paletteIndex = random(0,(NUM_PALETTES-1));
}

void decreaseDelay(){
  if((movingLedDelay-10)>0){
    movingLedDelay = movingLedDelay - 10;
  }  
}

void increaseDelay(){
  if((movingLedDelay+10)<7000){
    movingLedDelay = movingLedDelay + 10;
  }
}

void changeDirections(){
  forwards = !forwards;  
}

void applyChaserMode(uint32_t signal){
  switch (signal){
    case IR_03:
      autoCycle = !autoCycle;
      break;    
    case IR_04:
      previousBackground();
      break;                                 
    case IR_05:
      nextBackground();
      break;    
    case IR_06:
      increaseDelay();
      break;    
    case IR_07:
      decreaseDelay();
      break;  
    case IR_08:
      changeDirections();
      break;      
    case IR_10:
      previousChaserColor();
      break;  
    case IR_11:
      nextChaserColor();
      break;  
    case IR_13:
      decreaseChasers();      
      break;  
    case IR_14:
      increaseChasers();      
      break;                 
  }                  
}

void applySolidColorMode(uint32_t signal){
  totalMovingLeds = 0;
  switch (signal){
    case IR_03:
      autoCycle = !autoCycle;
      break;    
    case IR_04:
      previousBackground();
      break;                                 
    case IR_05:
      nextBackground();
      break;    
    case IR_06:
      decreaseDelay();
      break;    
    case IR_07:
      increaseDelay();
      break;    
    case IR_17:
      randomBackground();
      break;    
  }        
}

void applyImagesMode(uint32_t signal){
  Serial.println("Images mode");
  switch (signal){
    case IR_03:
      Serial.println("Toggle auto cycle");
      autoCycle = !autoCycle;
      break;    
    case IR_04:
      Serial.println("Previous image");
      previousImage();
      break;                                 
    case IR_05:
      Serial.println("Next image");
      nextImage();
      break;    
    case IR_06:
      Serial.println("Decrease cycle time");
      decreaseDelay();
      break;    
    case IR_07:
      Serial.println("Increase cycle time");
      increaseDelay();
      break;    
    case IR_17:
      Serial.println("Show random image");
      randomImage();
      break;    
  }           
}

void applyGradientMode(uint32_t signal){
  switch (signal){    
    case IR_03:
      autoCycle = !autoCycle;
      break;    
    case IR_04:
      previousBackground();
      break;                                 
    case IR_05:
      nextBackground();
      break;         
    case IR_06:
      decreaseDelay();
      break;    
    case IR_07:
      increaseDelay();
      break;         
    // case IR_08:
    //   changeDirections();
    //   break;      
    case IR_10:
      previousChaserColor();
      break;  
    case IR_11:
      nextChaserColor();
      break;       
    case IR_17:
      randomBackground();
      break;         
  }  
}

void applyPaletteMode(uint32_t signal){
  switch (signal){    
    case IR_03:
      autoCycle = !autoCycle;
      break;    
    case IR_04:
      previousPalette();
      break;                                 
    case IR_05:
      nextPalette();
      break;         
    // case IR_08:
    //   changeDirections();
    //   break;
    case IR_06:
      decreaseDelay();
      break;    
    case IR_07:
      increaseDelay();
      break;     
    case IR_17:
      randomPalette();
      break;         
  } 
}

void applyRainbowMode(uint32_t signal){
  switch (signal){    
    case IR_03:
      autoCycle = !autoCycle;
      break;    
    case IR_08:
      changeDirections();
      break;
    case IR_06:
      decreaseDelay();
      break;    
    case IR_07:
      increaseDelay();
      break;     
  }      
}

void modeSpecificSignalsController(uint32_t signal){
  switch(lightsMode){
    case 0:
      if(totalMovingLeds==0){
        applySolidColorMode(signal);        
      }   
      else{
        applyChaserMode(signal);
      }
      break;
    case 1:
      applyImagesMode(signal);
      break;
    case 2:
      applyGradientMode(signal);
      break;    
    case 3:
      applyPaletteMode(signal);
      break;
    case 4:
      applyRainbowMode(signal);
      break;        
  }
}

#endif
