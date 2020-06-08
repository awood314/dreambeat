
#pragma once

#include <JuceHeader.h>
#include <nod/nod.hpp>

class Arrangement
{
public:
    enum SequenceType
    {
        Beat = 0,
        Bar = 1,
        Phrase = 2,
        Section = 3
    };

    Arrangement();

    void play();

    int getSequence( SequenceType type );
    void incrementSequence( SequenceType type );
    void decrementSequence( SequenceType type );
    bool canDecrementSequence( SequenceType type );

    nod::unsafe_signal<void( int )> newSequence;
    nod::unsafe_signal<void( bool )> playPause;

private:
    void updateSequence( int sequence );

    bool _playing{ false };

    int _sequence{ 0 };

    std::vector<int> _sequencesPerType{ 1, 8, 32 };
    std::vector<int> _sections;
};
