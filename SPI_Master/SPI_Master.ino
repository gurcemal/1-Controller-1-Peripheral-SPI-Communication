/*Arduino Mega / Controller Device
 * MOSI     -> D51
 * MISO     -> D50
 * SCK      -> D52
 * CS       -> D37
 * LED      -> D41
 * BUTTONS  -> A0
 */
#include <SPI.h>

#define CS_pin 37
#define LED 41

uint16_t analog_deger_A0 = 0, buton_deger;
byte gelen_veri, giden_veri;
long onceki_zaman = 0;

void setup() {
  Serial.begin(9600);
  pinMode(CS_pin, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(CS_pin, HIGH);
  SPI.begin();
}

void loop() {
  if (gelen_veri == 100) {
    digitalWrite(LED, HIGH);
  }
  else if (gelen_veri == 0) {
    digitalWrite(LED, LOW);
  }

  
  if (millis() - onceki_zaman >= 100) {
    buton_deger = buton_secme();
    digitalWrite(CS_pin, LOW);
    gelen_veri = SPI.transfer(giden_veri);
    Serial.print("Gelen Veri: ");
    Serial.print(gelen_veri);
    Serial.print("    ");
    Serial.print("Giden Veri: ");
    Serial.println(giden_veri);
    digitalWrite(CS_pin, HIGH);
    onceki_zaman = millis();
  }

  
}
uint16_t buton_secme() {
  // Keypad'den veri okuyoruz
  analog_deger_A0 = analogRead(A0);
  if (analog_deger_A0 >= 1015  && analog_deger_A0 <= 1025) {
    giden_veri = 0;
    return 1023;  //BOŞ
  }
  else if (analog_deger_A0 >= 635  && analog_deger_A0 <= 645) {
    giden_veri = 10;
    return 640; //SELECT
  }
  else if (analog_deger_A0 >= 405  && analog_deger_A0 <= 415) {
    giden_veri = 20;
    return 410; //LEFT
  }
  else if (analog_deger_A0 >= 250  && analog_deger_A0 <= 260) {
    giden_veri = 30;
    return 255; //DOWN
  }
  else if (analog_deger_A0 >= 95  && analog_deger_A0 <= 105) {
    giden_veri = 40;
    return 100; //UP
  }
  else if (analog_deger_A0 >= 0  && analog_deger_A0 <= 5) {
    giden_veri = 50;
    return 0;  //RIGHT
  }
}
