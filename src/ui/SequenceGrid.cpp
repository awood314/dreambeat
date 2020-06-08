
#include "SequenceGrid.h"

int NUM_GRID_TRACKS = 8;

SequenceGrid::SequenceGrid( Arrangement& arrangement )
: _arrangement( arrangement )
{
    arrangement.newSequence.connect( [this] ( int sequence ) {
        refresh();
    } );
}

void SequenceGrid::visibilityChanged()
{
    refresh();
}

void SequenceGrid::refresh()
{
    int bar = _arrangement.getSequence( Arrangement::SequenceType::Bar );
    for ( auto* sequence : _sequences )
    {
        sequence->setBar( bar );
    }
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

void SequenceGrid::addSequence( TrackSequence* track )
{
    auto* sc = new SequenceComponent( track );
    _sequences.add( sc );
    addAndMakeVisible( sc );
}
