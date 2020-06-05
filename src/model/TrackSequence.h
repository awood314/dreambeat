
#pragma once

#include <JuceHeader.h>

class TrackSequence
{
public:
    TrackSequence( tracktion_engine::AudioTrack* );

    void setNote( int note, bool value );
    bool getNote( int note );

private:
    tracktion_engine::AudioTrack* _track;
};
