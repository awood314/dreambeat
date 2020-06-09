
#pragma once

#include <JuceHeader.h>
#include <model/Arrangement.h>
#include <model/Playback.h>
#include <ui/SequenceItem.h>

class SequenceGrid : public juce::Component
{
public:
    SequenceGrid( Arrangement& arrangement, Playback& playback );

    void resized() override;
    void visibilityChanged() override;

    void refresh();

    void addSequence();

private:
    juce::OwnedArray<juce::OwnedArray<SequenceItem>> _sequences;
    Playback& _playback;
    Arrangement& _arrangement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SequenceGrid )
};
