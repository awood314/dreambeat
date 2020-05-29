
#pragma once

#include "../model/DreambeatApp.h"
#include "ThumbnailComponent.h"
#include <JuceHeader.h>

class SampleSlicerComponent : public juce::Component
{
public:
    SampleSlicerComponent( DreambeatApp& app );

    void resized() override;

private:
    // waveform thumbnail
    ThumbnailComponent _thumbnailComponent;

    // slicer buttons
    juce::OwnedArray<juce::TextButton> _slicerButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SampleSlicerComponent )
};
