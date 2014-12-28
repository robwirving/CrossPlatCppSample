#pragma once

class GpsPosition
{
public:
	GpsPosition();
	~GpsPosition();

	virtual void GetCurrentPosition() = 0;
	
	double GetLatitude() const;
	double GetLongitude() const;

protected:
	double _latitude;
	double _longitude;
};

GpsPosition* GetGpsPosition();