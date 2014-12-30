#pragma once

#include <agile.h>

class PlatformCallback
{
public:
	PlatformCallback();
	~PlatformCallback();

	Windows::UI::Xaml::Controls::MediaElement^ GetMediaElement();
	void SetMediaElement(Windows::UI::Xaml::Controls::MediaElement^ mediaElement);

private:
	Platform::Agile<Windows::UI::Xaml::Controls::MediaElement> _mediaElement;
};

PlatformCallback* GetPlatformCallback();