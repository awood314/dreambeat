
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

tracktion_engine::HostedAudioDeviceInterface& DreambeatEngine::getAudioInterface()
{
    return _engine.getDeviceManager().getHostedAudioDeviceInterface();
}

tracktion_engine::ExternalPlayheadSynchroniser& DreambeatEngine::getPlayheadSynchroniser()
{
    return _playheadSynchroniser;
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

    // Add the midi input to track 1
    if ( auto t = getOrInsertAudioTrackAt( 0 ) )
        if ( auto dev = dm.getMidiInDevice( 0 ) )
            for ( auto instance : _edit.getAllInputDevices() )
                if ( &instance->getInputDevice() == dev )
                    instance->setTargetTrack( *t, 0, true );

    // Also add the same midi input to track 2
    if ( auto t = getOrInsertAudioTrackAt( 1 ) )
        if ( auto dev = dm.getMidiInDevice( 0 ) )
            for ( auto instance : _edit.getAllInputDevices() )
                if ( &instance->getInputDevice() == dev )
                    instance->setTargetTrack( *t, 0, false );


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

    // Set track 2 to send to midi output
    if ( auto t = getOrInsertAudioTrackAt( 1 ) )
    {
        auto& output = t->getOutput();
        output.setOutputToDefaultDevice( true );
    }

    _edit.restartPlayback();
}
