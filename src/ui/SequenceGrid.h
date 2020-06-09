
#pragma once

#include <JuceHeader.h>
#include <model/Arrangement.h>
#include <ui/SequenceItem.h>

class SequenceGrid : public juce::Component
{
public:
    SequenceGrid( Arrangement& arrangement );

    void resized() override;
    void visibilityChanged() override;

    void refresh();

    void addSequence();

private:
    juce::OwnedArray<juce::OwnedArray<SequenceItem>> _sequences;
    Arrangement& _arrangement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceGrid )
};
