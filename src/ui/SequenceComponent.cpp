
#include "SequenceComponent.h"

int NUM_NOTES = 8;

SequenceComponent::SequenceComponent( TrackSequence* track ) : _track( track )
{
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        auto* tb = new ToggleButton();
        _notes.add( tb );
        tb->onClick = [this, i]() {
            _track->setNote( i + _scene * NUM_NOTES, _notes[i]->getToggleState() );
        };
        addAndMakeVisible( tb );
    }
}

void SequenceComponent::resized()
{
    auto div = getHeight() / NUM_NOTES;
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        _notes[i]->setBounds( 0, i * div, getWidth(), div );
    }
}

void SequenceComponent::setScene( int scene )
{
    _scene = scene;
    for ( int i = 0; i < _notes.size(); i++ )
    {
        _notes[i]->setToggleState( _track->getNote( i + NUM_NOTES * scene ), juce::sendNotification );
    }
}
