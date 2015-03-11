#pragma once

#include <string>

class CityLocation
{
public:
	CityLocation();

	CityLocation(const std::string& nm, double lat, double lon, double dist);
	
	std::string GetName() const;

	double GetLatitude() const;
	double GetLongitude() const;

	void SetDistance(double distance);
	double GetDistance() const;

private:
	std::string _name;
	double _latitude;
	double _longitude;
	double _distance;
};