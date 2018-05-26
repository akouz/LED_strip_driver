// Board: Arduino Mini Pro
// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

// ####################################################################
// Inc
// ####################################################################

#include <FastLED.h>
#include "coos.h"

// ####################################################################
// Def
// ####################################################################

#define GLED        10  // green LED
#define RELAY       3   // relay output - it powers on LED strip
#define RGB_PIN     11  // SPI - LED strip control

#define NUM_LEDS    120
#define BRIGHTNESS  70

#define LED_TYPE    WS2811

//#define COLOR_ORDER GRB
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define LED_UPDATE_RATE   15  // ms, must be in the range 10...85

#define PATTERN_DURATION  20  // sec

#define PHOTO_THRESHOLD   50
#define RUN_TIME          4   // hours
#define DARK_CNT_LIM      30  // sec

// ####################################################################
// Var
// ####################################################################

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

uint run_time_cnt; 
uint sec_cnt;

uchar dark = 1;
uint dark_cnt = DARK_CNT_LIM + 3;

uchar dir = 0;
uchar rate;

int PhotoPin = A0;  // photosensor - 1M photoresistor to Vcc at A0
int PhotoVal = 0;

// ####################################################################
// Func
// ####################################################################

// ================================
// All LEDs black
// ================================
void LedsBlack(void)
{
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
}

// ================================
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) 
    {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

// ================================
// There are several different palettes of colors demonstrated here.
// ================================
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    static uint16_t sm;
    if (sec_cnt >= PATTERN_DURATION)
    {
      sec_cnt = 0;
      dir = random8() & 1;
      rate = random8(LED_UPDATE_RATE, 3*LED_UPDATE_RATE);
      sm++;
      Serial.print(sm);
      Serial.print(". ");
      currentBlending = LINEARBLEND;  
      switch(sm)
      {
        case 0: 
          currentPalette = RainbowStripeColors_p;    
          Serial.print("RainbowStripeColors_p");
          break;
        case 1: 
          SetupRandomPalette();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 2: 
          currentPalette = RainbowStripeColors_p;    
          Serial.print("RainbowStripeColors_p");
          break;
        case 3: 
          SetupPurpleAndGreenPalette();              
          Serial.print("SetupPurpleAndGreenPalette()");
          break;
        case 4: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 5: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 6: 
          SetupBlackAndWhiteStripedPalette();        
          Serial.print("SetupBlackAndWhiteStripedPalette()");
          break;
        case 7: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 8: 
          currentPalette = RainbowStripeColors_p;    
          Serial.print("RainbowStripeColors_p");
          break;
        case 9: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 10: 
          currentPalette = myRedWhiteBluePalette_p; 
          Serial.print("myRedWhiteBluePalette_p");
          break;
        case 11: 
          SetupRandomPalette();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 12: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 13: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 14: 
          SetupBlackAndWhiteStripedPalette();       
          Serial.print("SetupBlackAndWhiteStripedPalette()");
          break;
        case 15: 
          currentPalette = ForestColors_p;          
          Serial.print("ForestColors_p");
          break;
        case 16: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 17: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 18: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 19: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 20: 
          SetupRandomPalette2();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 21: 
          SetupRandomPalette();                      
          Serial.print("SetupRandomPalette()");
          break;
        case 22: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 23: 
          SetupRandomPalette();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 24: 
          SetupRandomPalette2();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 25: 
          SetupRandomPalette();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 26: 
          currentPalette = RainbowStripeColors_p;    
          Serial.print("RainbowStripeColors_p");
          break;
        case 27: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 28: 
          SetupRandomPalette();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 29:  
          SetupRandomPalette2();                     
          Serial.print("SetupRandomPalette()");
          break;
        case 30: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        case 31:  
          SetupRandomPalette();               
          Serial.print("SetupTotallyRandomPalette()");
          break;
        default: 
          SetupTotallyRandomPalette();               
          Serial.print("SetupRandomPalette()");
          sm = 0;
          break;
      }
      Serial.print(", photo=");
      Serial.println(PhotoVal);
    }
}

// ================================
// This function fills the palette with totally random colors.
// ================================
void SetupTotallyRandomPalette()
{
    fill_solid( currentPalette, 16, CRGB::Black);
    for( int i = 0; i < 16; i=i+2) 
    {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// ================================
// This function fills the palette with random colors.
// ================================
void SetupRandomPalette()
{
   fill_solid( currentPalette, 16, CRGB::Black);
   currentPalette[0] = CHSV( random8(), 255, 64);
   currentPalette[2] = CHSV( random8(), 128, 255);
   currentPalette[4] = CHSV( random8(), 255, 128);
   currentPalette[5] = CHSV( random8(), 192, 255);
   currentPalette[7] = CHSV( random8(), 255, 128);
   currentPalette[9] = CHSV( random8(), 128, 255);
   currentPalette[10] = CHSV( random8(), 255, random8());
   currentPalette[12] = CHSV( random8(), 192, 32);
   currentPalette[14] = CHSV( random8(), 128, 255);
}

// ================================
// This function fills the palette with random colors.
// ================================
void SetupRandomPalette2()
{
   fill_solid( currentPalette, 16, CRGB::Black);
   currentPalette[0] = CHSV( random8(), 255, 64);
   currentPalette[2] = CHSV( random8(), 128, 255);
   currentPalette[3] = CHSV( random8(), 255, 128);
   currentPalette[5] = CHSV( random8(), 192, 255);
   currentPalette[7] = CHSV( random8(), 255, 128);
   currentPalette[9] = CHSV( random8(), 128, 255);
   currentPalette[10] = CHSV( random8(), 255, 128);
   currentPalette[12] = CHSV( random8(), 192, 32);
   currentPalette[14] = CHSV( random8(), 128, 255);
}

// ================================
// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
// ================================
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::Yellow;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::Green;   
}

// ================================
// This function sets up a palette of purple and green stripes.
// ================================
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// ================================
// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
// ================================
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Black,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Black,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Black,
    CRGB::Red,
    CRGB::Black,
    CRGB::Gray,

    CRGB::Black,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Red
};

