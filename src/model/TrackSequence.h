
#pragma once

#include <JuceHeader.h>
#include <rubberband/rubberband/RubberBandStretcher.h>

class TrackSequence : public juce::AudioTransportSource
{
public:
    TrackSequence( juce::AudioFormatReader* reader, double sampleRate, float tempo, int slices, int index );
    ~TrackSequence();

    void getNextAudioBlock( const juce::AudioSourceChannelInfo& info ) override;

    void sync( int sequence, int offset, float tempo );

private:
    std::unique_ptr<juce::AudioFormatReaderSource> _readerSource;
    juce::int64 _basePosition{ 0 };

    // state to keep in sync with playback
    int _sequence{ 0 };
    int _offset{ 0 };
    float _tempo;

    RubberBand::RubberBandStretcher _timestretcher;
};
