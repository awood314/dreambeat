
#pragma once

#include <JuceHeader.h>
#include <nod/nod.hpp>

class Playback
{
public:
    enum SequenceType
    {
        Beat = 0,
        Bar = 1,
        Phrase = 2,
        Section = 3
    };

    Playback();

    void setSampleRate( double rate );
    double getSampleRate();

    void setTempo( float tempo );
    float getTempo();

    void play();
    bool isPlaying();

    void incrementPosition( int samples );

    int getSequence();
    int getOffset();

    // beat, bar, phrase, navigation
    int getSequence( SequenceType type );
    void incrementSequence( SequenceType type );
    void decrementSequence( SequenceType type );
    bool canDecrementSequence( SequenceType type );

    nod::unsafe_signal<void( int )> newSequence;

private:
    void updateSequence( juce::uint32 sequence );
    int samplesPerSequence();

    // state
    juce::AudioParameterFloat _tempo;
    juce::uint64 _position{ 0 };
    double _sampleRate{ 44100 };
    bool _playing{ false };

    // selected sequence
    juce::uint32 _sequence{ 0 };

    // sequences and patterns
    std::vector<int> _sequencesPerType{ 1, 8, 32 };
    std::vector<int> _sections;
};
