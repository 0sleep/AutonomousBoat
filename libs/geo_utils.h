#ifndef GEO_UTILS
#define GEO_UTILS
#define USE_MATH_DEFINES
#include "math.h"

#define UINTCOORDS(x) (x/10000000)
//From https://www.ncei.noaa.gov/products/wandering-geomagnetic-poles
//This is from the WMM2020 representation
#define MAG_NORTH_LAT 80.73
#define MAG_NORTH_LON -72.68
// determine distance to a target in meters
// The implementation of this function is adapted from
// https://github.com/AhiyaHiya/haversine, which is a c++ rewrite of the
// javascript example on http://www.movable-type.co.uk/scripts/latlong.html
float distance_meters(float latA, float lonA, float latB, float lonB);

// helper function
float convert_angle_radians(float angle);

// calculate bearing to a target
// returns in degrees
float bearing_degrees(float latFrom, float lonFrom, float latTo, float lonTo);
#endif /*GEO_UTILS*/
