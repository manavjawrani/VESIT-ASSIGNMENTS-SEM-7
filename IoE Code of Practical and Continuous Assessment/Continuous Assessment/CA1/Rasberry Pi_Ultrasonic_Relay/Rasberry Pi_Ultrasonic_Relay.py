import RPi.GPIO as GPIO
import time

# Set GPIO pin numbers
TRIG_PIN = 17
ECHO_PIN = 18
RELAY_PIN = 22

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
GPIO.setup(RELAY_PIN, GPIO.OUT)

# Function to measure distance from ultrasonic sensor
def measure_distance():
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = (pulse_duration * 34300) / 2
    return distance

try:
    while True:
        distance = measure_distance()
        print(f"Distance: {distance} cm")

        if distance < 50:  # Adjust this threshold as needed
            GPIO.output(RELAY_PIN, GPIO.HIGH)  # Turn on the relay and LED
        else:
            GPIO.output(RELAY_PIN, GPIO.LOW)  # Turn off the relay and LED

        time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()