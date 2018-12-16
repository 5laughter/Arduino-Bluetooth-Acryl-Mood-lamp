#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 13
#define NUMPIXELS 4
#define BRIGHTNESS 255

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

SoftwareSerial bluetooth(2, 3);

String bluetoothString = "";

void setup() {
  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }

  bluetooth.begin(9600);  
}

void loop() {
  while (bluetooth.available()) {
    char bluetoothChar = (char)bluetooth.read();
    bluetoothString += bluetoothChar;
    delay(5);
  }

  if(!bluetooth.equals("")){
    Serial.println("bluetooth value : " + bluetoothString);
    bluetoothString.toCharArray(bluetoothString, 50);
    
    char red[5] = {0};
    char green[5] = {0};
    char blue[5] = {0};

    red[0] = green[0] = blue[0] = '0';
    red[1] = green[1] = blue[1] = 'X';

    red[2] = bluetoothString[1];
    red[3] = bluetoothString[2];

    green[2] = bluetoothString[3];
    green[3] = bluetoothString[4];

    blue[2] = bluetoothString[5];
    blue[3] = bluetoothString[6];

    int r = strtol(red, NULL, 16);
    int g = strtol(green, NULL, 16);
    int b = strtol(blue, NULL, 16);
    
    int i = 0;
    for(i=0; i<=NUMPIXELS; i++){      
      pixels.setPixelColor(i, r, g, b, 0);
      pixels.show();
      delay(50);
    }
  }
}
