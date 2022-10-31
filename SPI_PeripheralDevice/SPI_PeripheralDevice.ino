/*Arduino Nano  / Peripheral Device
 * MOSI -> D11
 * MISO -> D12
 * SCK  -> D13
 * CS   -> D10
 * LED1 -> A1
 * LED2 -> A2
 * LED3 -> A3
 * LED4 -> A4
 * LED5 -> A5
 */

#define CS_pin 10
#define LED1 A1
#define LED2 A2
#define LED3 A3
#define LED4 A4
#define LED5 A5

byte gelen_veri, giden_veri;
bool led1_durum = false,
     led2_durum = false,
     led3_durum = false,
     led4_durum = false,
     led5_durum = false;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  pinMode(SS , INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  SPCR  |= 0b11000000;
  SPSR  |= 0b00000000;
  sei();
}

void loop() {

}

ISR(SPI_STC_vect)
{
  cli();  // interruptları kapatıyoruz
  while (digitalRead(CS_pin == LOW))
  {
    while (!(SPSR & (1 << SPIF)));
    gelen_veri = SPDR;
    if (gelen_veri == 0) {
      giden_veri = 0;
      led1_durum = false;
      led2_durum = false;
      led3_durum = false;
      led4_durum = false;
      led5_durum = false;
    }
    else if (gelen_veri == 10) {
      giden_veri = 100;
      led1_durum = true;
      led2_durum = false;
      led3_durum = false;
      led4_durum = false;
      led5_durum = false;
    }
    else if (gelen_veri == 20) {
      giden_veri = 100;
      led1_durum = false;
      led2_durum = true;
      led3_durum = false;
      led4_durum = false;
      led5_durum = false;
    }
    else if (gelen_veri == 30) {
      giden_veri = 100;
      led1_durum = false;
      led2_durum = false;
      led3_durum = true;
      led4_durum = false;
      led5_durum = false;
    }
    else if (gelen_veri == 40) {
      giden_veri = 100;
      led1_durum = false;
      led2_durum = false;
      led3_durum = false;
      led4_durum = true;
      led5_durum = false;
    }
    else if (gelen_veri == 50) {
      giden_veri = 100;
      led1_durum = false;
      led2_durum = false;
      led3_durum = false;
      led4_durum = false;
      led5_durum = true;
    }

    digitalWrite(LED1, led1_durum);
    digitalWrite(LED2, led2_durum);
    digitalWrite(LED3, led3_durum);
    digitalWrite(LED4, led4_durum);
    digitalWrite(LED5, led5_durum);

    SPDR = giden_veri;
    while (!(SPSR & (1 << SPIF)));
    Serial.print("Gelen Veri: ");
    Serial.print(gelen_veri);
    Serial.print("    ");
    Serial.print("Giden Veri: ");
    Serial.println(giden_veri);
  }
  sei();
}
