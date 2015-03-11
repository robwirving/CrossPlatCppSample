#include "CalculateDistance.h"
#include <math.h>

#define PI 3.14159265358979323846
#define RADIUS 6378.16

double CalculateDistance::BetweenPoints(double lat1, double lon1, double lat2, double lon2)
{
	auto dLon = ConvertDegreesToRadians(lon2 - lon1);
	auto dLat = ConvertDegreesToRadians(lat2 - lat1);
	auto a = (sin(dLat / 2) * sin(dLat / 2)) + cos(ConvertDegreesToRadians(lat1)) * cos(ConvertDegreesToRadians(lat2)) * (sin(dLon / 2) * sin(dLon / 2));

	auto angle = (2 * atan2(sqrt(a), sqrt(1 - a)));

	auto dist = angle * RADIUS;

	return dist;
}

double CalculateDistance::ConvertDegreesToRadians(double degrees)
{
	return (degrees * PI / 180);
}

double CalculateDistance::ConvertRadiansToDegrees(double radians)
{
	return (radians * 180 / PI);
}
