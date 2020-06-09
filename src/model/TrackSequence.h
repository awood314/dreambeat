
#pragma once

#include <JuceHeader.h>

class TrackSequence
{
public:
    TrackSequence( juce::AudioFormatReader* reader, int slices, int index );

    int applyToBuffer( juce::AudioBuffer<float>& buffer, int position, int numInputChannels, int numOutputChannels );

private:
    juce::AudioSampleBuffer _sampleBuffer;
};
