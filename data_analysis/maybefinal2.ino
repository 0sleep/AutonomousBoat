#include <Arduino.h>
#include <math.h>

int condPin = A0; // Conductivity sensor pin
int thermistorPin = A1; // Thermistor pin

// Parameters for conductivity to TDS conversion
const float CONVERSION_FACTOR = 0.64;  // TDS conversion factor
const float CELL_CONSTANT = 353.364;   // New cell constant in µS/cm
const float TEMPERATURE_COEFFICIENT = 0.019;  // Temperature coefficient
const float STANDARD_TEMP = 25.0;  // Standard reference temperature in °C

// Number of samples for smoothing conductivity readings
const int numSamples = 10;
int samples[numSamples];
int sampleIndex = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read and average conductivity samples
  int rawValue = analogRead(condPin);
  samples[sampleIndex] = rawValue;
  sampleIndex = (sampleIndex + 1) % numSamples;
  
  float sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += samples[i];
  }
  float averageRawValue = sum / numSamples;

  // Convert raw analog reading to electrical conductivity (µS/cm)
  float voltage = averageRawValue * (5.0 / 1023.0);
  float conductivity = voltage * CELL_CONSTANT;

  // Read temperature from thermistor and convert to Celsius
  int thermistorValue = analogRead(thermistorPin);
  float temperature = thermistorToCelsius(thermistorValue);

  // Correct conductivity to the standard temperature (25°C)
  float conductivityAtStandardTemp = correctConductivityForTemperature(conductivity, temperature, TEMPERATURE_COEFFICIENT, STANDARD_TEMP);

  // Convert corrected conductivity to TDS (ppm)
  float tds = conductivityAtStandardTemp * CONVERSION_FACTOR;

  // Print TDS and temperature to the serial monitor
  Serial.print("TDS (ppm): ");
  Serial.print(tds);
  Serial.print(", Temp (C): ");
  Serial.println(temperature);
  
  delay(50);
}

// Function to correct conductivity to a standard temperature (25°C)
float correctConductivityForTemperature(float conductivity, float currentTemperature, float tempCoefficient, float standardTemp) {
  return conductivity / (1 + tempCoefficient * (currentTemperature - standardTemp));
}

// Function to convert thermistor reading to temperature in degrees Celsius
float thermistorToCelsius(int rawValue) {
  float R1 = 10000; // Thermistor resistance at 25°C
  float T1 = 25;    // Temperature at which R1 is measured (°C)
  float beta = 3950; // Thermistor beta value
  
  // Calculate thermistor resistance
  float resistance = (1023.0 / rawValue - 1) * 10000;
  
  // Calculate temperature using the Steinhart-Hart equation
  return 1 / (log(resistance / R1) / beta + 1 / (T1 + 273.15)) - 273.15;
}
