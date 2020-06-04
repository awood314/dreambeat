
#include "SequenceGrid.h"

int NUM_GRID_TRACKS = 8;

SequenceGrid::SequenceGrid()
{
}

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

void SequenceGrid::setScene( int i )
{
    if ( i != _scene )
    {
        _scene = i;
        for ( auto* sc : _sequences )
        {
            sc->setScene( i );
        }
    }
}

void SequenceGrid::addSequence( TrackSequence* track )
{
    auto* sc = new SequenceComponent( track );
    _sequences.add( sc );
    addAndMakeVisible( sc );
}
