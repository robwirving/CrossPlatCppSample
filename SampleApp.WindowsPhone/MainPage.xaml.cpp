//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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

void MainPage::selectAnswer(unsigned int answerChoice)
{
	bool correct = _quizzer.SelectAnswer(answerChoice);
	if ( correct )
	{
		if(_quizzer.NextQuestion())
			displayQuestion();
	}
}

void MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	progressRing->IsActive = true;

	auto coreWindow = CoreWindow::GetForCurrentThread();

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

void MainPage::displayQuestion()
{
	auto question = _quizzer.GetQuestion();

	txtQuestion->Text = convertToPlatformString(question.GetQuestion());
	button1->Content = convertToPlatformString(question.GetAnswers()[0]);
	button2->Content = convertToPlatformString(question.GetAnswers()[1]);
	button3->Content = convertToPlatformString(question.GetAnswers()[2]);
}
