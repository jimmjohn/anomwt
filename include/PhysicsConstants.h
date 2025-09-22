#pragma once

namespace Physics {
constexpr double m_tau = 1.77686; // Tau mass in GeV
constexpr double m_mu = 0.105658; // Muon mass in GeV
constexpr double m_pi = 0.139570; // Charged pion mass in GeV
constexpr double m_rho = 0.77526; // Rho meson mass in GeV
}

namespace PDG {
    enum class ParticleID {
        electron = 11,
        positron = -11,
        muon     = 13,
        tau      = 15
    };
}