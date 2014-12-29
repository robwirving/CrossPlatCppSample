#include "pch.h"
#include "GpsPosition_Windows.h"

using namespace concurrency;
using namespace Windows::Devices::Geolocation;

GpsPosition* GetGpsPosition()
{
	return new GpsPosition_Windows();
}

GpsPosition_Windows::GpsPosition_Windows()
{
}

GpsPosition_Windows::~GpsPosition_Windows()
{
}

void GpsPosition_Windows::GetCurrentPosition()
{
	event synchronizer;
	auto asyncOp = create_task([]()
	{
		auto geoLocator = ref new Windows::Devices::Geolocation::Geolocator();
		return geoLocator->GetGeopositionAsync();
	}).then([&](Geoposition^ position)
	{
		_latitude = position->Coordinate->Point->Position.Latitude;
		_longitude = position->Coordinate->Point->Position.Longitude;
		synchronizer.set();
	}, task_continuation_context::use_arbitrary());
	synchronizer.wait();
}
