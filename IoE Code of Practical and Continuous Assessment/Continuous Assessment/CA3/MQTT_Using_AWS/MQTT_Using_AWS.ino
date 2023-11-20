#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"

#define AWS_IOT_PUBLISH_TOPIC   "publish"
#define AWS_IOT_SUBSCRIBE_TOPIC "subscribe"

// Define an array of messages
String messages[] = {
  "Temperature is : 33.9 °C & Humidity is : 57%",
  "Temperature is : 25.5 °C & Humidity is : 45%",
  "Temperature is : 29.8 °C & Humidity is : 62%",
  "Temperature is : 31.2 °C & Humidity is : 50%",
  "Temperature is : 28.7 °C & Humidity is : 55%",
  "Temperature is : 27.3 °C & Humidity is : 48%",
  "Temperature is : 26.1 °C & Humidity is : 59%",
  "Temperature is : 30.5 °C & Humidity is : 53%",
  "Temperature is : 32.8 °C & Humidity is : 47%",
  "Temperature is : 24.9 °C & Humidity is : 64%",
  "Temperature is : 29.0 °C & Humidity is : 51%"
};

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
struct tm timeinfo;

WiFiClientSecure net;

BearSSL::X509List cert(AWS_CERT_CA);
BearSSL::X509List client_crt(AWS_CERT_CRT);
BearSSL::PrivateKey key(AWS_CERT_PRIVATE);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;

void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");

  gmtime_r(&now, &timeinfo);
}
 
// Message sent from AWS to Arduino
void messageReceived(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message from AWS IoT is: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
 
 
void connectAWS()
{
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
 
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
 
  NTPConnect();
 
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
 
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageReceived);
 
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(1000);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

// Message sent from ESP8266 to AWS 
void publishMessage()
{
  // Randomly select a message from the array
  int randomIndex = random(sizeof(messages) / sizeof(messages[0]));
  String randomMessage = messages[randomIndex];

  StaticJsonDocument<200> doc;

  gmtime_r(&now, &timeinfo);
  doc["Readings are "] = randomMessage;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup()
{
  Serial.begin(115200);
  connectAWS();
}

void loop()
{
  gmtime_r(&now, &timeinfo); 

  // Randomly select and print a message from the array
  int randomIndex = random(sizeof(messages) / sizeof(messages[0]));
  String randomMessage = messages[randomIndex];
  Serial.print(randomMessage + '\n');

  delay(5000);

  now = time(nullptr);

  if (!client.connected())
  {
    connectAWS();
  }
  else
  {
    client.loop();
    if (millis() - lastMillis > interval)
    {
      lastMillis = millis();
      publishMessage();
    }
  }
}