#include "GpsPosition.h"

GpsPosition::GpsPosition()
	: _latitude(0.0)
	, _longitude(0.0)
{
}

GpsPosition::GpsPosition(const GpsPosition& rhs)
{
	_latitude = rhs.GetLatitude();
	_longitude = rhs.GetLongitude();
}

GpsPosition::~GpsPosition()
{
}

void GpsPosition::GetCurrentPosition()
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
