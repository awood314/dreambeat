
#pragma once

#include "../model/DreambeatApp.h"
#include <JuceHeader.h>

class ThumbnailComponent : public juce::Component, public juce::ChangeListener
{
public:
    ThumbnailComponent( DreambeatApp& app );

    void changeListenerCallback( juce::ChangeBroadcaster* source ) override;

    void paint( juce::Graphics& g ) override;

private:
    // thumbnail
    juce::AudioFormatManager _formatManager;
    juce::AudioThumbnailCache _sampleThumbnailCache;
    juce::AudioThumbnail _sampleThumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ThumbnailComponent )
};
