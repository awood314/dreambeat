
#pragma once

#include "../model/DreambeatAudioProcessor.h"
#include <JuceHeader.h>

class DreambeatAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& p );
    ~DreambeatAudioProcessorEditor();

    void paint( Graphics& g ) override;
    void resized() override;

private:
    TabbedComponent _tc;
    juce::TextButton _button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
