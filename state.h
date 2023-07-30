//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_STATE_H
#define EFFICIENTPARAFOILGRID_STATE_H

#include <eigen3/Eigen/Core>
#include "attributes.h"
#include <deque>

class State {
public:
    State(const Attributes &a, Parameters *p);

    State gen_next_state(const double &u, const double t_i) const;

    Attributes a;
    Parameters *p;
};


#endif //EFFICIENTPARAFOILGRID_STATE_H
