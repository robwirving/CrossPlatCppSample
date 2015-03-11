//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "PlatformCallback.h"
#include "GpsPosition.h"
#include "SharedCode.h"
#include "PlatformConversions_Windows.h"

using namespace SampleApp_WindowsPhone;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();

	GetPlatformCallback()->SetMediaElement(media);
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	// TODO: Prepare page for display here.

	// TODO: If your application contains multiple pages, ensure that you are
	// handling the hardware Back button by registering for the
	// Windows::Phone::UI::Input::HardwareButtons.BackPressed event.
	// If you are using the NavigationHelper provided by some templates,
	// this event is handled for you.
}

void MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	progressRing->IsActive = true;

	auto coreWindow = Platform::Agile<CoreWindow>(CoreWindow::GetForCurrentThread());

	concurrency::create_task([=]()
	{
		_quizzer.Load();

		coreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([=]()
		{
			progressRing->IsActive = false;

			displayQuestion();
		}));
	});
}

void MainPage::button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	selectAnswer(0);
}

void MainPage::button2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	selectAnswer(1);
}

void MainPage::button3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	selectAnswer(2);
}

void MainPage::button4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if(_quizzer.IsNextQuestion())
	{
		_quizzer.NextQuestion();
		displayQuestion();
	}
}

void MainPage::selectAnswer(unsigned int answerChoice)
{
	_quizzer.SelectAnswer(answerChoice);

	if (_quizzer.IsNextQuestion())
		button4->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

void MainPage::displayQuestion()
{
	auto q = _quizzer.GetQuestion();

	txtQuestion->Text = convertToPlatformString(q.GetQuestion());
	button1->Content = convertToPlatformString(q.GetAnswers()[0]);
	button2->Content = convertToPlatformString(q.GetAnswers()[1]);
	button3->Content = convertToPlatformString(q.GetAnswers()[2]);

	button4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}
