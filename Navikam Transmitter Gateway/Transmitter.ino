#include <SPI.h>  // SPI is a synchronous serial communication protocol used to connect microcontrollers to peripheral devices such as sensors, displays, and memory chips. It is a master-slave architecture, where one master device controls the communication with one or more slave devices.
#include <LoRa.h> // LoRa is a wireless communication technology developed to create the low-power, wide-area networks (LPWANs) required for machine-to-machine (M2M) and Internet of Things (IoT) applications.
#include <TinyGPS++.h>  // TinyGPS++ is a small GPS library for Arduino providing universal NMEA parsing
#include <SoftwareSerial.h>  // SoftwareSerial is a library of Arduino which enables serial communication on digital pins other than the hardware serial port (i.e. pins 0 and 1)

static const int RXPin = 26, TXPin = 27; // RX and TX pins for GPS module
static const uint32_t GPSBaud = 9600; // Baud rate for GPS module
#define LORA_SS 5 // LoRa SS pin
#define LORA_RST 14 //  LoRa RST pin
#define LORA_DI0 2   //   LoRa DIO0 pin


TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin); // RX and TX pins for GPS module

void setup() { // This setup function runs once when you press reset or power the board
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  ss.begin(GPSBaud);
  LoRa.begin(433E6);
  LoRa.setTxPower(18);
}

void loop() {   // the loop function runs over and over again forever
  smartDelay(5000);

  if (gps.location.isValid()) { // Check if GPS location is valid
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.println(gps.location.lng(), 6);

    LoRa.beginPacket();
    LoRa.print(gps.location.lat(), 6);
    LoRa.print(",");
    LoRa.println(gps.location.lng(), 6);
    LoRa.endPacket();
  }
}

static void smartDelay(unsigned long ms) { // Function to delay for a certain time
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
// Completion of the code