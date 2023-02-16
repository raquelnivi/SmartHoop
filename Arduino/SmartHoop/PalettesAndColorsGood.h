#ifndef PALETTESANDCOLORS_H_
#define PALETTESANDCOLORS_H_

DEFINE_GRADIENT_PALETTE(heatmap_gp){
  0,0,0,0,
  128,255,0,0,
  200,255,255,0,
  255,255,255,NUM_LEDS
};

DEFINE_GRADIENT_PALETTE(sunset_real){
  191,  0,  0, 0,
  223, 85,  0, int(9*NUM_LEDS/100),
  255,170,  0, int(21*NUM_LEDS/100),
  217, 85, 89, int(34*NUM_LEDS/100),
  178,  0,178, int(53*NUM_LEDS/100),
   89,  0,195, int(78*NUM_LEDS/100),
    0,  0,212, NUM_LEDS  
};

CRGBPalette16 firstPalette = heatmap_gp;

CRGBPalette16 purplePalette = CRGBPalette16 {
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::Magenta,

  CRGB::Magenta,
  CRGB::Linen,
  CRGB::Linen,
  CRGB::Magenta,

  CRGB::Magenta,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,

  CRGB::DarkViolet,
  CRGB::Linen,
  CRGB::Linen,
  CRGB::DarkViolet
};

const CRGBPalette16 palettes[] PROGMEM = {
  purplePalette,
  firstPalette,
  sunset_real
};

const CRGB colors[] PROGMEM = {
  CRGB::White, CRGB::Red, CRGB::Purple, CRGB::Blue, CRGB::Green,
  CRGB::Yellow, CRGB::Orange, CRGB::Pink, CRGB::Teal,
  CRGB::Magenta, CRGB::LimeGreen, CRGB::HotPink, CRGB::SeaGreen
};

#define NUM_PALETTES (sizeof(palettes) / sizeof(palettes[0]))
#define NUM_COLORS (sizeof(colors) / sizeof(colors[0]))

#endif