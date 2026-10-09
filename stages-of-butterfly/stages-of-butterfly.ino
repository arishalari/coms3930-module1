/*
  Transitions: Caterpillar to Butterfly
  ESP32 TTGO T-Display, landscape (240x135).

  A counter called "frame" goes up by 1 every time loop() runs.
    frame 0-299   : caterpillar crawls in from the left
    frame 300-599 : chrysalis hangs from the branch (green, then dark brown)
    frame 600-899 : butterfly comes out, flaps, and flies off the top
  At frame 900 the counter goes back to 0 and the story starts over.
*/

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
// hidden canvas, so drawing doesn't flicker
TFT_eSprite spr = TFT_eSprite(&tft);

// counts how many frames have been drawn
int frame = 0;

// Where the chrysalis hangs
int chrysalisX = 195;
int chrysalisY = 58;

void setup() {
  tft.init();
  // landscape (use 3 if it looks upside down)
  tft.setRotation(1);
  // canvas the same size as the screen
  spr.createSprite(240, 135);
}

void loop() {
  //Background
  spr.fillSprite(tft.color565(135, 206, 235));
  spr.fillRect(0, 118, 240, 17, tft.color565(150, 200, 120));

  //Branch
  spr.fillRect(165, 2, 75, 19, tft.color565(110, 80, 55));
  spr.drawWideLine(167, 11, 140, 26, 17, tft.color565(110, 80, 55));

  //Stage 1: caterpillar 
  if (frame < 300) {
    int headX = -45 + frame * 4 / 5;   

    int bounce = 0;
    if (frame % 20 < 10) { 
      bounce = 4;
    }

    // body segments, tail to head
    spr.fillCircle(headX - 36, 110,          7, tft.color565(110, 190, 90));
    spr.fillCircle(headX - 24, 110 - bounce, 7, tft.color565(110, 190, 90));
    spr.fillCircle(headX - 12, 110,          7, tft.color565(110, 190, 90));
    spr.fillCircle(headX,      110 - bounce, 8, tft.color565(60, 140, 60));
    spr.fillCircle(headX + 3, 107 - bounce, 3, TFT_WHITE); 
    spr.fillCircle(headX + 4, 107 - bounce, 1, TFT_BLACK);
  }

  //Stage 2: chrysalis
  else if (frame < 600) {
    // thread hanging from the branch
    spr.drawLine(chrysalisX, 21, chrysalisX, chrysalisY - 18, tft.color565(110, 80, 55));

    if (frame < 450) {
      spr.fillEllipse(chrysalisX, chrysalisY, 9, 19, tft.color565(110, 190, 90));
    } else {
      spr.fillEllipse(chrysalisX, chrysalisY, 9, 19, tft.color565(90, 55, 35));
    }
  }

  //Stage 3: butterfly
  else {
    int framesFlying = frame - 600;
    int butterflyX = chrysalisX - framesFlying / 3;
    int butterflyY = chrysalisY - framesFlying / 3;

    int wingWidth = 6;
    if (frame % 16 < 8) {
      wingWidth = 22;
    }
    int lowerWingWidth = wingWidth * 3 / 4;

    // empty chrysalis shell left behind on the branch
    spr.drawLine(chrysalisX, 21, chrysalisX, chrysalisY - 18, tft.color565(110, 80, 55));
    spr.fillEllipse(chrysalisX, chrysalisY, 9, 19, tft.color565(225, 215, 190));

    // lower wings
    spr.fillEllipse(butterflyX - lowerWingWidth, butterflyY + 14, lowerWingWidth, 12, TFT_BLACK);
    spr.fillEllipse(butterflyX - lowerWingWidth, butterflyY + 14, lowerWingWidth - 2, 9, tft.color565(255, 69, 0));
    spr.fillEllipse(butterflyX + lowerWingWidth, butterflyY + 14, lowerWingWidth, 12, TFT_BLACK);
    spr.fillEllipse(butterflyX + lowerWingWidth, butterflyY + 14, lowerWingWidth - 2, 9, tft.color565(255, 69, 0));

    // upper wings
    spr.fillEllipse(butterflyX - wingWidth, butterflyY - 6, wingWidth, 18, TFT_BLACK);
    spr.fillEllipse(butterflyX - wingWidth, butterflyY - 6, wingWidth - 2, 15, tft.color565(255, 69, 0));
    spr.fillEllipse(butterflyX + wingWidth, butterflyY - 6, wingWidth, 18, TFT_BLACK);
    spr.fillEllipse(butterflyX + wingWidth, butterflyY - 6, wingWidth - 2, 15, tft.color565(255, 69, 0));

    // body and antennae
    spr.fillEllipse(butterflyX, butterflyY, 3, 15, TFT_BLACK);
    spr.drawLine(butterflyX, butterflyY - 14, butterflyX - 6, butterflyY - 24, TFT_BLACK);
    spr.drawLine(butterflyX, butterflyY - 14, butterflyX + 6, butterflyY - 24, TFT_BLACK);
  }

  spr.pushSprite(0, 0);

  frame = frame + 1;
  if (frame >= 900) {
    // start the story over
    frame = 0;
  }
  // small pause between frames (smaller = faster)
  delay(20);                          
}
