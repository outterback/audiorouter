/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Mini_routerAudioProcessorEditor  : public AudioProcessorEditor,
										 public ButtonListener,
										 public LabelListener,
										 public SliderListener
{
public:
    Mini_routerAudioProcessorEditor (Mini_routerAudioProcessor&);
    ~Mini_routerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void buttonClicked(Button* buttonThatWasClicked) override;
	void labelTextChanged(Label* labelThatChanged) override;
	void sliderValueChanged(Slider* sliderChanged) override;

private:

	class InnerThread : public Thread
	{
		public:
			InnerThread(Mini_routerAudioProcessorEditor& p, const String& threadName, size_t threadStackSize = 0)
						:
						Thread(threadName, threadStackSize), parent(p)  {
				std::cout << "Init thread" << std::endl;
			}

			void run()
			{
				std::cout << "Starting thread (run())" << std::endl;
				while (true)
				{
					sleep(16);
					parent.updateGooey();
				}
			}
		private:
			Mini_routerAudioProcessorEditor& parent;
	};

	InnerThread thr;
	void updateGooey();
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Mini_routerAudioProcessor& processor;
	TextButton btn;
	Slider volumeSlider;
	Label textLabel;
	Slider channelSlider;

	ToggleButton chan23Toggle;
	Slider chan23Gain;
	ToggleButton chan45Toggle;
	Slider chan45Gain;
	ToggleButton chan67Toggle;
	Slider chan67Gain;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mini_routerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
