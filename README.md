# led-rave-mask

## Setup

To setup cut up multiple strips of WS2812B.

Cut up the lightstrip so that you have 11 strips with the following number of leds: 15, 14, 13, 12, 13, 12, 11, 10, 9, 6, 5

Since FastLED treats the entire mask as one array of leds, you need to solder them in a specific order. Every other row needs to to have the strip flipped so that you won't need long wires since the `in` pin would be right below the `out` pin from the strip above it.

Solder the light strips in this order:
15,
14, (in and out pins are flipped)
13,
12, (in and out pins are flipped)
13,
12, (in and out pins are flipped)
11,
10, (in and out pins are flipped)
9,
6, (in and out pins are flipped)
5

Connect the WS2812B led light strip `in` pin to pin 5 on your arduino / arduino mega / arduino nano

## To run the project

Open the project in the Arduino IDE and upload it to the arduino. The arduino will automatically loop through leds when it starts up.
