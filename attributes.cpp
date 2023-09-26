//
// Created by user on 7/30/23.
//

#include "attributes.h"
#include <complex>
#include <float.h>

std::pair<double, double>
Attributes::fxfy(const Parameters &p, const double &psi_dd_f, const double &t_i, const double &t_f) const {
    double t2 = pow(psi_d_i, 2);
    double t3 = psi_i * psi_dd_f * 2.0;
    std::complex<double> t4_c = 1.0 / psi_dd_f;
    double t5 = sqrt(M_PI);
    double t6 = psi_d_i / 2.0;
    double t8 = (psi_dd_f * t_f) / 2.0;
    double t9 = (psi_dd_f * t_i) / 2.0;
    double t10 = 1.0 / t5;
    double t11 = -t9;
    std::complex<double> t12_c = sqrt(t4_c);
    bool isPureReal = t12_c.real() != 0 && isfinite(t12_c.real());
    //std::cout << "real? " << isPureReal << std::endl;
    //std::cout << t12_c.real() << " " << t12_c.imag() << std::endl;
    double t16 = t4_c.real() * (t2 - t3) * (-1.0 / 2.0);
    std::complex<double> t14_c = psi_d_i * t10 * t12_c;
    double t15 = t6 + t8 + t11;
    double t17 = cos(t16);
    double t18 = sin(t16);
    std::complex<double> t19_c = t10 * t12_c * t15 * 2.0;
    double fresnelc_t14, fresnels_t14, fresnelc_t19, fresnels_t19;
    std::complex<double>
            fresnelc_t14_c = 0,
            fresnels_t14_c = 0,
            fresnelc_t19_c = 0,
            fresnels_t19_c = 0;
    if (isPureReal) {
        alglib::fresnelintegral(t14_c.real(), fresnelc_t14, fresnels_t14);
        alglib::fresnelintegral(t19_c.real(), fresnelc_t19, fresnels_t19);
        fresnelc_t14_c.real(fresnelc_t14);
        fresnels_t14_c.real(fresnels_t14);
        fresnelc_t19_c.real(fresnelc_t19);
        fresnels_t19_c.real(fresnels_t19);
    } else {
        alglib::fresnelintegral(t14_c.imag(), fresnelc_t14, fresnels_t14);
        alglib::fresnelintegral(t19_c.imag(), fresnelc_t19, fresnels_t19);
        fresnelc_t14_c.imag(fresnelc_t14);
        fresnels_t14_c.imag(-fresnels_t14);
        fresnelc_t19_c.imag(fresnelc_t19);
        fresnels_t19_c.imag(-fresnels_t19);
    }


    std::complex<double> out1_fx = x_i - p.V * t5 * t12_c * t17 * fresnelc_t14_c +
                                   p.V * t5 * t12_c * t17 * fresnelc_t19_c +
                                   p.V * t5 * t12_c * t18 * fresnels_t14_c -
                                   p.V * t5 * t12_c * t18 * fresnels_t19_c;
    std::complex<double> out1_fy = y_i - p.V * t5 * t12_c * t18 * fresnelc_t14_c +
                                   p.V * t5 * t12_c * t18 * fresnelc_t19_c -
                                   p.V * t5 * t12_c * t17 * fresnels_t14_c +
                                   p.V * t5 * t12_c * t17 * fresnels_t19_c;
    //::cout << out1_fx.real() << " " << out1_fy.real() << std::endl;
    return std::make_pair(out1_fx.real(), out1_fy.real());
}

std::pair<double, double> // for psi_dd = 0 cases
Attributes::fxfy2(const Parameters &p, const double &psi_dd_f, const double &t_i, const double &t_f) const {
    double out1_fx = x_i + (p.V * (sin(psi_i + psi_d_i * (t_f - t_i)) - sin(psi_i))) / psi_d_i;
    double out1_fy = y_i - (p.V * (cos(psi_i + psi_d_i * (t_f - t_i)) - cos(psi_i))) / psi_d_i;
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
    std::pair<double, double>  xy;
    if (psi_dd_f != 0)
        xy =fxfy(p, psi_dd_f, t_i, t_f);
    else xy =fxfy2(p, psi_dd_f, t_i, t_f);
    return {fpsi(psi_dd_f, t_i, t_f), fpsi_d(psi_dd_f, t_i, t_f),
            psi_dd_f, xy.first, xy.second};
}
