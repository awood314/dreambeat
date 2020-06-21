
#pragma once

#include <model/DreambeatAudioProcessor.h>
#include <ui/PlayControls.h>
#include <ui/SequenceGrid.h>
#include <ui/Timeline.h>

#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );

    void paint( juce::Graphics& g ) override;
    void resized() override;

private:
    DreambeatApp& _app;

    juce::Slider _tempoSlider;

    SequenceGrid _grid;
    juce::Label _playhead;
    Timeline _timeline;
    PlayControls _playControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
