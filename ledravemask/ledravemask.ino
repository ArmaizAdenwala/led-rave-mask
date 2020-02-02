#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 121
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
#define BRIGHTNESS 15
#define maxCountInRow = 15;
int rowCount[11] = {15, 14, 13, 12, 13, 12, 11, 10, 9, 6, 5};

CRGB leds[NUM_LEDS];

// Sets up FastLED library
void setup()
{
  Serial.begin(9600);
  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

// Examples of designs you can loop through
void loop()
{
  heart();
  hexagon();
  rainbowFade(2, 4);
  rainbowFade(2, 3);
  rainbowFadeVertical(10, 4);
  for (int h = 0; h < 5; h++)
  {
    circle();
  }
  for (int h = 0; h < 5; h++)
  {
    rainbowFade(2, h);
  }
  for (int h = 5; h > 0; h--)
  {
    rainbowFade(2, h);
  }
  for (int h = 0; h < 5; h++)
  {
    rainbowFadeVertical(10, h);
  }
  for (int h = 5; h > 0; h--)
  {
    rainbowFadeVertical(10, h);
  }
}

int getSum(int row)
{
  int sum = 0;
  for (int i = 0; i < row; i++)
  {
    sum += rowCount[i];
  }
  return sum;
}
void rainbowFadeVertical(int lightDelay, int delta)
{
  for (int hue = 0; hue < 255; hue++)
  {
    for (int row = 0; row < 11; row++)
    {
      int sum = getSum(row);
      for (int col = 0; col < rowCount[row]; col++)
      {
        fill_rainbow(leds + (sum + col), 1, hue + (delta * row), delta);
      }
    }
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.show();
    delay(lightDelay);
  }
}

void rainbowFade(int lightDelay, int delta)
{
  for (int hue = 0; hue < 255; hue++)
  {
    for (int row = 0; row < 11; row++)
    {
      int sum = getSum(row);
      if (row % 2 == 0)
      {
        fill_rainbow(leds + sum, rowCount[row] + 1, hue, delta);
      }
      else
      {
        for (int k = 0; k < rowCount[row]; k++)
        {
          fill_rainbow(leds + (sum + rowCount[row] - k), 1, hue + (delta * k), delta);
        }
      }
    }
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.show();
    delay(lightDelay);
  }
}

int getColorFade(int a, int b, int index, int range, int i)
{
  if (a == b)
  {
    return a;
  }
  int dif = abs(a - b);
  float change = (float)dif / range * (index + 1);
  if (a > b)
  {
    return a - change;
  }
  return a + change;
}

void circle()
{
  int maxCount = 121;
  int colors[121] = {
    0, 9, 8, 7, 6, 5, 5, 5, 5, 5, 6, 7, 8, 9, 0,
      9, 8, 7, 6, 5, 4, 4, 4, 4, 5, 6, 7, 8, 9,
        8, 7, 6, 5, 4, 3, 3, 3, 4, 5, 6, 7, 8,
         7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7,
        7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7,
         6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6,
           6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6,
             6, 5, 4, 3, 2, 2, 3, 4, 5, 6,
              6, 5, 4, 3, 3, 3, 4, 5, 6,
                   5, 4, 4, 4, 4, 5,
                     5, 5, 5, 5, 5,
  };
  int rgbColors[10][3] = {
      {10, 50, 90},
      {40, 20, 40},
      {170, 30, 60},
      {190, 70, 180},
      {10, 150, 162},
  };
  for (int x = 0; x < 5; x++)
  {
    for (int z = 0; z < 251; z += 50)
    {
      for (int i = 0; i < maxCount; i++)
      {
        int color = (colors[i] + x) % 5;
        int nextColor = (color + 1) % 5;
        if (z == 0)
        {
          leds[i] = CRGB(rgbColors[color][0], rgbColors[color][1], rgbColors[color][2]);
        }
        else if (z == 250)
        {
          leds[i] = CRGB(rgbColors[nextColor][0], rgbColors[nextColor][1], rgbColors[nextColor][2]);
        }
        else
        {
          int r = getColorFade(rgbColors[color][0], rgbColors[nextColor][0], z, 255, i);
          int g = getColorFade(rgbColors[color][1], rgbColors[nextColor][1], z, 255, i);
          int b = getColorFade(rgbColors[color][2], rgbColors[nextColor][2], z, 255, i);
          leds[i] = CRGB(r, g, b);
        }
      }
      FastLED.show();
      FastLED.setMaxPowerInVoltsAndMilliamps(5, 750);
      FastLED.delay(10);
    }
  }
}

void heart()
{
  int maxCount = 121;
  int colors[121] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
  };
  for (int x = 0; x < 10; x++)
  {
    for (int i = 0; i < maxCount; i++)
    {
      if (colors[i] % 5 == x % 5)
      {
        leds[i] = CRGB(40, 160, 40);
      }
      else
      {
        leds[i] = CRGB(20, 20, 20);
      }
    }
    FastLED.show();
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 750);
    FastLED.delay(200);
  }
}

void hexagon()
{
  int maxCount = 121;
  int colors[121] = {
    0, 9, 8, 7, 6, 5, 5, 5, 5, 5, 6, 7, 8, 9, 0,
      9, 8, 7, 6, 5, 4, 4, 4, 4, 5, 6, 7, 8, 9,
       8, 7, 6, 5, 4, 3, 3, 3, 4, 5, 6, 7, 8,
        7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7,
       7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7,
        6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6,
          6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6,
            6, 5, 4, 3, 2, 2, 3, 4, 5, 6,
             6, 5, 4, 3, 3, 3, 4, 5, 6,
                  5, 4, 4, 4, 4, 5,
                   5, 5, 5, 5, 5,
  };
  int rgbColors[10][3] = {
      {140, 30, 40},
      {140, 30, 40},
      {140, 30, 40},
      {40, 20, 60},
      {40, 20, 60},
  };
  for (int x = 0; x < 5; x++)
  {
    for (int z = 0; z < 251; z += 50)
    {
      for (int i = 0; i < maxCount; i++)
      {
        int color = (9 - colors[i] + x) % 5;
        int nextColor = (color + 1) % 5;
        if (z == 0)
        {
          leds[i] = CRGB(rgbColors[color][0], rgbColors[color][1], rgbColors[color][2]);
        }
        else if (z == 250)
        {
          leds[i] = CRGB(rgbColors[nextColor][0], rgbColors[nextColor][1], rgbColors[nextColor][2]);
        }
        else
        {
          int r = getColorFade(rgbColors[color][0], rgbColors[nextColor][0], z, 255, i);
          int g = getColorFade(rgbColors[color][1], rgbColors[nextColor][1], z, 255, i);
          int b = getColorFade(rgbColors[color][2], rgbColors[nextColor][2], z, 255, i);
          leds[i] = CRGB(r, g, b);
        }
      }
      FastLED.show();
      FastLED.setMaxPowerInVoltsAndMilliamps(5, 750);
      FastLED.delay(10);
    }
  }
}
