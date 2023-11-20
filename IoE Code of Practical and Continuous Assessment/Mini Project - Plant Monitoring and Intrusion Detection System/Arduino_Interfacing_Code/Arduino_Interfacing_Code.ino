#include <DHT.h>

#define DHTPIN 2            // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11       // Change to DHT22 if you are using DHT22 sensor
#define SOIL_MOISTURE_SENSOR_PIN A0
#define RELAY_PUMP_PIN 3     // Change this to the appropriate relay pin
#define BUZZER_PIN 9
#define PIR_SENSOR_PIN 8     // Pin for the PIR motion sensor

DHT dht(DHTPIN, DHTTYPE);
int state = LOW;             // By default, no motion detected
int val = 0;
int moistureThreshold = 500; // Adjust this threshold as needed
bool isBuzzerOn = false;
unsigned long lastMotionTime = 0;
const unsigned long debounceDelay = 5000; // 5 seconds debounce time

void setup() {
  pinMode(RELAY_PUMP_PIN, OUTPUT);
  digitalWrite(RELAY_PUMP_PIN, LOW);  // Turn off the pump initially
  pinMode(BUZZER_PIN, OUTPUT);         // Initialize Buzzer as an output
  pinMode(PIR_SENSOR_PIN, INPUT);      // Initialize PIR sensor as an input
  digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer initially
  Serial.begin(115200);
  dht.begin();
}

void loop() {

  int pirValue = digitalRead(PIR_SENSOR_PIN);
  
  if (pirValue == HIGH) {
    // Motion detected
    if (!isBuzzerOn) {
      digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
      Serial.println("Motion detected!");
      isBuzzerOn = true;
      delay(2000); // Buzzer sounds for 2 seconds
      digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
      isBuzzerOn = false;
      lastMotionTime = millis(); // Record the time of the last motion
    }
  }
  else {
    // No motion, check for debounce before turning off the buzzer
    if (isBuzzerOn && (millis() - lastMotionTime) >= debounceDelay) {
      digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
      isBuzzerOn = false;
      Serial.println("Motion stopped!");
    }
  }

  // Read DHT11 sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Display temperature and humidity
  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print("T: ");
    Serial.println(temperature);
    Serial.print("H: ");
    Serial.println(humidity);
    // Serial.println("%");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Soil moisture reading
  int moistureLevel = analogRead(SOIL_MOISTURE_SENSOR_PIN);
  Serial.print("M: ");
  Serial.println(moistureLevel);

  // Water the plant if moisture is below the threshold
  if (moistureLevel < moistureThreshold) {
    digitalWrite(RELAY_PUMP_PIN, HIGH);
    Serial.println("Watering the plant...");
  } else {
    digitalWrite(RELAY_PUMP_PIN, LOW);
    Serial.println("Soil is moist, no need to water.");
  }
  Serial.println(" ");

  // Delay for a moment before the next loop iteration
  delay(5000); // Adjust the delay as needed for your project
}