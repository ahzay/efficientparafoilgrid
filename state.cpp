//
// Created by user on 7/30/23.
//

#include "state.h"

#include <utility>

State::State(const Attributes &a, Parameters *p) : a(a), p(p) {}

State State::gen_next_state(const double &u, const double t_i) const {
    return {a.gen_next_attributes(*p, u, t_i, t_i + p->dt), p};
}

