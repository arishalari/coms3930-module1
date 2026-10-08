#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

int frame = 0;

int chrysalisX = 195;
int chrysalisY = 58;

void setup() {
  tft.init();
  tft.setRotation(1);
  spr.createSprite(240, 135);
}

void loop() {
  spr.fillSprite(tft.color565(135, 206, 235));
  spr.fillRect(0, 118, 240, 17, tft.color565(150, 200, 120));

  // Branch
  spr.fillRect(165, 2, 75, 19, tft.color565(110, 80, 55));
    spr.drawWideLine(167, 11, 140, 26, 17, tft.color565(110, 80, 55));

  // Caterpillar
  if (frame < 300) {
    int headX = -45 + frame * 4 / 5;

    int bounce = 0;
    if (frame % 20 < 10) {
      bounce = 4;
    }

    spr.fillCircle(headX - 36, 110,          7, tft.color565(110, 190, 90));
    spr.fillCircle(headX - 24, 110 - bounce, 7, tft.color565(110, 190, 90));
    spr.fillCircle(headX - 12, 110,          7, tft.color565(110, 190, 90));
    spr.fillCircle(headX,      110 - bounce, 8, tft.color565(60, 140, 60));
    spr.fillCircle(headX + 3, 107 - bounce, 3, TFT_WHITE);
    spr.fillCircle(headX + 4, 107 - bounce, 1, TFT_BLACK);
  }

  //Chrysalis
  else if (frame < 600) {
    spr.drawLine(chrysalisX, 21, chrysalisX, chrysalisY - 18, tft.color565(110, 80, 55));

    if (frame < 450) {
      spr.fillEllipse(chrysalisX, chrysalisY, 9, 19, tft.color565(110, 190, 90));
    } else {
      spr.fillEllipse(chrysalisX, chrysalisY, 9, 19, tft.color565(90, 55, 35));
    }
  }

  // Butterfly
  else {
    int framesFlying = frame - 600;
    int butterflyX = chrysalisX - framesFlying / 3;
    int butterflyY = chrysalisY - framesFlying / 3;

    int wingWidth = 6;
    if (frame % 16 < 8) {
      wingWidth = 22;
    }
    int lowerWingWidth = wingWidth * 3 / 4;

    // empty chrysalis shell
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
    frame = 0;
  }
  delay(20);
}
