//
// Created by user on 7/30/23.
//

#ifndef EFFICIENTPARAFOILGRID_ATTRIBUTES_H
#define EFFICIENTPARAFOILGRID_ATTRIBUTES_H

#include "parameters.h"
#include <iostream>
#include <utility>
#include <alglib/specialfunctions.h>

class Attributes {
public: // _i is at present time
    Attributes(double psi_i, double psi_d_i, double psi_dd_i, double x_i, double y_i);

    Attributes gen_next_attributes(const Parameters &p, const double &u,
                                   const double &t_i, const double &t_f) const;

    double psi_i,
            psi_d_i,
            psi_dd_i,
            x_i,
            y_i;

    // to be privated or moved
private:
    std::pair<double, double>
    fxfy(const Parameters &p, const double &psi_dd_f, const double &t_i, const double &t_f) const;

    double fpsi(const double &psi_dd_f, const double &t_i, const double &t_f) const;

    double fpsi_d(const double &psi_dd_f, const double &t_i, const double &t_f) const;
};


#endif //EFFICIENTPARAFOILGRID_ATTRIBUTES_H
