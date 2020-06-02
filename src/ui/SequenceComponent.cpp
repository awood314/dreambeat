
#include "SequenceComponent.h"

int NUM_NOTES = 8;

SequenceComponent::SequenceComponent( DreambeatApp& app, int channel )
{
    for ( int i = 0; i < NUM_NOTES; i++ )
    {
        auto* tb = new ToggleButton();
        _notes.add( tb );
        tb->onClick = [tb, &app, channel, i]() {
            app.enableClip( channel, i, tb->getToggleState() );
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
