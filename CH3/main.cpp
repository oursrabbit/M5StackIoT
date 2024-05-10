#include <SD.h>
#include <M5Unified.h>

#define countDownTimePositionX 140
#define countDownTimePositionY 80
#define countDownTimeSize 5

#define RedLight 0
#define YelloLight 1
#define GreenLight 2
int trafficStatus = 0;

// millisecond
#define redTime 3000;
#define yellowTime 2000;
#define greenTime 1000;

int countdownTime = 0;

#define RedLightPositionX 70
#define RedLightPositionY 50
#define RedLightRadius 25
#define YelloLightPositionX 70
#define YelloLightPositionY 120
#define YelloLightRadius 25
#define GreenLightPositionX 70
#define GreenLightPositionY 190
#define GreenLightRadius 25

#define AnimPositionX 210
#define AnimPositoinY 80
int animIndex = 0;

int trafficStatusOffset = 1;

void switchTrafficLight()
{
  trafficStatus = trafficStatus + trafficStatusOffset;

  if (trafficStatus == 3)
  {
    trafficStatus = YelloLight;
    trafficStatusOffset = -1;
  }

  if (trafficStatus == -1)
  {
    trafficStatus = YelloLight;
    trafficStatusOffset = 1;
  }

  switch (trafficStatus)
  {
  case RedLight:
    countdownTime = redTime;
    break;
  case YelloLight:
    countdownTime = yellowTime;
    break;
  case GreenLight:
    countdownTime = greenTime;
    break;
  }
}

void drawSecond()
{
  if (trafficStatus == RedLight)
    M5.Display.setTextColor(RED);
  else if (trafficStatus == YelloLight)
    M5.Display.setTextColor(YELLOW);
  else
    M5.Display.setTextColor(GREEN);

  M5.Display.setTextSize(countDownTimeSize);
  M5.Display.setCursor(countDownTimePositionX, countDownTimePositionY);

  int displayTime = countdownTime / 1000;
  M5.Display.print(displayTime);
}

void drawLight()
{
  if (trafficStatus == RedLight)
  {
    M5.Display.fillCircle(RedLightPositionX, RedLightPositionY, RedLightRadius, RED);
    M5.Display.fillCircle(YelloLightPositionX, YelloLightPositionY, YelloLightRadius, DARKGREY);
    M5.Display.fillCircle(GreenLightPositionX, GreenLightPositionY, GreenLightRadius, DARKGREY);
  }
  else if (trafficStatus == YelloLight)
  {
    M5.Display.fillCircle(RedLightPositionX, RedLightPositionY, RedLightRadius, DARKGREY);
    M5.Display.fillCircle(YelloLightPositionX, YelloLightPositionY, YelloLightRadius, YELLOW);
    M5.Display.fillCircle(GreenLightPositionX, GreenLightPositionY, GreenLightRadius, DARKGREY);
  }
  else
  {
    M5.Display.fillCircle(RedLightPositionX, RedLightPositionY, RedLightRadius, DARKGREY);
    M5.Display.fillCircle(YelloLightPositionX, YelloLightPositionY, YelloLightRadius, DARKGREY);
    M5.Display.fillCircle(GreenLightPositionX, GreenLightPositionY, GreenLightRadius, GREEN);
  }
}

void drawAnim()
{
  if (trafficStatus == YelloLight)
  {
    auto filePath = "";

    if (animIndex == 0)
      filePath = "/w1.png";
    else if (animIndex == 1)
      filePath = "/w2.png";
    else
      filePath = "/w3.png";

    M5.Display.drawPngFile(SD, filePath, AnimPositionX, AnimPositoinY, M5.Display.width(), M5.Display.height());
    animIndex = (animIndex + 1) % 3;
  }
}

void drawTrafficLight()
{
  M5.Display.clear(BLACK);
  drawSecond();
  drawLight();
  drawAnim();
}

void setup()
{
  SD.begin(GPIO_NUM_4, SPI, 25000000);

  auto cfg = M5.config();
  M5.begin(cfg);

  // green
  trafficStatus = GreenLight;
  countdownTime = greenTime;
}

void loop()
{
  drawTrafficLight();

  countdownTime = countdownTime - 1000;
  if (countdownTime <= 0)
  {
    switchTrafficLight();
  }

  delay(1000);
}