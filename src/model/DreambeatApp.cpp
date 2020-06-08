
#include "DreambeatApp.h"
#include "../util/Threading.h"

DreambeatApp::DreambeatApp()
{
}

void DreambeatApp::loadSample()
{
    auto amen = juce::File::createTempFile( ".wav" );
    amen.replaceWithData( BinaryData::amen_wav, BinaryData::amen_wavSize );
//    auto createdTracks = _engine->loadSample( amen );
//    for ( auto* track : createdTracks )
//    {
//        _tracks.add( new TrackSequence( track ) );
//    }
}

void DreambeatApp::updateTempo( double tempo )
{
}

Arrangement& DreambeatApp::getArrangement()
{
    return _arrangement;
}

TrackSequence* DreambeatApp::getTrack( int i )
{
    return _tracks[i];
}
