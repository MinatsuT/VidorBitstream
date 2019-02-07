#include "VidorGraphics.h"
#include "Vidor_GFX.h"

Vidor_GFX  vdgfx;

#define SW 640
#define SH 480
#define SX (SW-1)
#define SY (SH-1)

void setup() {
  Serial.begin(9600);

  // wait for the serial monitor to open,
  // if you are powering the board from a USB charger remove the next line
  //while (!Serial);

  // Initialize the FPGA
  if (!FPGA.begin()) {
    Serial.println("Initialization failed!");
    while (1) {}
  }

  vdgfx.begin();
}

void loop()
{
  /**
     Draw an Arduino logo
  */

  // Fill the screen with a white background
  //vdgfx.fillRect(0,0,640,480,vdgfx.White());

  /**
     The library allows drawing some basic elements to the view, like circles, rectangles, lines
  */

  vdgfx.fillCircle(225, 225, 100 , vdgfx.lightBlue());
  vdgfx.fillCircle(415, 225, 100 , vdgfx.lightBlue());
  vdgfx.fillCircle(225, 225, 90 , vdgfx.White());
  vdgfx.fillCircle(415, 225, 90 , vdgfx.White());
  vdgfx.fillRect(175, 220, 100, 10 , vdgfx.lightBlue());
  vdgfx.fillRect(365, 220, 100, 10 , vdgfx.lightBlue());
  vdgfx.fillRect(410, 175, 10, 100 , vdgfx.lightBlue());

  /**
     To draw a text we can use the classic functions like write() and print()
     Text size, color and position can be changed using the .text subclass
  */
  vdgfx.text.setFont(0);
  vdgfx.text.setCursor(150,375);
  vdgfx.text.setAlpha(255);
  vdgfx.text.setSize(7);
  vdgfx.text.setColor(vdgfx.lightBlue());
  vdgfx.println("ARDUINO");
  vdgfx.text.setCursor(480,145);
  vdgfx.text.setSize(3);
  vdgfx.println("TM");

  LineArt();
}

#define N 100
#define M 10
static int hx[N][2], hy[N][2];
static int x[2], y[2];
static int vx[2], vy[2];

void LineArt() {
  int i, j;

  for (j = 0; j < N; j++) {
    for (i = 0; i < 2; i++) {
      hx[j][i] = hy[j][i] = 0;
    }
  }

 randomSeed(analogRead(0));
  for (i = 0; i < 2; i++) {
    x[i] = random(10, SW - 10);
    y[i] = random(10, SH - 10);
    vx[i] = (random(2) * 2 - 1) * 2;
    vy[i] = (random(2) * 2 - 1) * 2;
  }

  while (1) {
    drawLines(vdgfx.White());
    for (i = 0; i < 2; i++) {
      x[i] += vx[i];
      y[i] += vy[i];
      vx[i] = (x[i] >= SX || x[i] <= 0) ? -vx[i] : vx[i];
      vy[i] = (y[i] >= SY || y[i] <= 0) ? -vy[i] : vy[i];
      hx[0][i] = x[i];
      hy[0][i] = y[i];
      for (j = N - 1; j > 0; j--) {
        hx[j][i] = hx[j - 1][i];
        hy[j][i] = hy[j - 1][i];
      }
    }
    drawLines(vdgfx.Blue());
  }
}

void drawLines(uint32_t col) {
  for (int i = 0; i < N; i += M) {
    vdgfx.drawLine(hx[i][0], hy[i][0], hx[i][1], hy[i][1], col);
  }
}
