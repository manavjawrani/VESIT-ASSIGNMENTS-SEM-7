#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "**Your SSID/Wifi Name**";
const char* password = " **Your SSID/Wifi Password** ";
const char* thingspeakApiKey = " **Your Thingspeak API Key ** ";

const int numReadings = 35; // Number of random readings to generate
float randomDistances[numReadings] = {
  13.45, 14.57, 15.23, 12.89, 14.01, 13.78, 14.92, 13.11, 15.67, 13.34,
  16.45, 17.57, 18.23, 16.89, 17.01, 17.78, 18.92, 17.11, 18.67, 17.34,
  19.45, 20.57, 21.23, 19.89, 20.01
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;

    // Send random distances to ThingSpeak
    for (int i = 0; i < numReadings; i++) {
      String data = "field1=" + String(randomDistances[i]);
      
      if (client.connect("api.thingspeak.com", 80)) {
        client.print("GET /update?");
        client.print(data);
        client.print("&api_key=");
        client.print(thingspeakApiKey);
        client.println(" HTTP/1.1");
        client.println("Host: api.thingspeak.com");
        client.println("Connection: close");
        client.println();
        delay(500); // Delay for stability
        client.stop();

        Serial.print("Data sent to ThingSpeak: ");
        Serial.println(randomDistances[i]);
      } else {
        Serial.println("Error connecting to ThingSpeak");
      }

      delay(1000); // Delay
    }
  }
}