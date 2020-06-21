
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

    // rate adjustment
    void setSampleRate( double rate );
    double getSampleRate();
    void setTempo( float tempo );
    float getTempo();

    // playback
    void play();
    bool isPlaying();
    void incrementPosition( int samples );

    // rhythmic navigation
    int getSequence();
    void setSequence( int sequence );
    int getWindow();
    int getResolution();
    int getOffset();
    std::string getSequenceString( int sequence );

    // signals
    nod::unsafe_signal<void( int )> newSequence;
    nod::unsafe_signal<void( int )> newWindow;

private:
    int samplesPerSequence();

    // playback state
    juce::AudioParameterFloat _tempo;
    juce::uint64 _position{ 0 };
    double _sampleRate{ 44100 };
    bool _playing{ false };

    // rhythmic view state
    juce::uint32 _window{ 0 };
    juce::uint32 _sequence{ 0 };
    juce::uint8 _resolution{ 1 }; // (sequences per grid item)
    std::vector<int> _sequencesPerType{ 1, 4, 16 };
    std::vector<int> _sections;
};
