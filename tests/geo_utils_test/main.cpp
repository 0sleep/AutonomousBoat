#include <iostream>
#include "geo_utils.h"

int main() {
  std::cout << "Calculated distance between York (53.96, -1.08) and London(51.507222, -0.1275), should be 280.4 km: \n";
  std::cout << distance_meters(53.96, -1.08, 51.507222, -0.1275);
  std::cout << "\n";
  std::cout << "Calculated bearing between London (51.5, -0.12) and New York (40.71, -74.00), should be 288°\n";
  std::cout << bearing_degrees(51.5, -0.12, 40.71, -74.00);//*180/M_PI;
  std::cout << "\n";
  return 0;
}
