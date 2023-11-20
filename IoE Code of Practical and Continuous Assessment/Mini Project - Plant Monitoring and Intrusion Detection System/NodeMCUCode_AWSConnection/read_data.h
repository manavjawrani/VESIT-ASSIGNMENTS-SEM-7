float receivedH;
float receivedT;
int receivedM;

void read_data() {
  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read the data from Arduino
    String data = Serial.readStringUntil('\n'); // Read until newline character
    if (data.startsWith("M:")) {
      receivedM = data.substring(2).toInt();  // Update the global variable
      Serial.print("Moisture: ");
      Serial.println(receivedM);
    } 
    else if (data.startsWith("T:")) {
      receivedT = data.substring(2).toFloat();  // Update the global variable
      Serial.print("Temperature: ");
      Serial.println(receivedT, 2);  // Print with 2 decimal places
    }
    else if (data.startsWith("H:")) {
      receivedH = data.substring(2).toFloat();  // Update the global variable
      Serial.print("Humidity: ");
      Serial.println(receivedH, 2);  // Print with 2 decimal places
    }
  }

  delay(1000); // Adjust the delay as needed
}