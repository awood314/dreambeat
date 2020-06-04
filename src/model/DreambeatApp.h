
#pragma once

#include "DreambeatEngine.h"
#include "TrackSequence.h"
#include <JuceHeader.h>

class DreambeatApp
{
public:
    DreambeatApp();

    void createEngine( double sampleRate, int blockSize );
    void synchronize( juce::AudioProcessor& proc );
    void processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages );

    void loadSample();
    int getCurrentSequence();
    bool isPlaying();
    void play();
    void enableClip( int track, int clip, bool value );
    void updateTempo( double tempo );

    TrackSequence* getTrack( int i );

private:
    std::unique_ptr<DreambeatEngine> _engine;
    juce::OwnedArray<TrackSequence> _tracks;
};
