
#pragma once

#include "../model/TrackSequence.h"
#include <JuceHeader.h>

class SequenceComponent : public juce::Component
{
public:
    SequenceComponent( TrackSequence* track );

    void resized() override;

    void setScene( int scene );

private:
    int _scene{ 0 };
    TrackSequence* _track;
    juce::OwnedArray<juce::ToggleButton> _notes;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceComponent )
};
