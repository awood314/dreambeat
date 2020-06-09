
#include "DreambeatAudioProcessor.h"
#include "../ui/DreambeatAudioProcessorEditor.h"

DreambeatAudioProcessor::DreambeatAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor( BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                  .withInput( "Input", AudioChannelSet::stereo(), true )
#endif
                  .withOutput( "Output", AudioChannelSet::stereo(), true )
#endif
  )
#endif
{
}

DreambeatAudioProcessor::~DreambeatAudioProcessor()
{
}

const String DreambeatAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DreambeatAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DreambeatAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DreambeatAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DreambeatAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DreambeatAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int DreambeatAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DreambeatAudioProcessor::setCurrentProgram( int index )
{
}

const String DreambeatAudioProcessor::getProgramName( int index )
{
    return {};
}

void DreambeatAudioProcessor::changeProgramName( int index, const String& newName )
{
}

void DreambeatAudioProcessor::prepareToPlay( double sampleRate, int blockSize )
{
    setLatencySamples( blockSize );
    _app.setSampleRate( sampleRate );
}

void DreambeatAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DreambeatAudioProcessor::isBusesLayoutSupported( const BusesLayout& layouts ) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused( layouts );
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if ( layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
         layouts.getMainOutputChannelSet() != AudioChannelSet::stereo() )
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if ( layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet() )
        return false;
#endif

    return true;
#endif
}
#endif

void DreambeatAudioProcessor::processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages )
{
    juce::ScopedNoDenormals noDenormals;
    auto numInputChannels = getTotalNumInputChannels();
    auto numOutputChannels = getTotalNumOutputChannels();
    for ( auto i = numInputChannels; i < numOutputChannels; ++i )
    {
        buffer.clear( i, 0, buffer.getNumSamples() );
    }

    _app.processBlock( buffer, midiMessages, numInputChannels, numOutputChannels );
}

bool DreambeatAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* DreambeatAudioProcessor::createEditor()
{
    return new DreambeatAudioProcessorEditor( *this );
}

void DreambeatAudioProcessor::getStateInformation( MemoryBlock& destData )
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DreambeatAudioProcessor::setStateInformation( const void* data, int sizeInBytes )
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

DreambeatApp& DreambeatAudioProcessor::getApp()
{
    return _app;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DreambeatAudioProcessor();
}
