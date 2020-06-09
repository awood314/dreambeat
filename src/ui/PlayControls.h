
#pragma once

#include <JuceHeader.h>
#include <model/Playback.h>

class PlayControls : public juce::Component
{
public:
    PlayControls( Playback& playback );

    void resized() override;

private:
    Playback& _playback;

    juce::DrawableButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PlayControls )
};
