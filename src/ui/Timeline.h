
#pragma once

#include <model/Playback.h>

#include <JuceHeader.h>

class Timeline : public juce::Component
{
public:
    Timeline( Playback& p );

    void paint( juce::Graphics& g ) override;
    void resized() override;

private:
    Playback& _playback;

    juce::OwnedArray<juce::Label> _timeLabels;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Timeline )
};
