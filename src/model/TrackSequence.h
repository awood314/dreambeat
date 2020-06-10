
#pragma once

#include <JuceHeader.h>
#include <rubberband/rubberband/RubberBandStretcher.h>

class TrackSequence : public juce::AudioTransportSource
{
public:
    TrackSequence( juce::AudioFormatReader* reader, double sampleRate, int slices, int index );
    ~TrackSequence();

    void getNextAudioBlock( const juce::AudioSourceChannelInfo& info ) override;

    void reset();

private:
    std::unique_ptr<juce::AudioFormatReaderSource> _readerSource;
    juce::int64 _basePosition{ 0 };
    RubberBand::RubberBandStretcher _timestretcher;
};
