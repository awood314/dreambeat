
#pragma once

#include "../model/DreambeatAudioProcessor.h"
#include "ArrangementNavigator.h"
#include "SequenceGrid.h"
#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );

    void resized() override;

private:
    DreambeatApp& _app;

    juce::TabbedComponent _sequencerTabs;
    juce::OwnedArray<SequenceGrid> _grids;
    juce::Label _playhead;
    ArrangementNavigator _nav;
    juce::Slider _tempoSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
