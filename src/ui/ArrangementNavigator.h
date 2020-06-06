
#pragma once

#include <JuceHeader.h>
#include <model/Arrangement.h>

class ArrangementNavigator : public juce::Component
{
public:
    ArrangementNavigator( Arrangement& arrangement );

    void resized() override;

private:
    Arrangement& _arrangement;

    juce::TextButton _beatUpButton{ "up" };
    juce::Label _beatLabel;
    juce::TextButton _beatDownButton{ "down" };

    juce::DrawableButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ArrangementNavigator )
};
