
#pragma once

#include <unordered_map>
#include <unordered_set>

class ResolutionTree
{
public:
    ResolutionTree( int rootResolution );
    
    void addNote( int sequence );
    
    void removeNote( int sequence );
    
    bool hasFinerResolution( int sequence, int resolution );
    
private:
    struct ResolutionTreeNode
    {
        std::unique_ptr<ResolutionTreeNode> first {nullptr};
        std::unique_ptr<ResolutionTreeNode> second {nullptr};
    };
    
    int _rootResolution;
    std::unordered_map<int, ResolutionTreeNode> _rootNodes;
};
