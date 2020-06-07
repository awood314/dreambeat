
#pragma once

#include <JuceHeader.h>
#include <model/Arrangement.h>

class PlayControls : public juce::Component
{
public:
    PlayControls( Arrangement& arrangement );

    void resized() override;

private:
    Arrangement& _arrangement;

    juce::DrawableButton _playButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PlayControls )
};
