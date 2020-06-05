
#pragma once

#include <JuceHeader.h>
#include <nod/nod.hpp>

class Arrangement : public juce::Timer
{
public:
    Arrangement();

    void timerCallback() override;

    void setTransport( tracktion_engine::TransportControl* transport );

    void play();

    nod::unsafe_signal<void( int )> newSequence;
    nod::unsafe_signal<void( bool )> playPause;

private:
    tracktion_engine::TransportControl* _transport{ nullptr };
    bool _playing{ false };
    int _sequence{ -1 };
};
