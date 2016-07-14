/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <chrono>


//==============================================================================
/**
*/
class Mini_routerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Mini_routerAudioProcessor();
    ~Mini_routerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	int getTimeInPeriod();
	void resetTime();
	void setThroughChannel(int);
	void toggleChannel(int, bool);
	void setChanGain(int, double);

private:
	Array<bool> channelToggles;
	Array<double> channelGains;
	
	AudioDeviceManager *adm;
	int throughChannel;
	double t;
	std::chrono::time_point<std::chrono::system_clock> start;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mini_routerAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
