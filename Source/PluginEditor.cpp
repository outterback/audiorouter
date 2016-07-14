/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>
#include <chrono>
#include <thread>

//==============================================================================


Mini_routerAudioProcessorEditor::Mini_routerAudioProcessorEditor (Mini_routerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), thr(*this, "gooey"),
	chan23Gain("chan23gain"), chan23Toggle("chan23Toggle"),
	chan45Gain("chan45gain"), chan45Toggle("chan45Toggle"),
	chan67Gain("chan67gain"), chan67Toggle("chan67Toggle")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	setSize(600, 600);
	setResizable(true, true);
	btn.setName("ok");
	btn.setButtonText("Hello Byuttno");
	btn.addListener(this);
	
	

	volumeSlider.setRange(0.0, 127.0);
	channelSlider.setRange(0.0, 9.0, 1.0);
	
	channelSlider.addListener(this);

	textLabel.setText("Init", NotificationType::dontSendNotification);
	textLabel.addListener(this);

	throughput.setName("throughput");
	throughput.setButtonText("Throuhgput");
	throughputGain.setRange(0, 127, 0);
	throughputGain.setSliderStyle(Slider::Rotary);
	throughputGain.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	throughputGain.addListener(this);
	throughput.addListener(this);

	chan23Toggle.setButtonText(TRANS("Channel 2/3"));
	chan23Toggle.addListener(this);
	chan23Gain.setRange(0, 127, 0);
	chan23Gain.setSliderStyle(Slider::Rotary);
	chan23Gain.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	chan23Gain.addListener(this);

	chan45Toggle.setButtonText(TRANS("Channel 4/5"));
	chan45Toggle.addListener(this);
	chan45Gain.setRange(0, 127, 0);
	chan45Gain.setSliderStyle(Slider::Rotary);
	chan45Gain.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	chan45Gain.addListener(this);

	chan67Toggle.setButtonText(TRANS("Channel 6/7"));
	chan67Toggle.addListener(this);
	chan67Gain.setRange(0, 127, 0);
	chan67Gain.setSliderStyle(Slider::Rotary);
	chan67Gain.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
	chan67Gain.addListener(this);

	addAndMakeVisible(&throughput);
	addAndMakeVisible(&throughputGain);
	addAndMakeVisible(&chan23Gain);
	addAndMakeVisible(&chan23Toggle);
	addAndMakeVisible(&chan45Gain);
	addAndMakeVisible(&chan45Toggle);
	addAndMakeVisible(&chan67Gain);
	addAndMakeVisible(&chan67Toggle);


	addAndMakeVisible(&channelSlider);
	addAndMakeVisible(&textLabel);
	addAndMakeVisible(&btn);
	addAndMakeVisible(&volumeSlider);
	int time_0 = Time::getMillisecondCounter();
	//Time::waitForMillisecondCounter(time_0 + 250);

	std::cout << "Created Editor" << std::endl;
	thr.startThread();

		
}

Mini_routerAudioProcessorEditor::~Mini_routerAudioProcessorEditor()
{
	std::cout << "Destroying Editor" << std::endl;
	std::cout << "Killing thread...";
	thr.stopThread(200);
	std::cout << " Done" << std::endl;
}

//==============================================================================
void Mini_routerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("NJET!", getLocalBounds(), Justification::centred, 1);
}

void Mini_routerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	btn.setBounds(20, 280, 60, 60);
	volumeSlider.setBounds(20, 240, 400, 40);
	textLabel.setBounds(20, 200, 120, 60);
	channelSlider.setBounds(100, 150, 400, 100);

	
	throughputGain.setBounds(10 + 70, 110 + 50, 64, 48);
	chan23Gain.setBounds(10, 0, 64, 48);
	chan45Gain.setBounds(10 + 0, 0 + 50, 64, 48);
	chan67Gain.setBounds((10 + 0) + 0, (0 + 50) + 50, 64, 48);

	throughput.setBounds(10 + 70, 110 + 50, 104, 24);
	chan23Toggle.setBounds(10 + 70, 0 + 10, 104, 24);
	chan45Toggle.setBounds(10 + 70, 0 + 60, 104, 24);
	chan67Toggle.setBounds((10 + 0) + 70, (0 + 60) + 50, 104, 24);
	
}

void Mini_routerAudioProcessorEditor::sliderValueChanged(Slider* sliderThatChanged)
{

	if (sliderThatChanged == &volumeSlider)
	{
		
	}
	else if (sliderThatChanged == &channelSlider)
	{
		int newChannel = static_cast<int>(sliderThatChanged->getValue());
		std::cout << "slider val changed: " << newChannel << std::endl;
		processor.setThroughChannel(newChannel);
	}
	else if (sliderThatChanged == &throughputGain)
	{
		processor.setChanGain(0, sliderThatChanged->getValue());
	}
	else if (sliderThatChanged == &chan23Gain)
	{
		processor.setChanGain(1, sliderThatChanged->getValue());
	}
	else if (sliderThatChanged == &chan45Gain)
	{
		processor.setChanGain(2, sliderThatChanged->getValue());
	}
	else if (sliderThatChanged == &chan67Gain)
	{
		processor.setChanGain(3, sliderThatChanged->getValue());
	}
	else
	{
		std::cout << sliderThatChanged->getName() << " changed: " << sliderThatChanged->getValue() << std::endl;
	}
	
}

void Mini_routerAudioProcessorEditor::updateGooey()
{
	//std::cout << "updateGooey()" << std::endl;
	double as = processor.getTimeInPeriod();
	textLabel.setText(std::to_string(as), NotificationType::sendNotification);
	double time_shifted = 2.0 * 3.14159 * as * (1.0 / 1000.0);
	double slider_val = 127.0 * (0.5*cos(time_shifted) + 0.5);
	volumeSlider.setValue(slider_val, NotificationType::sendNotification);
	repaint();
}

void Mini_routerAudioProcessorEditor::buttonClicked(Button * buttonThatWasClicked)
{
	std::cout << buttonThatWasClicked->getName() << ": " << std::endl;
	if (buttonThatWasClicked == &chan23Toggle)
	{
		processor.toggleChannel(1, buttonThatWasClicked->getToggleStateValue().getValue());
	}
	else if (buttonThatWasClicked == &chan45Toggle)
	{
		processor.toggleChannel(2, buttonThatWasClicked->getToggleStateValue().getValue());
	}
	else if (buttonThatWasClicked == &chan67Toggle)
	{
		processor.toggleChannel(3, buttonThatWasClicked->getToggleStateValue().getValue());
	}
	else if (buttonThatWasClicked == &throughput)
	{
		processor.toggleChannel(0, buttonThatWasClicked->getToggleStateValue().getValue());
	}

	double as = processor.getTimeInPeriod();
	processor.resetTime();
	textLabel.setText(std::to_string(as), NotificationType::sendNotification);
}

void Mini_routerAudioProcessorEditor::labelTextChanged(Label * labelThatChanged)
{
}
