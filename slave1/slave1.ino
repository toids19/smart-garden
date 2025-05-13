#include <HardwareSerial.h>

#define TRIG_PIN 5  //pin connected to Trig_RX_SCL_I/O on the JSN-SR04T
#define ECHO_PIN 6  //pin connected to Echo_TX_SDA on the JSN-SR04T

//use UART1 on GPIO17 (TX1) and GPIO18 (RX1) for HC-12 communication
HardwareSerial hc12(1); //define UART1

const int TANK_HEIGHT = 33; //height of the bottle in cm

void setup() {
  Serial.begin(115200);
  hc12.begin(9600, SERIAL_8N1, 18, 17); //initialize HC-12 at 2400 baud rate
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("WATER TANK 1 Transmitter Ready");
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; //convert to cm

  int fullness = 0;
  if (distance <= TANK_HEIGHT) {
    fullness = (1 - (distance / (float)TANK_HEIGHT)) * 100; //calculate percentage
  } else {
    fullness = 0;
  }

  if (fullness >= 0 && fullness <= 100) {
    String message = "WATER TANK 1: " + String(fullness) + "% full";
    hc12.println(message);
    Serial.println("Message Sent: " + message);
  } else {
    Serial.println("Out of range");
  }

  delay(6000); //wait 6 seconds before next message
}
