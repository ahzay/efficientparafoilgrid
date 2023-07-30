//
// Created by user on 7/30/23.
//

#include "attributes.h"

std::pair<double, double>
Attributes::fxfy(const Parameters &p, const double &psi_dd_f, const double &t_i, const double &t_f) const {
    double t2 = pow(psi_d_i, 2);
    double t3 = psi_i * psi_dd_f * 2.0;
    double t4 = 1.0 / psi_dd_f;
    double t5 = sqrt(M_PI);
    double t6 = psi_d_i / 2.0;
    double t8 = (psi_dd_f * t_f) / 2.0;
    double t9 = (psi_dd_f * t_i) / 2.0;
    double t10 = 1.0 / t5;
    double t11 = -t9;
    double t12 = sqrt(t4);
    double t16 = t4 * (t2 - t3) * (-1.0 / 2.0);
    double t14 = psi_d_i * t10 * t12;
    double t15 = t6 + t8 + t11;
    double t17 = cos(t16);
    double t18 = sin(t16);
    double t19 = t10 * t12 * t15 * 2.0;

    double fresnelc_t14, fresnels_t14;
    alglib::fresnelintegral(t14, fresnelc_t14, fresnels_t14);
    double fresnelc_t19, fresnels_t19;
    alglib::fresnelintegral(t19, fresnelc_t19, fresnels_t19);

    double out1_fx = x_i - p.V * t5 * t12 * t17 * fresnelc_t14 + p.V * t5 * t12 * t17 * fresnelc_t19 +
                     p.V * t5 * t12 * t18 * fresnels_t14 - p.V * t5 * t12 * t18 * fresnels_t19;
    double out1_fy = y_i - p.V * t5 * t12 * t18 * fresnelc_t14 + p.V * t5 * t12 * t18 * fresnelc_t19 -
                     p.V * t5 * t12 * t17 * fresnels_t14 + p.V * t5 * t12 * t17 * fresnels_t19;

    return std::make_pair(out1_fx, out1_fy);

}

double Attributes::fpsi(const double &psi_dd_f, const double &t_i, const double &t_f) const {
    double t2 = -t_i;
    double out1 = psi_i + ((t_f + t2) * (psi_d_i * 2.0 + psi_dd_f * t_f + psi_dd_f * t2)) / 2.0;
    return out1;
}

double Attributes::fpsi_d(const double &psi_dd_f, const double &t_i, const double &t_f) const {
    return psi_d_i + psi_dd_f * (t_f - t_i);
}

Attributes::Attributes(double psi_i, double psi_d_i, double psi_dd_i, double x_i, double y_i) : psi_i(
        psi_i),
                                                                                                psi_d_i(psi_d_i),
                                                                                                psi_dd_i(
                                                                                                        psi_d_i),
                                                                                                x_i(x_i),
                                                                                                y_i(y_i) {

}

Attributes
Attributes::gen_next_attributes(const Parameters &p, const double &u, const double &t_i, const double &t_f) const {
    double psi_dd_f = psi_dd_i + u;
    const auto xy = fxfy(p, psi_dd_f, t_i, t_f);
    return {fpsi(psi_dd_f, t_i, t_f), fpsi_d(psi_dd_f, t_i, t_f),
            psi_dd_f, xy.first, xy.second};
}
