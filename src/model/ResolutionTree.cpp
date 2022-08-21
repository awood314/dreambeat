
#include "ResolutionTree.h"

ResolutionTree::ResolutionTree( int rootResolution )
: _rootResolution( rootResolution )
{
}

void ResolutionTree::addNote( int sequence )
{
    auto currentResolution = _rootResolution;
    auto* node = &_rootNodes[sequence / currentResolution];
    while ( sequence > 0 )
    {
        sequence %= currentResolution;
        currentResolution /= 2;
        auto& nextNode = ( sequence >= currentResolution ) ? node->first : node->second;
        if ( nextNode == nullptr )
        {
            nextNode = std::make_unique<ResolutionTreeNode>();
        }
        node = nextNode.get();
    }
}

void ResolutionTree::removeNote( int sequence )
{
    auto currentResolution = _rootResolution;
    auto rootIndex = sequence / currentResolution;
    if ( sequence == 0 )
    {
        _rootNodes.erase( rootIndex );
        return;
    }
    auto* node = &_rootNodes[rootIndex];
    while ( sequence > 0 )
    {
        sequence %= currentResolution;
        currentResolution /= 2;
        auto& nextNode = ( sequence >= currentResolution ) ? node->first : node->second;
        if ( nextNode == nullptr )
        {
            return;
        }
        else if ( sequence == 0 )
        {
            nextNode.reset( nullptr );
        }
        node = nextNode.get();
    }
}

bool ResolutionTree::hasFinerResolution( int sequence, int resolution )
{
    auto currentResolution = _rootResolution;
    auto rootIndex = sequence / currentResolution;
    if ( _rootNodes.find( rootIndex ) == _rootNodes.end() )
    {
        return false;
    }
    auto* node = &_rootNodes[rootIndex];
    while ( currentResolution > resolution )
    {
        sequence %= currentResolution;
        currentResolution /= 2;
        auto& nextNode = ( sequence >= currentResolution ) ? node->first : node->second;
        if ( nextNode == nullptr )
        {
            return false;
        }
        node = nextNode.get();
    }
    return node->first != nullptr || node->second != nullptr;
}
