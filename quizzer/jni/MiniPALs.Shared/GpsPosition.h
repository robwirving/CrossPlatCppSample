#pragma once

class GpsPosition
{
public:
	GpsPosition();
	GpsPosition(const GpsPosition& rhs);
	~GpsPosition();

	virtual void GetCurrentPosition();
	
	double GetLatitude() const;
	double GetLongitude() const;

protected:
	double _latitude;
	double _longitude;
};

GpsPosition* GetGpsPosition();