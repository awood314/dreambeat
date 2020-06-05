
#pragma once

#include "../model/Arrangement.h"
#include <JuceHeader.h>

class ArrangementNavigator : public juce::Component
{
public:
    ArrangementNavigator( Arrangement& arrangement );

    void resized() override;

private:
    Arrangement& _arrangement;

    juce::TextButton _playButton{ "play" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ArrangementNavigator )
};
