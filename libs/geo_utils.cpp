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

float convert_angle_radians(float angle) { return angle * (M_PI / 180.0); }

float bearing_degrees(float latFrom, float lonFrom, float latTo, float lonTo) {
  /* From http://www.movable-type.co.uk/scripts/latlong.html#Bearing
   *
   * θ = atan2( sin Δλ ⋅ cos φ2 , cos φ1 ⋅ sin φ2 − sin φ1 ⋅ cos φ2 ⋅ cos Δλ )
   * where φ1,λ1 is the start point, φ2,λ2 the end point (Δλ is the
   * difference in longitude)
   */
  float delta = convert_angle_radians(lonTo - lonFrom);
  float phi1 = convert_angle_radians(latFrom);
  float phi2 = convert_angle_radians(latTo);
  const float y = sin(delta) * cos(phi2);
  const float x = cos(phi1) * sin(phi2) - sin(phi1) * cos(phi2) * cos(delta);
  const float theta = atan2(y, x);
  const float brng = (int)(theta * 180.0 / M_PI + 360.0) % 360;  // in degrees
  return brng;
}
