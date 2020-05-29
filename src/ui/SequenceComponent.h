
#pragma once

#include "../model/DreambeatApp.h"
#include <JuceHeader.h>

class SequenceComponent : public juce::Component
{
public:
    SequenceComponent( DreambeatApp& app, int channel );

    void resized() override;

private:
    juce::OwnedArray<juce::ToggleButton> _notes;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceComponent )
};
