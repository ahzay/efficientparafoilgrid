//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_MAIN_H
#define EFFICIENTPARAFOILGRID_MAIN_H
#include <iostream>
#include <alglib/specialfunctions.h>
#include "state.h"
#include "cmdlineoptions.h"
#include "visualizer.h"
std::deque<std::deque<State>> gen_grid(const Parameters &p, State & s_init);
#endif //EFFICIENTPARAFOILGRID_MAIN_H
