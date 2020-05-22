
#pragma once

#include <JuceHeader.h>
#include "../model/DreambeatAudioProcessor.h"

class DreambeatAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor( DreambeatAudioProcessor& );
    ~DreambeatAudioProcessorEditor();

    void paint( Graphics& g ) override;
    void resized() override;

private:
    DreambeatAudioProcessor& processor;
    
    TabbedComponent _tc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( DreambeatAudioProcessorEditor )
};
