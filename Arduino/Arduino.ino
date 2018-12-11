#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NUMPIXELS
#define BRIGHTNESS 255

SoftwareSerial bluetooth(2, 3); 

int neoPixelPin = 13;

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
    
    String rString = bluetoothString.substring(1, 2);
    String gString = bluetoothString.substring(3, 4);
    String bString = bluetoothString.substring(5, 6);

    int r = x2i(rString);
    int g = x2i(gString);
    int b = x2i(bString);
  }
}
