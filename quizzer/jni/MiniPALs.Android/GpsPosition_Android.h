#pragma once

#include "GpsPosition.h"

class GpsPosition_Android : public GpsPosition
{
public:
	GpsPosition_Android();
	virtual ~GpsPosition_Android();

	void GetCurrentPosition() override;
};
