
#pragma once

#include <JuceHeader.h>
#include <model/Playback.h>

class PlaybackNavigator : public juce::Component
{
public:
    PlaybackNavigator( Playback& playback );

    void resized() override;

private:
    Playback& _playback;

    juce::OwnedArray<juce::DrawableButton> _sequenceUpButtons;
    juce::OwnedArray<juce::Label> _sequenceLabels;
    juce::OwnedArray<juce::DrawableButton> _sequenceDownButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PlaybackNavigator )
};
