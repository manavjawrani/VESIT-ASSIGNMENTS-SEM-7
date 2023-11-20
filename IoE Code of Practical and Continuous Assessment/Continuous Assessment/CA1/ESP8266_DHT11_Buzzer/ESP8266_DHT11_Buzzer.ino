#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int buzzerPin = D5;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  delay(2000); // Wait for 2 seconds between measurements

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Use the temperature value to control the buzzer
  if (temperature > 23.0) {
    tone(buzzerPin, 1000); // Turn on the buzzer
  } else if (temperature < 20.0) {
    tone(buzzerPin, 750);
  }
  else {
    noTone(buzzerPin); // Turn off the buzzer
  }
}