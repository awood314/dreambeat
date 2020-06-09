
#pragma once

#include <model/DreambeatAudioProcessor.h>
#include <ui/PlayControls.h>
#include <ui/PlaybackNavigator.h>
#include <ui/SequenceGrid.h>

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

    juce::TabbedComponent _sequencerTabs;
    juce::OwnedArray<SequenceGrid> _grids;
    juce::Label _playhead;
    PlaybackNavigator _nav;
    PlayControls _playControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
