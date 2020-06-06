
#pragma once

#include <JuceHeader.h>
#include <model/TrackSequence.h>
#include <ui/SequenceItem.h>

class SequenceComponent : public juce::Component
{
public:
    SequenceComponent( TrackSequence* track );

    void resized() override;

    void setScene( int scene );

private:
    int _scene{ 0 };
    TrackSequence* _track;
    juce::OwnedArray<SequenceItem> _notes;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceComponent )
};
