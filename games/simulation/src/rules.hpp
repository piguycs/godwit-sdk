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
    // VonNeumann,
};

struct SimRules {
    Rule stay;
    Rule birth;

    int decay_start;

    NeighbourMode neighbour_mode;

    SimRules() {
        // 4/4/5/M rule
        stay[4] = true;
        birth[4] = true;
        decay_start = 5;
        neighbour_mode = Moore;
    }
};
