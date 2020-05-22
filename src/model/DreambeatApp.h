
#pragma once

#include "DreambeatEngine.h"
#include <JuceHeader.h>

class DreambeatApp
{
public:
    void createEngine( double sampleRate, int blockSize );
    void synchronize( juce::AudioProcessor& proc );
    void processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages );

    void play();

private:
    std::unique_ptr<DreambeatEngine> _engine;
};
