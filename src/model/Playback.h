
#pragma once

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
    void updateSequence( int sequence );

    // state
    bool _playing{ false };
    int _position{ 0 };
    int _sequence{ 0 };
    double _sampleRate{ 44100 };
    double _bpm{ 137.40 };

    int _samplesPerSequence;
    std::vector<int> _sequencesPerType{ 1, 8, 32 };
    std::vector<int> _sections;
};
