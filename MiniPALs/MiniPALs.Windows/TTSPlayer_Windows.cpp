#include "TTSPlayer_Windows.h"
#include "PlatformConversions_Windows.h"

using namespace Windows::Media::SpeechSynthesis;
using namespace Windows::UI::Xaml::Controls;

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
	auto coreWindow = Windows::UI::Core::CoreWindow::GetForCurrentThread();

	concurrency::create_task(_speechSynth->SynthesizeTextToStreamAsync(convertToPlatformString(text)))
		.then([=](SpeechSynthesisStream ^speechStream)
	{
		coreWindow->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this, speechStream]()
		{
			auto media = ref new MediaElement();
	
			media->SetSource(speechStream, speechStream->ContentType);
			media->AutoPlay = true;
			media->Play();
		}));
	});
}