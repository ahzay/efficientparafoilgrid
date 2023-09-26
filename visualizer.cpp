//
// Created by user on 7/30/23.
//

#include "visualizer.h"

using namespace std;

Visualizer::Visualizer(int cnt, const string &color) {
    of.open(to_string(cnt) + ".gpt");
    of << "set term pngcairo size 5000,5000 enhanced font \"Times,12\" "
       << endl
       << "set multiplot"
       << endl
       << "set nokey "
       << endl
       << endl
       << "set samples 2000" << endl
       << "set isosamples 10000,10000 " << endl
       << "set xrange [0:2.5] " << endl
       << "set yrange [-1.25:1.25] " << endl
       << "set ytics 0.5" << endl
       << "set xtics 0.5" << endl
       << "set grid" << endl
       << "set grid mytics" << endl
       << "set grid mxtics"
       << endl
       << "set parametric" << endl
       << R"(plot "-" w p ls 7 lw 0.025 lc rgb ")" << color << "\"" << endl;
}

void Visualizer::save() {
    of << "e" << endl;
    of.close();
}

void Visualizer::add_state(const State &s) {
    of << s.a.x_i << " " << s.a.y_i << endl;
}