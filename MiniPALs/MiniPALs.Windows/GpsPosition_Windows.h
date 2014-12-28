#pragma once

#include "GpsPosition.h"

class GpsPosition_Windows : public GpsPosition
{
public:
	GpsPosition_Windows();
	virtual ~GpsPosition_Windows();

	void GetCurrentPosition() override;
};