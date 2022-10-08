#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
// Set WiFi credentials
#define WIFI_SSID "TheOtherESP"
#define WIFI_PASS "flashmeifyoucan"

// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);
#define UDP_PORT 4210

void setup() {

  // Setup IO
//  pinMode(5, INPUT);
  pinMode(2, INPUT);
  
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);
 
}

char buf = 3;
 
void loop() {

  // Read button
  char buttonState = digitalRead(2);

  Serial.println(buttonState, BIN);

  if(buttonState == HIGH){
    buf = 1;
  }else if(buttonState == LOW){
    buf = 2;
  }

  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);
  UDP.write(buf);
  UDP.endPacket();
  delay(100);
  
}
