#include <cstdio>
#include <math.h>
//NOTE: This is a modified version of Maciek's maybefinal2.ino Arduino program
//I made it to check the validity of convert.py calculations

// Parameters for conductivity to TDS conversion
const float CONVERSION_FACTOR = 0.64;  // TDS conversion factor
const float CELL_CONSTANT = 353.364;   // New cell constant in µS/cm
const float TEMPERATURE_COEFFICIENT = 0.019;  // Temperature coefficient
const float STANDARD_TEMP = 25.0;  // Standard reference temperature in °C

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

int main() {
  // Convert raw analog reading to electrical conductivity (µS/cm)
  float voltage = 0.405371;//TODO hardcode this for testing
  float conductivity = voltage * CELL_CONSTANT;
  printf("Conductivity %f\n", conductivity);
  // Read temperature from thermistor and convert to Celsius
  int thermistorValue = 0.524773 * 255;//TODO hardcode this for testing
  float temperature = thermistorToCelsius(thermistorValue);
  // Correct conductivity to the standard temperature (25°C)
  float conductivityAtStandardTemp = correctConductivityForTemperature(conductivity, temperature, TEMPERATURE_COEFFICIENT, STANDARD_TEMP);
  printf("Cond at Standard Temp: %f\n", conductivityAtStandardTemp);
  // Convert corrected conductivity to TDS (ppm)
  float tds = conductivityAtStandardTemp * CONVERSION_FACTOR;
  // Print TDS and temperature to the stdout
  printf("TDS (ppm): %f, Temp (C): %f \n", tds, temperature);
  return 0;
}
