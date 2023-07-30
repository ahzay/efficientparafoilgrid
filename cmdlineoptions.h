//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_CMDLINEOPTIONS_H
#define EFFICIENTPARAFOILGRID_CMDLINEOPTIONS_H

#include <iostream>
#include <deque>

class CmdLineOptions {
public:
    CmdLineOptions(int argc, char *argv[]);

    std::deque<double> us;
    double dt, V, psi_init;
    int depth;
};


#endif //EFFICIENTPARAFOILGRID_CMDLINEOPTIONS_H
