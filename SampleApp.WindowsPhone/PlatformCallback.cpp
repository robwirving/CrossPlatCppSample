#include "pch.h"
#include "PlatformCallback.h"

PlatformCallback* g_platformCallback = nullptr;

PlatformCallback* GetPlatformCallback()
{
	if(!g_platformCallback)
		g_platformCallback = new PlatformCallback();

	return g_platformCallback;
}

PlatformCallback::PlatformCallback()
{

}

PlatformCallback::~PlatformCallback()
{

}

Windows::UI::Xaml::Controls::MediaElement^ PlatformCallback::GetMediaElement()
{
	return _mediaElement.Get();
}

void PlatformCallback::SetMediaElement(Windows::UI::Xaml::Controls::MediaElement^ mediaElement)
{
	_mediaElement = mediaElement;
}