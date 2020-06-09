
#pragma once

#include <JuceHeader.h>
#include <model/Arrangement.h>
#include <model/Playback.h>
#include <model/TrackSequence.h>

class DreambeatApp
{
public:
    void processBlock( juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, int numInputChannels, int numOutputChannels );

    OwnedArray<TrackSequence>& loadSample();

    void setSampleRate( double rate );

    TrackSequence* getTrack( int i );
    Arrangement& getArrangement();
    Playback& getPlayback();

private:
    juce::AudioFormatManager _formatManager;

    juce::OwnedArray<TrackSequence> _tracks;
    Arrangement _arrangement;
    Playback _playback;
};
