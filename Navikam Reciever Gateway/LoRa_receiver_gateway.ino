#include <SPI.h> // SPI is a synchronous serial communication protocol used to connect microcontrollers to peripheral devices such as sensors, displays, and memory chips. It is a master-slave architecture, where one master device controls the communication with one or more slave
#include <LoRa.h> //    LoRa is a wireless communication technology developed to create the low-power, wide-area networks (LPWANs) required for machine-to-machine (M2M) and Internet of Things (IoT) applications.

#define LORA_SS 15  // LoRa SS pin
#define LORA_RST 16 //  LoRa RST pin    
#define LORA_DI0 4 // LoRa DIO0 pin

void setup() { // This setup function runs once when you press reset or power the board
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
 
  while (!Serial); // Wait for Serial to be ready


  if (!LoRa.begin(433E6)) {   // Initialize LoRa at 433 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() { // the loop function runs over and over again forever
 
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    
    Serial.print("Received packet '");   // Print the received packet 

   
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());   // Print the received data
    }

  
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());  // Print the RSSI of the received packet
  }
}
