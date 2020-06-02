
#pragma once

#include "DreambeatEngine.h"
#include <JuceHeader.h>

class DreambeatApp
{
public:
    DreambeatApp();

    void createEngine( double sampleRate, int blockSize );
    void synchronize( juce::AudioProcessor& proc );
    void processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages );

    juce::File& getSample();
    void play();
    void enableClip( int track, int clip, bool value );


private:
    std::unique_ptr<DreambeatEngine> _engine;

    juce::File _amen;
};
