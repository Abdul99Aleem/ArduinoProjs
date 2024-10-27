// Define the pin numbers
const int thermistorPin = 36; // GPIO 36 for thermistor
const int relayPin = 5;        // GPIO 5 for relay

// Constants
const float R1 = 57000; // Resistor value in ohms (57kΩ)
const float T0_Celsius = 25.0; // Reference temperature in Celsius
const float T0_Kelvin = T0_Celsius + 273.15; // Reference temperature in Kelvin
const float B = 3950;    // Beta value for thermistor
const float R0 = 10000;  // Resistance of thermistor at 25°C in ohms

void setup() {
  Serial.begin(115200); // Start the serial communication
  pinMode(relayPin, OUTPUT); // Set relay pin as output
  digitalWrite(relayPin, LOW); // Start with the fan off
}

void loop() {
  int adcValue = analogRead(thermistorPin); // Read the ADC value from the thermistor
  float voltage = adcValue * (3.3 / 4095); // Convert ADC value to voltage
  float R_thermistor = R1 * (3.3 / voltage - 1); // Calculate thermistor resistance

  // Calculate temperature in Kelvin
  float temperatureK = (B * T0_Kelvin) / (B + (R0 / R_thermistor) * (T0_Kelvin - 1));
  
  // Convert temperature to Celsius
  float temperatureC = temperatureK - 273.15;

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Control the fan based on temperature
  if (temperatureC >= 40) { // Fan ON if temp is 40°C or higher
    digitalWrite(relayPin, HIGH); // Turn on the fan
    Serial.println("Fan ON");
  } else {
    digitalWrite(relayPin, LOW); // Turn off the fan
    Serial.println("Fan OFF");
  }

  delay(1000); // Delay for 1 second before the next reading
}
