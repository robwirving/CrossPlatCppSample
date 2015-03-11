#include "CityLocation.h"

CityLocation::CityLocation()
{
}

CityLocation::CityLocation(const std::string& nm, double lat, double lon, double dist)
	: _name(nm)
	, _latitude(lat)
	, _longitude(lon)
	, _distance(dist)
{
}

std::string CityLocation::GetName() const
{
	return _name;
}

double CityLocation::GetLatitude() const
{
	return _latitude;
}

double CityLocation::GetLongitude() const
{
	return _longitude;
}

void CityLocation::SetDistance(double distance)
{
	_distance = distance;
}

double CityLocation::GetDistance() const
{
	return _distance;
}