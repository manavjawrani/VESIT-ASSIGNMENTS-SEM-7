const int moistureSensorPin = A0;
const int relayPumpPin = 2; // Change this to the appropriate relay pin

int moistureThreshold = 500; // Adjust this threshold as needed

void setup() {
  pinMode(relayPumpPin, OUTPUT);
  digitalWrite(relayPumpPin, LOW); // Turn off the pump initially
  Serial.begin(9600);
}

void loop() {
  int moistureLevel = analogRead(moistureSensorPin);
  Serial.print("Current Moisture Level: ");
  Serial.println(moistureLevel);

  if (moistureLevel < moistureThreshold) {
    // Soil is too dry, turn on the pump
    digitalWrite(relayPumpPin, HIGH);
    Serial.println("Watering the plant...");
  } else {
    // Soil is sufficiently moist, turn off the pump
    digitalWrite(relayPumpPin, LOW);
    Serial.println("Soil is moist, no need to water.");
  }

  delay(1000); // Delay for stability
}
