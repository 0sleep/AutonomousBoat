#include <iostream>
#include "geo_utils.h"

int main() {
  std::cout << "Calculated distance between York (53.96, -1.08) and London(51.507222, -0.1275), should be 280.4 km: \n";
  std::cout << distance_meters(53.96, -1.08, 51.507222, -0.1275);
  std::cout << "\n";
  return 0;
}
