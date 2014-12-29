#pragma once

#include <string>

class CityLocation
{
public:
	CityLocation()
	{
	}

	CityLocation(const std::string& nm, double lat, double lon, double dist)
		: name(nm), latitude(lat), longitude(lon), distance(dist)
	{
	}

	std::string name;
	double latitude;
	double longitude;
	double distance;
};