
#include "SequenceGrid.h"

int NUM_GRID_TRACKS = 8;

void SequenceGrid::resized()
{
    auto div = getWidth() / NUM_GRID_TRACKS;
    for ( int i = 0; i < NUM_GRID_TRACKS; i++ )
    {
        if ( i < _sequences.size() )
        {
            _sequences[i]->setBounds( i * div, 0, div, getHeight() );
        }
    }
}

void SequenceGrid::addSequence( DreambeatApp& app, int track )
{
    auto* sc = new SequenceComponent( app, track );
    _sequences.add( sc );
    addAndMakeVisible( sc );
}
