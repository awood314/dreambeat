
#pragma once

#include <set>
#include <unordered_map>

class Arrangement
{
public:
    Arrangement() = default;

    std::set<int>& getNotes( int sequence );
    void setNote( int track, int sequence, bool value );

private:
    std::unordered_map<int, std::set<int>> _notes;
};