// ================================
// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

// =================================
// Task 0 : Control RGB strip
// =================================
void coos_task0(void)
{
  static uint8_t startIndex = 0;
  run_time_cnt = 0;
  sec_cnt = (PATTERN_DURATION >> 1);
  rate = 2*LED_UPDATE_RATE;
  COOS_DELAY(1000); // power-up safety delay    
  FastLED.addLeds<LED_TYPE, RGB_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );  
  SetupRandomPalette();
  currentBlending = LINEARBLEND;
  while(1)
  {
    COOS_DELAY(rate);    
    FastLED.show();
    // ----------------------------
    // Night time
    // ----------------------------
    if (dark)
    {
      if (run_time_cnt < RUN_TIME*3600) // 
      {        
        digitalWrite(RELAY,HIGH);
        ChangePalettePeriodically();
        if (dir)
        {
          startIndex = startIndex + 1; /* motion speed */
        }
        else
        {
          if (startIndex)
            startIndex--;
          else
            startIndex = 0xFF;   
        }
        FillLEDsFromPaletteColors( startIndex);
      }
      else
      {
        LedsBlack();
        digitalWrite(RELAY,LOW);
        dark |= 2;
        COOS_DELAY(1000);
      }
    }
    // ----------------------------
    // Daytime
    // ----------------------------
    else 
    {
      if (run_time_cnt)
      {
        run_time_cnt = 0;
        LedsBlack();
      }
      digitalWrite(RELAY,LOW);
      COOS_DELAY(100);
    }
  }
}
// =================================
// Task 1: Debug
// =================================
void coos_task1(void)
{
  static uchar cnt = 0;
  while(1)
  {
    if (dark)
    {
        cnt = 0;
    }
    else
    {
      Serial.print("."); 
      if (++cnt > 15)
      {
        Serial.println();
        cnt = 0;    
      }
    }
    COOS_DELAY(1000);
  }
}
// =================================
// Task 2: Photo sensor and time
// =================================
void coos_task2(void)
{
  uint thr;
  run_time_cnt = 0;  
  while(1)
  {
    // ------------------------
    // Photo sensor
    // ------------------------
    PhotoVal = analogRead(PhotoPin);
//    Serial.print("Photo = ");
//    Serial.println(PhotoVal);
    if (dark) 
      thr = 2*PHOTO_THRESHOLD;
    else
      thr = PHOTO_THRESHOLD;
    // ------------------------
    // Grace
    // ------------------------
    if (PhotoVal < thr)
    {
      if (dark_cnt < 3*DARK_CNT_LIM)
        dark_cnt++;
    }
    else if (dark_cnt)
    {
       dark_cnt--;
    }
    if (dark_cnt >= 2*DARK_CNT_LIM)
    {
      if (dark == 0)
      {
        digitalWrite(RELAY, HIGH);
        digitalWrite(GLED, HIGH);
        COOS_DELAY(10);  
        LedsBlack();
        run_time_cnt = 0;
      }
      dark = 1;
    }
    else if (dark_cnt < DARK_CNT_LIM)
    {
      dark = 0;      
      digitalWrite(RELAY, LOW);
      digitalWrite(GLED, LOW);
    }
    // ------------------------
    // Run time
    // ------------------------
    COOS_DELAY(1000);  
    sec_cnt++;    
    if (run_time_cnt < 0xFFFF)
    {
      run_time_cnt++;
    }
  }
}   
// ================================================================
// Setup
// ================================================================
void setup() 
{
  Serial.begin(57600);

  Serial.println();
  Serial.println("Port init");
  pinMode(GLED, OUTPUT);
  pinMode(RELAY, OUTPUT);

  // unused pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.println("Task init");
  coos.register_task(coos_task0);
  coos.register_task(coos_task1);
  coos.register_task(coos_task2);
}

// ================================================================
// Loop
// ================================================================
void loop()
{ 
    static uint8_t startIndex = 0;
    uint16_t cnt;

    // --------------------------------------------
    // COOS scheduler
    // --------------------------------------------
    while(1)
    {    
       coos.run_scheduler();  // Coos scheduler is an endless loop itself
    }
}

/* EOF */
