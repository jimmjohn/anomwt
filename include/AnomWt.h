#ifndef ANOMWT_CLASS_H
#define ANOMWT_CLASS_H

#include <array>
#include <cmath>
#include <iostream>
#include "KinLib.h"
#include "DipoleEERij.h"
#include "EventInitilizers.h"
#include <TVector3.h>
#include <TRandom3.h>


class AnomWt {
public:
    // ---- Configuration / inputs ----
    void setCouplings(double Ar, double Ai, double Br, double Bi) {
        Ar0 = Ar; Ai0 = Ai; Br0 = Br; Bi0 = Bi;
    }

    void setKinematics(EventInitilizers& evtIn) {
        H1 = evtIn.m_HvCloneTaum;
        H2 = evtIn.m_HvCloneTaul;
        P1 = evtIn.P1;
        P2 = evtIn.P2;
        beamEnergy = evtIn.beamEnergy;
    }

    // frameOption: 1 = Collins–Soper, 2 = use PB1, 3 = use PB2.
    void setOptions(int frameOptionI, int nevtsI = 0, int printEvtsI = 0) {
        frameOption = frameOptionI;
        nevts = nevtsI;
        printEvts = printEvtsI;
    }

    // ---- Do the computation ----
    void compute();

    // ---- Outputs (getters) ----
    double wtME()        const { return m_wtME; }
    double wtSPIN()      const { return m_wtSPIN; }
    double wtSPIN0()     const { return m_wtSPIN0; }
    double theta()       const { return m_theta; }
    double hardSoft()    const { return m_hardSoft; }
    double prob()        const { return m_prob; }
    double spinApproxWt()  const { return m_spinWeight_approx; }
    int    approxHel1()        const { return m_hel1; }
    int    approxHel2()        const { return m_hel2; }

    // If you prefer public fields, you can expose these directly instead of getters.

private:
    // Inputs
    double Ar0{0.0}, Ai0{0.0}, Br0{0.0}, Bi0{0.0};
    std::array<double,4> H1{0,0,0,0}, H2{0,0,0,0};
    std::array<double,4> P1{0,0,0,0}, P2{0,0,0,0};
    double beamEnergy{0.0};
    int frameOption{1};
    int nevts{0}, printEvts{0};

    // Outputs
    double m_wtME{1.0}, m_wtSPIN{1.0}, m_wtSPIN0{1.0};
    double m_theta{0.0}, m_hardSoft{0.0}, m_prob{1.0};
    double m_spinWeight_approx{0.0};
    int m_hel1{0}, m_hel2{0};
};

#endif // ANOMWT_CLASS_H
