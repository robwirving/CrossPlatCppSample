#pragma once

#include "CityLocation.h"

class CalculateDistance
{
public:
	static double BetweenPoints(double lat1, double lon1, double lat2, double lon2);
	static double ConvertDegreesToRadians(double degrees);
	static double ConvertRadiansToDegrees(double radians);
};