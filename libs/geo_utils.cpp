#include "geo_utils.h"

float distance_meters(float latA, float lonA, float latB, float lonB) {
  const int earth_radius = 6371000;  // mean earth radius in meters
  const float lat_delta = convert_angle_radians((latB - latA));
  const float lon_delta = convert_angle_radians((lonB - lonA));

  const float converted_latA = convert_angle_radians((latA));
  const float converted_latB = convert_angle_radians((latB));

  const float a = pow(sin(lat_delta / 2), 2) + cos(converted_latA) *
                                                   cos(converted_latB) *
                                                   pow(sin(lon_delta / 2), 2);
  const float c = 2 * asin(sqrt(a));
  const float d = earth_radius * c;
  return d;  // in meters
}

float convert_angle_radians(float angle) {
  return angle * (M_PI / 180.0);
}

float bearing(float latFrom, float lonFrom, float latTo, float lonTo) {
  // TODO: use correct angle. for now: incorrect "equirectangular" estimation
  const float g = latTo - latFrom;
  const float a = lonTo - lonFrom;
  return 0;
//  return atan2(g / a);
}
