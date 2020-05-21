
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RowComponent.h"

class DreambeatAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DreambeatAudioProcessorEditor (DreambeatAudioProcessor&);
    ~DreambeatAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    // row of frequency modulators
    OwnedArray<RowComponent> _rows;
    OwnedArray<double> _modAngles;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DreambeatAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DreambeatAudioProcessorEditor)
};
