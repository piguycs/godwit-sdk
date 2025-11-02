#pragma once

enum Neighbourhood {
    Moore,
    // VonNeumann,
};

/*!
*  Rules for the automota simulation. The default rule is 4/4/5/M
*/
struct SimRule {
    int remain_alive_threshold  = 4;
    int birth_threshold         = 4;
    int decay_start_value       = 5;
    Neighbourhood neighbourhood = Neighbourhood::Moore;
};
