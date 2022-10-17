#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"
 
// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210

// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

void setup() {

  // Setup LED pin
  pinMode(2, OUTPUT);
  
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  // Begin Access Point
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

}

int period = 500;

void loop() {

  // Receive packet
  UDP.parsePacket();
  UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
  if (packetBuffer[0]){
    Serial.println(packetBuffer[0], BIN);
    Serial.println(packetBuffer[1], BIN);
    Serial.println(packetBuffer[2], BIN);

    if(packetBuffer[0] == 1){
      period = 100;
    }else if(packetBuffer[0] == 2){
      period = 20;
    }
    
  }

  digitalWrite(2, HIGH);
  delay(period);
  digitalWrite(2, LOW);
  delay(period);

} 
