//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_VISUALIZER_H
#define EFFICIENTPARAFOILGRID_VISUALIZER_H
#include <string>
#include "state.h"
#include <fstream>
class Visualizer {
public:
    explicit Visualizer(int cnt, const std::string &color);

    void add_state(const State &s);

    void save();

    std::ofstream of;
};


#endif //EFFICIENTPARAFOILGRID_VISUALIZER_H
