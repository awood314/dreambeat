
#pragma once

#include <JuceHeader.h>

class SequenceItem : public juce::ToggleButton
{
public:
    SequenceItem( juce::Colour color );

    void paint( juce::Graphics& g ) override;

private:
    juce::Colour _color;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceItem )
};
