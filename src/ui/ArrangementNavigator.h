
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

    juce::OwnedArray<juce::DrawableButton> _sequenceUpButtons;
    juce::OwnedArray<juce::Label> _sequenceLabels;
    juce::OwnedArray<juce::DrawableButton> _sequenceDownButtons;
    //    juce::DrawableButton                   _

    juce::DrawableButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ArrangementNavigator )
};
