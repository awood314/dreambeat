
#include "SequenceComponent.h"
#include <ui/Colors.h>

int NUM_NOTES = 8;
int PADDING = 5;

SequenceComponent::SequenceComponent( TrackSequence* track ) : _track( track )
{
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        auto* note = new SequenceItem( colors::black );
        _notes.add( note );
        note->onClick = [this, i]() {
            _track->setNote( i + _scene * NUM_NOTES, _notes[i]->getToggleState() );
        };
        addAndMakeVisible( note );
    }
}

void SequenceComponent::resized()
{
    auto div = getHeight() / NUM_NOTES;
    auto size = juce::jmin( div, getWidth() ) - PADDING * 2;
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        _notes[i]->setBounds( getWidth() - size - PADDING, div * i + PADDING, size, size );
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
