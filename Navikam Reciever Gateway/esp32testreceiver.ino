#include <SPI.h> // SPI is a synchronous serial communication protocol used to connect microcontrollers to peripheral devices such as sensors, displays, and memory chips. It is a master-slave architecture, where one master device controls the communication with one or more slave devices.
#include <LoRa.h> // LoRa is a wireless communication technology developed to create the low-power, wide-area networks (LPWANs) required for machine-to-machine (M2M) and Internet of Things (IoT) applications.
#define LORA_SS 5 // LoRa SS pin
#define LORA_RST 14
#define LORA_DI0 2

void setup()
{
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  while (!Serial)
    ;

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setTxPower(18);  
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSpreadingFactor(10); //  6 to 12
  LoRa.setSyncWord(0xF3); // 0xF3 is default, but can be changed
  LoRa.enableCrc(); // Enable CRC for reliable communication
}

void loop()
{
  int packetSize = LoRa.parsePacket(); // Returns the number of bytes available for reading
  if (packetSize)
  {

    while (LoRa.available())  // Returns the number of bytes available for reading
    {
      Serial.print((char)LoRa.read());
    }
  }
}
// Completion of the code