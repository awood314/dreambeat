
#pragma once

#include "../model/DreambeatAudioProcessor.h"
#include "SampleSlicerComponent.h"
#include "SequenceGrid.h"
#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );

    void resized() override;

private:
    juce::TabbedComponent _sequencerTabs;
    juce::OwnedArray<SequenceGrid> _grids;
    juce::TextButton _playButton{ "play" };
    juce::Slider _tempoSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
