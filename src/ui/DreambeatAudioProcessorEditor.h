
#pragma once

#include "../model/DreambeatAudioProcessor.h"
#include "SampleSlicerComponent.h"
#include "SequenceGrid.h"
#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor, public juce::Timer
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );

    void timerCallback() override;
    void resized() override;

private:
    DreambeatApp& _app;

    juce::TabbedComponent _sequencerTabs;
    juce::OwnedArray<SequenceGrid> _grids;
    juce::Label _playhead;
    juce::TextButton _playButton{ "play" };
    juce::Slider _tempoSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
