
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
    if ( auto track = getOrInsertAudioTrackAt( 0 ) )
    {
        // audio file to slice
        auto af = tracktion_engine::AudioFile( _engine, f );
        _edit.tempoSequence.getTempos()[0]->setBpm( 137.40 );

        // create 1bar step clip
        const tracktion_engine::EditTimeRange editTimeRange( 0, _edit.tempoSequence.barsBeatsToTime( { 4, 0.0 } ) );
        track->insertNewClip( tracktion_engine::TrackItem::Type::step, "Step Clip", editTimeRange, nullptr );
        if ( auto* clip = dynamic_cast<tracktion_engine::StepClip*>( track->getClips()[0] ) )
        {
            // loop around clip
            auto& transport = _edit.getTransport();
            transport.setLoopRange( clip->getEditTimeRange() );
            transport.looping = true;
            transport.position = 0.0;

            // create sampler for the clip
            if ( auto sampler = dynamic_cast<tracktion_engine::SamplerPlugin*>(
                 _edit.getPluginCache()
                 .createNewPlugin( tracktion_engine::SamplerPlugin::xmlTypeName, {} )
                 .get() ) )
            {
                track->pluginList.insertPlugin( *sampler, 0, nullptr );

                // slice the sample across each channel
                auto& channels = clip->getChannels();
                auto slice = af.getLength() / (double)channels.size();
                for ( int i = 0; i < channels.size(); i++ )
                {
                    const auto error = sampler->addSound( f.getFullPathName(), channels[i]->name.get(),
                                                          (double)i * slice, 0.0, 1.0f );
                    sampler->setSoundParams( i, channels[i]->noteNumber, channels[i]->noteNumber,
                                             channels[i]->noteNumber );
                    jassert( error.isEmpty() );
                }
            }
        }
    }
}

tracktion_engine::StepClip::Ptr DreambeatEngine::getClip()
{
    if ( auto track = getOrInsertAudioTrackAt( 0 ) )
    {
        if ( auto clip = dynamic_cast<tracktion_engine::StepClip*>( track->getClips()[0] ) )
            return *clip;
    }

    return {};
}


tracktion_engine::HostedAudioDeviceInterface& DreambeatEngine::getAudioInterface()
{
    return _engine.getDeviceManager().getHostedAudioDeviceInterface();
}

tracktion_engine::ExternalPlayheadSynchroniser& DreambeatEngine::getPlayheadSynchroniser()
{
    return _playheadSynchroniser;
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

void DreambeatEngine::play( int index )
{
    auto& transport = _edit.getTransport();
    if ( transport.isPlaying() )
    {
        transport.stop( false, false );
    }

    transport.setCurrentPosition( ( index / 8. ) * transport.getLoopRange().getEnd() );
    transport.play( false );
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
