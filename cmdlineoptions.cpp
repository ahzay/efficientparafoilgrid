//
// Created by user on 7/30/23.
//

#include "cmdlineoptions.h"
#include <cmath>
using namespace std;

CmdLineOptions::CmdLineOptions(int argc, char **argv) {
    if (argc < 6)
        throw std::runtime_error("Not enough input arguments.");
    if ((argc % 2)) // number of args is odd
        throw std::runtime_error("Number of input arguments should be even.");
    depth = stoi(argv[1]);
    V = stod(argv[2], nullptr);
    dt = stod(argv[3], nullptr);
    psi_init = stod(argv[4], nullptr);
    for (int i = 5; i < argc; i++)
        us.push_back(std::nextafter(stod(argv[i], nullptr),0));

}