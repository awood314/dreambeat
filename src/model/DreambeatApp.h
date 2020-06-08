
#pragma once

#include "Arrangement.h"
#include "TrackSequence.h"
#include <JuceHeader.h>

class DreambeatApp
{
public:
    DreambeatApp();

    void loadSample();

    void updateTempo( double tempo );

    TrackSequence* getTrack( int i );
    Arrangement& getArrangement();

private:
    juce::OwnedArray<TrackSequence> _tracks;
    Arrangement _arrangement;
};
