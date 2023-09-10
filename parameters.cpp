//
// Created by user on 7/30/23.
//

#include "parameters.h"

Parameters::Parameters(double V, double dt, int depth, const std::deque<double> &us) :
        V(V), dt(dt), depth(depth),
        us(us) {
    uperside = ((us.size() - 1) / 2);
}
