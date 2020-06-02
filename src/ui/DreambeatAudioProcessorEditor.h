
#pragma once

#include "../model/DreambeatAudioProcessor.h"
#include "SampleSlicerComponent.h"
#include "SequenceComponent.h"
#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );

    void resized() override;

private:
    //    SampleSlicerComponent _sampleSlicer;
    juce::OwnedArray<SequenceComponent> _sequencer;
    juce::TextButton _playButton{ "play" };
    juce::Slider _tempoSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
