#pragma once

#include <array>

/// We represent our rules as booleans
/// example: we want to see if 8 neighbours should result in a birth
/// ```cpp
/// if (rule[8]) /* do something */
/// ```
using Rule = std::array<bool, 27>;

enum NeighbourMode {
    Moore,
    VonNeumann,
};

struct SimRules {
    Rule stay;
    Rule death;
    Rule birth;

    NeighbourMode neighbour_mode;
};
