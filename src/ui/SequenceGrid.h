
#pragma once

#include "../model/DreambeatApp.h"
#include "SequenceComponent.h"
#include <JuceHeader.h>

class SequenceGrid : public juce::Component
{
public:
    SequenceGrid()
    {
    }
    void resized() override;

    void addSequence( DreambeatApp& app, int track );

private:
    juce::OwnedArray<SequenceComponent> _sequences;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceGrid )
};
