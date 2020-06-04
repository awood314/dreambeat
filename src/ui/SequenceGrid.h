
#pragma once

#include "../model/TrackSequence.h"
#include "SequenceComponent.h"
#include <JuceHeader.h>

class SequenceGrid : public juce::Component
{
public:
    SequenceGrid();
    void resized() override;

    void addSequence( TrackSequence* track );
    void setScene( int i );

private:
    juce::OwnedArray<SequenceComponent> _sequences;
    int _scene{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceGrid )
};
