/*
  ==============================================================================

    AAP - DEBUG Example

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DebugExampleAudioProcessor::DebugExampleAudioProcessor()
{
	panPosition = new AudioParameterFloat("panPosition", "Pan Position", -1.0f, 1.0f, 0.0f);
	addParameter(panPosition);

	constantPower = new AudioParameterBool("constantPower", "Constant Power", false);
	addParameter(constantPower);

}

DebugExampleAudioProcessor::~DebugExampleAudioProcessor()
{
}

//==============================================================================
const String DebugExampleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DebugExampleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DebugExampleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DebugExampleAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double DebugExampleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DebugExampleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DebugExampleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DebugExampleAudioProcessor::setCurrentProgram (int index)
{
}

const String DebugExampleAudioProcessor::getProgramName (int index)
{
    return String();
}

void DebugExampleAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DebugExampleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    *panPosition = 1.0f;
}

void DebugExampleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void DebugExampleAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Retrieve the total number of samples in the buffer for this block
    int numSamples = buffer.getNumSamples();
    
    // channelDataL and channelDataR are pointers to arrays of length numSamples which
    // contain the audio for one channel.  You repeat this for each channel
    float *channelDataL = buffer.getWritePointer(0);
    float *channelDataR = buffer.getWritePointer(1);
    
    // Calculate out of for loop for efficiency
    float temp = panPosition->get() + 1.0f;
    float pDash = 0.0;
    *constantPower = false;
    
    // Loop runs from 0 to number of samples in the block
    for (int i = 0; i < numSamples; ++i)
    {
        
        if(constantPower->get())
        {
            // Constant power panning algorithm
            pDash = (temp * MathConstants<float>::pi) / 4.0f;
            channelDataL[i] = channelDataL[i] * cos(pDash);
            channelDataL[i] = channelDataR[i] * sin(pDash);
            
            // Added intentionally to cause a significant bottleneck and hit on CPU
            for (int j = 0; j < numSamples * 1000024; j++)
                pDash = 500 / 250 / 2 / 1;

        }
        else
        {
            // Linear panning algorithm
            pDash = temp / 2.0f;
            channelDataL[i] = channelDataL[i] * (1.0f - pDash);
            channelDataL[i] = channelDataR[i] * pDash;
        }
        
    }

}

//==============================================================================
bool DebugExampleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DebugExampleAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (*this);
}

//==============================================================================
void DebugExampleAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DebugExampleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DebugExampleAudioProcessor();
}
