#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>

char ssid[] = "student-FoU";
char pass[] = "stud2018";
char server[] = "www.mocky.io";
int result;

WiFiClient client;

void WifiStatus();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);
  //Serial.print("Start");
while (result != WL_CONNECTED)
  {
    result = WiFi.begin(ssid, pass);
    Serial.print("\nConnecting...");
    delay(5000);
  }
//delay(10000);

Serial.print("\nConnection succesfull!");

  if (client.connect(server, 80)) {
   Serial.println("\nConnected to server!");
  
   // Make a HTTP request (get page content)
   client.println("GET /v2/5e37e64b3100004c00d37d03 HTTP/1.1");
   client.println("Host: www.mocky.io");
   client.println("Connection: close");
   client.println();
   Serial.println(client);
   Serial.print("Test\n");
 } else {
    Serial.println("\nConnection to server failed!");
 }
   
  WifiStatus();
}

void loop() {

 StaticJsonDocument<200> doc;

  while (client.available()) {

   delay(300);
   deserializeJson(doc, client);
   delay(300);
   
   if (doc["first name"]) {
     Serial.print("\nFirst name: ");
     serializeJson(doc["first name"], Serial);
   }
   if (doc["last name"]) {
     Serial.print("\nLast name: ");
     serializeJson(doc["last name"], Serial);
   }
   if (doc["age"]) {
     Serial.print("\nAge: ");
     serializeJson(doc["age"], Serial);
   }
 }

 // If the server's disconnected, stop the client:
 if (!client.connected()) {
   Serial.println();
   Serial.println("disconnecting from server.");
   client.stop();

   // Then just do nothing
   while (true);
 }


}

void WifiStatus() {
  // print board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
