#include <HardwareSerial.h>
HardwareSerial hc12(1); //define UART1

//buffers for messages from each tank
String tank1Message = "WATER TANK 1: No Data";
String tank2Message = "WATER TANK 2: No Data";
String tank3Message = "WATER TANK 3: No Data";

void setup() {
  Serial.begin(115200);
  hc12.begin(9600, SERIAL_8N1, 18, 17); //HC-12: RX=GPIO18, TX=GPIO17
  Serial.println("HC-12 Receiver Ready");
}

void loop() {
  //read data from HC-12
  while (hc12.available()) {
    String receivedMessage = hc12.readStringUntil('\n'); //read until newline
    processMessage(receivedMessage);
  }

  //display data every 11 seconds
  static unsigned long lastDisplayTime = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastDisplayTime >= 11000) {
    displayMessages();
    lastDisplayTime = currentTime;
  }
}

//process the received message
void processMessage(String message) {
  if (message.startsWith("WATER TANK 1:")) {
    tank1Message = message;
  } else if (message.startsWith("WATER TANK 2:")) {
    tank2Message = message;
  } else if (message.startsWith("WATER TANK 3:")) {
    tank3Message = message;
  } else {
    Serial.println("Unknown Message: " + message);
  }
}

//display messages from all tanks
void displayMessages() {
  Serial.println("=======================");
  Serial.println(tank1Message);
  Serial.println(tank2Message);
  Serial.println(tank3Message);
  Serial.println("=======================");
}
