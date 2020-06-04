
#include "TrackSequence.h"

TrackSequence::TrackSequence( tracktion_engine::AudioTrack* track ) : _track( track )
{
}

void TrackSequence::setNote( int note, bool value )
{
    if ( auto audioClip = _track->getClips()[note] )
    {
        audioClip->setMuted( !value );
    }
}

bool TrackSequence::getNote( int note )
{
    if ( auto audioClip = _track->getClips()[note] )
    {
        return !audioClip->isMuted();
    }
    return false;
}
