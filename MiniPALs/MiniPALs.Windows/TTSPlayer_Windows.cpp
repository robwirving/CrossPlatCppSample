#include "pch.h"
#include "TTSPlayer_Windows.h"
#include "PlatformConversions_Windows.h"
#include "PlatformCallback.h"

using namespace Windows::Media::SpeechSynthesis;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Core;

TTSPlayer* GetTTSPlayer()
{
	return new TTSPlayer_Windows();
}

TTSPlayer_Windows::TTSPlayer_Windows()
{
	_speechSynth = ref new SpeechSynthesizer();
}

TTSPlayer_Windows::~TTSPlayer_Windows()
{

}

void TTSPlayer_Windows::SpeakText(std::string text)
{
	auto coreWindow = Platform::Agile<CoreWindow>(CoreWindow::GetForCurrentThread());

	concurrency::create_task(_speechSynth->SynthesizeTextToStreamAsync(convertToPlatformString(text)))
		.then([=](SpeechSynthesisStream ^speechStream)
	{
		coreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, 
			ref new DispatchedHandler([this, speechStream]()
		{
			auto media = GetPlatformCallback()->GetMediaElement();
	
			media->SetSource(speechStream, speechStream->ContentType);
			media->AutoPlay = true;
			media->Play();
		}));
	});
}