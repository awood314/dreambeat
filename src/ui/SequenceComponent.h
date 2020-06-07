
#pragma once

#include <JuceHeader.h>
#include <model/TrackSequence.h>
#include <ui/SequenceItem.h>

class SequenceComponent : public juce::Component
{
public:
    SequenceComponent( TrackSequence* track );

    void resized() override;

    void setBar( int bar );

private:
    int _bar{ 0 };
    TrackSequence* _track;
    juce::OwnedArray<SequenceItem> _notes;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceComponent )
};
