//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_PARAMETERS_H
#define EFFICIENTPARAFOILGRID_PARAMETERS_H
#include <deque>

class Parameters {
public:
    double V, dt;
    int depth;
    // maybe also define maxpsi and minpsi
    std::deque<double> us;

    Parameters(double V, double dt, int depth, const std::deque<double> &us);

    int uperside; // calculate in constructor
};


#endif //EFFICIENTPARAFOILGRID_PARAMETERS_H
