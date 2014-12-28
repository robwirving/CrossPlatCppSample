#include "GpsPosition.h"

GpsPosition::GpsPosition()
	: _latitude(0.0)
	, _longitude(0.0)
{
}

GpsPosition::~GpsPosition()
{
}

double GpsPosition::GetLatitude() const
{
	return _latitude;
}

double GpsPosition::GetLongitude() const
{
	return _longitude;
}
