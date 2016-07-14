/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <chrono>
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
Mini_routerAudioProcessor::Mini_routerAudioProcessor() 
	: 
	start(std::chrono::system_clock::now()), throughChannel(0),
	channelGains({64, 64, 64}),
	channelToggles({false, false, false})
	
{
	std::cout << std::endl;
	/*
	AudioChannelSet acs = AudioChannelSet::discreteChannels(7);
	
	
	//AudioProcessorBus apb("buzz", acs);
	auto pba = AudioProcessor::setPreferredBusArrangement(true, 0, acs);
	int num_in = AudioProcessor::AudioBusArrangement::getTotalNumInputChannels()
	int num_out = AudioProcessor::AudioBusArrangement::getTotalNumOutputChannels();

	std::cout << "total input: " << num_in << std::endl;
	std::cout << "total output: " << num_out << std::endl;
	std::cout << "pbapbapba!  " << pba << std::endl;
	
	auto pba = AudioProcessor::setPreferredBusArrangement(true, 0, acs);
	acs = AudioChannelSet::discreteChannels(3);
	std::cout << pba << std::endl;
	pba = AudioProcessor::setPreferredBusArrangement(true, 1, acs);
	std::cout << pba << std::endl;
	std::cout << AudioProcessor::getTotalNumInputChannels() << std::endl;
	*/
	std::cout << "Created AudioProcessor()" << std::endl;

}

int Mini_routerAudioProcessor::getTimeInPeriod()
{
	return std::chrono::milliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)).count();
}

void Mini_routerAudioProcessor::toggleChannel(int channel, bool newState)
{
	if (channel < 1 || channel > 3)
	{
		std::cout << "cannot toggle channel " << channel << std::endl;
		return;
	}
	std::cout << "chan: " << channel << " - " << newState << " new: ";
	//bool old_val = !channelToggles[channel - 1];
	channelToggles.set(channel - 1, newState);
	std::cout << channelToggles[channel - 1] << std::endl;
}

Mini_routerAudioProcessor::~Mini_routerAudioProcessor()
{
	std::cout << "killed AudioProcessor()" << std::endl;

}

void Mini_routerAudioProcessor::resetTime()
{
	start = std::chrono::system_clock::now();
}

void Mini_routerAudioProcessor::setThroughChannel(int newChannel)
{
	throughChannel = newChannel;
}



//==============================================================================
const String Mini_routerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Mini_routerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Mini_routerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double Mini_routerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Mini_routerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Mini_routerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Mini_routerAudioProcessor::setCurrentProgram (int index)
{
}

const String Mini_routerAudioProcessor::getProgramName (int index)
{
    return String();
}

void Mini_routerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Mini_routerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	
}

void Mini_routerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Mini_routerAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    //if (numChannels != 1 && numChannels != 2)
    //    return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void Mini_routerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();
	//std::cout << "numin: " << totalNumInputChannels;
	//std::cout << " numut: " << totalNumOutputChannels;
	//std::cout << " n_samp: " << numSamples;
	//std::cout << std::endl;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
	float* firstChannel = buffer.getWritePointer(0);
	AudioBuffer<float> outputBuffer(4, numSamples);
	outputBuffer.clear();

	//std::cout << "stats pre:" << std::endl;
	//std::cout << " magn: " << buffer.getMagnitude(0, 0, numSamples);
	//std::cout << " rms: " << buffer.getRMSLevel(0, 0, numSamples) << std::endl;
	//std::cout << std::endl;
	for (int channel = 1; channel <= 3; ++channel)
	{
		if (channelToggles[channel - 1])
		{
			int left = (2 * channel);
			int right = (2 * channel + 1);
			double gain = channelGains[channel - 1];
			const float* leftChanSource = buffer.getReadPointer(left);
			const float* rightChanSource = buffer.getReadPointer(right);

			outputBuffer.addFrom(0, 0, leftChanSource, numSamples, gain);
			outputBuffer.addFrom(1, 0, rightChanSource, numSamples, gain);
			std::cout << "process channel: " << channel << "  gain: " << gain << std::endl; 
			std::cout << buffer.getRMSLevel(left, 0, numSamples) << "  " << buffer.getRMSLevel(right, 0, numSamples) << std::endl;
		}
	}
	std::cout << "outputbuffer:";
	std::cout << outputBuffer.getRMSLevel(0, 0, numSamples) << "  " << buffer.getRMSLevel(1, 0, numSamples) << std::endl;
	buffer.copyFrom(2, 0, outputBuffer.getReadPointer(0), numSamples);
	buffer.copyFrom(3, 0, outputBuffer.getReadPointer(1), numSamples);

	
}

void Mini_routerAudioProcessor::setChanGain(int channel, double gain)
{
	if (channel < 1 || channel > 3)
	{
		std::cout << "cannot toggle channel " << channel << std::endl;
		return;
	}
	channelGains.set(channel-1, gain/127.0);
	std::cout << "new gain: " << channelGains[channel - 1] << std::endl;

}

//==============================================================================
bool Mini_routerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Mini_routerAudioProcessor::createEditor()
{
    return new Mini_routerAudioProcessorEditor (*this);
}

//==============================================================================
void Mini_routerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Mini_routerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Mini_routerAudioProcessor();
}
