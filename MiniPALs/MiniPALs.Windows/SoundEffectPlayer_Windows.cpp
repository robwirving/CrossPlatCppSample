#include "SoundEffectPlayer_Windows.h"
#include "PlatformConversions_Windows.h"
#include "PlatformCallback.h"
#include <collection.h>

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Core;

SoundEffectPlayer* GetSoundEffectPlayer()
{
	return new SoundEffectPlayer_Windows();
}

SoundEffectPlayer_Windows::SoundEffectPlayer_Windows()
{
}

SoundEffectPlayer_Windows::~SoundEffectPlayer_Windows()
{
}

void SoundEffectPlayer_Windows::PlayEffect(std::string effect)
{
	auto coreWindow = Platform::Agile<CoreWindow>(CoreWindow::GetForCurrentThread());

	auto mp3Uri = ref new Platform::String(TEXT("ms-appx:///Assets/"));
	mp3Uri += convertToPlatformString(effect);

	concurrency::create_task(StorageFile::GetFileFromApplicationUriAsync(ref new Uri(mp3Uri)))
		.then([](StorageFile^ mp3File)
		{
			return mp3File->OpenReadAsync();
		})
		.then([=](IRandomAccessStreamWithContentType^ stream)
		{
			coreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
				ref new DispatchedHandler([stream]()
			{
				auto media = GetPlatformCallback()->GetMediaElement();

				media->SetSource(stream, "MP3");
				media->AutoPlay = true;
				media->Play();
			}));
		});
}