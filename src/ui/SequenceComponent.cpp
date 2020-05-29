
#include "SequenceComponent.h"

int NUM_NOTES = 8;

SequenceComponent::SequenceComponent( DreambeatApp& app, int channel )
{
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        auto* tb = new ToggleButton();
        _notes.add( tb );
        tb->onClick = [tb, &app, channel, i]() {
            auto pattern = app.getClip()->getPattern( 0 );
            pattern.setNumNotes( 64 );
            pattern.setGate( channel, pattern.getNumNotes() * i / 8.0, 8 );
            pattern.setNote( channel, pattern.getNumNotes() * i / 8.0, tb->getToggleState() );
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
