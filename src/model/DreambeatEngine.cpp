
#include "DreambeatEngine.h"

DreambeatEngine::DreambeatEngine()
: _engine( ProjectInfo::projectName, nullptr, std::make_unique<PluginEngineBehaviour>() ),
  _edit( _engine, tracktion_engine::createEmptyEdit( _engine ), tracktion_engine::Edit::forEditing, nullptr, 0 ),
  _playheadSynchroniser( _edit )
{
    JUCE_ASSERT_MESSAGE_THREAD
    getAudioInterface().initialise( {} );
    setupInputs();
    setupOutputs();
}

void DreambeatEngine::loadSample( juce::File& f )
{
    // audio file to slice
    auto af = tracktion_engine::AudioFile( _engine, f );
    double slice = af.getLength() / 16.0;
    for ( int i = 0; i < 16; i++ )
    {
        // each slice gets a track
        if ( auto track = getOrInsertAudioTrackAt( i ) )
        {
            // repeat the slice along the track
            for ( int j = 0; j < 16; j++ )
            {
                if ( auto newClip =
                     track->insertWaveClip( f.getFileNameWithoutExtension(), f,
                                            { { slice * j, slice * ( j + 1 ) }, slice * i }, false ) )
                {
                    newClip->setSyncType( tracktion_engine::Clip::SyncType::syncAbsolute );
                    newClip->setTimeStretchMode( tracktion_engine::TimeStretcher::Mode::soundtouchNormal );
                    newClip->setMuted( true );
                }
            }
        }
    }

    // loop around clips
    auto& transport = _edit.getTransport();
    transport.looping = true;
    transport.position = 0.0;

    updateTempo( 170.00 );
}

void DreambeatEngine::updateTempo( double tempo )
{
    _edit.tempoSequence.getTempo( 0 )->setBpm( tempo );
    auto len = _edit.tempoSequence.barsBeatsToTime( { 4, 0 } );
    const tracktion_engine::EditTimeRange editTimeRange( 0, len );
    auto& transport = _edit.getTransport();
    transport.setLoopRange( editTimeRange );

    double ratio = tempo / 137.40;
    for ( int i = 0; i < 16; i++ )
    {
        if ( auto* track = getOrInsertAudioTrackAt( i ) )
        {
            auto clips = track->getClips();
            for ( int j = 15; j >= 0; j-- )
            {
                if ( auto* audioClip = dynamic_cast<tracktion_engine::WaveAudioClip*>( clips[j] ) )
                {
                    audioClip->setPosition( { { len * j / 16.0, len * ( j + 1 ) / 16.0 }, len * i / 16.0 } );
                    audioClip->setSpeedRatio( ratio );
                }
            }
        }
    }
}

void DreambeatEngine::enableClip( int track, int clip, bool value )
{
    if ( auto* audioTrack = getOrInsertAudioTrackAt( track ) )
    {
        if ( auto audioClip = audioTrack->getClips()[clip] )
        {
            audioClip->setMuted( !value );
        }
    }
}

tracktion_engine::HostedAudioDeviceInterface& DreambeatEngine::getAudioInterface()
{
    return _engine.getDeviceManager().getHostedAudioDeviceInterface();
}

tracktion_engine::ExternalPlayheadSynchroniser& DreambeatEngine::getPlayheadSynchroniser()
{
    return _playheadSynchroniser;
}

int DreambeatEngine::getCurrentSequence()
{
    auto& transport = _edit.getTransport();
    return transport.getCurrentPosition() * 16.0 / transport.getLoopRange().getEnd();
}

bool DreambeatEngine::isPlaying()
{
    auto& transport = _edit.getTransport();
    return transport.isPlaying();
}

void DreambeatEngine::play()
{
    auto& transport = _edit.getTransport();
    if ( transport.isPlaying() )
    {
        transport.stop( false, false );
    }
    else
    {
        transport.setCurrentPosition( 0 );
        transport.play( false );
    }
}


tracktion_engine::AudioTrack* DreambeatEngine::getOrInsertAudioTrackAt( int index )
{
    _edit.ensureNumberOfAudioTracks( index + 1 );
    return tracktion_engine::getAudioTracks( _edit )[index];
}

void DreambeatEngine::setupInputs()
{
    auto& dm = _edit.engine.getDeviceManager();

    for ( int i = 0; i < dm.getNumMidiInDevices(); i++ )
    {
        auto dev = dm.getMidiInDevice( i );
        dev->setEnabled( true );
        dev->setEndToEndEnabled( true );
    }

    _edit.playInStopEnabled = true;
    _edit.getTransport().ensureContextAllocated( true );
    _edit.restartPlayback();
}

void DreambeatEngine::setupOutputs()
{
    auto& dm = _edit.engine.getDeviceManager();

    for ( int i = 0; i < dm.getNumMidiOutDevices(); i++ )
    {
        auto dev = dm.getMidiOutDevice( i );
        dev->setEnabled( true );
    }

    _edit.playInStopEnabled = true;
    _edit.getTransport().ensureContextAllocated( true );
    _edit.restartPlayback();
}
