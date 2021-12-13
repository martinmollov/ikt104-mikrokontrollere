#include <Arduino.h>
#include <Arduino_MKRENV.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>

void WifiStatus();

char ssid[] = "student-FoU";
char pass[] = "stud2018";
//char server[] = "10.245.30.80";
int status = WL_IDLE_STATUS;

WiFiClient client;

int humidity;
int pressure;
int temperature;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //delay(1500); 

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

  WifiStatus();

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = int(ENV.readHumidity());
  pressure = int(ENV.readPressure());
  temperature = int(ENV.readTemperature());
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" kPa");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");


  char body[100] = {0};

String temperature_s = String(temperature);
String humidity_s = String(humidity);
String pressure_s = String(pressure);
sprintf(body, "{\"temperature\":%s, \"humidity\":%s, \"pressure\":%s}", temperature_s.c_str(), humidity_s.c_str(), pressure_s.c_str());

if (client.connect("10.225.147.174", 9090)) {  
  client.println("POST /api/v1/N07wXpUQIKZFcgHBbtoj/telemetry HTTP/1.1");
  client.println("Host: 10.245.30.80");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(strlen(body));
  client.println("Connection: close");
  client.println();
  client.println(body);
 } else{
   Serial.println("Not working...");
 }

Serial.println("POST /api/v1/N07wXpUQIKZFcgHBbtoj/telemetry HTTP/1.1");
  Serial.println("Host: localhost");
  Serial.println("Content-Type: application/json");
  Serial.print("Content-Length: ");
  Serial.println(strlen(body));
  Serial.println("Connection: close");
  Serial.println();
  Serial.println(body);
 Serial.println(temperature_s.c_str());

  delay(1000);
}

void WifiStatus() {
  // print board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

