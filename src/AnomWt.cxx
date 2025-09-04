#include "AnomWt.h"

void AnomWt::compute() {
  // 3) Build the tau‐pair rest frame
  std::array<double,4> QQ, PB1{0,0,0,1}, PB2{0,0,0,1}, PBB;
  for(int k=0; k<4; ++k) {
      QQ[k] = P1[k] + P2[k];
      // beam directions along ±z in tau‐pair frame
      PB1[k] = PB2[k] = 0.0;
  }

  //Reconstruction of the beam directions
  PB1[3] = +1.0; //e- along z direction
  PB2[3] = -1.0; //e+ along -z direction
  PB1[0] = 1.0;
  PB2[0] = 1.0;

  for(auto& arr : { &H1, &H2, &P1, &P2, &PB1, &PB2}) {
      KinLib::BostDQ(1, QQ, *arr, *arr);
  }

  // 5) Rotate about z to eliminate y‐components of P2
  double fi;
  double randSave = gRandom->Uniform();
  if(randSave < 1.0) {
      fi = KinLib::ANGFI(P2[1], P2[2]);
  } else {
      fi = KinLib::ANGFI(P1[1], P1[2]);
  }
  for(auto& arr : { &H1, &H2, &P1, &P2, &PB1, &PB2}) {
      KinLib::ROTOD3(-fi, *arr, *arr);
  }

  // 6) Rotate about y to align taus along z
  //double thet = std::acos(-PB1[3]/std::sqrt(PB1[1]*PB1[1] + PB1[2]*PB1[2] + PB1[3]*PB1[3]));
  double thet;
  if(randSave < 1.0) {
      thet = KinLib::ANGXY(P2[3], P2[1]);
  } else {
      thet = KinLib::ANGXY(P1[3], P1[1]);
  }
  for(auto& arr : { &H1, &H2, &P1, &P2, &PB1, &PB2}) {
      KinLib::ROTOD2(-thet, *arr, *arr);
  }


  // 7) Align beam‐difference to x–z plane
  switch(frameOption){
      case 1:
          for(int k=0; k<4; ++k) PBB[k] = PB2[k] - PB1[k];//Collins-Soper frame
          break;
      case 2:
          for(int k=0; k<4; ++k) PBB[k] = PB1[k];
          break;
      case 3:
          for(int k=0; k<4; ++k) PBB[k] = PB2[k];
          break;
  }

  double fi1 = KinLib::ANGFI(PBB[1], PBB[2]);
  for(auto& arr : { &H1, &H2, &P1, &P2, &PB1, &PB2}) {
              KinLib::ROTOD3(-fi1, *arr, *arr);
  }

  TVector3 p1(P1[1],P1[2],P1[3]);
  TVector3 p2(P2[1],P2[2],P2[3]);
  TVector3 pb1(PB1[1],PB1[2],PB1[3]);
  TVector3 pb2(PB2[1],PB2[2],PB2[3]);
  double theta1 =  p1.Unit().Angle(pb1.Unit());
  double theta2 =  p2.Unit().Angle(pb2.Unit());
  double T1 = PB1[0]*PB1[0]*(1.0+cos(theta1)*cos(theta1));
  double T2 = PB2[0]*PB2[0]*(1.0+cos(theta2)*cos(theta2));
  switch(frameOption){
      case 1:
          m_prob = 1.0;
          break;
      case 2:
          m_prob = T1/(T1+T2);
          break;
      case 3:
          m_prob = T2/(T1+T2);
          break;
  }


  //Finding Hard Photons
  std::array<double,4> TR;
  for(int k=0; k<4; ++k) TR[k] = P1[k]+P2[k];
  m_hardSoft =(TR[0]*TR[0])/(beamEnergy*beamEnergy);

  // 8) Final boosts of polarimeters and pions to tau rest frame
  for(auto& arr : { &H1}) {
      // Boost to tau- rest frame
      KinLib::BostDQ(1, P1, *arr, *arr);
  }
  for(auto& arr : { &H2}) {
      // Boost to tau+ rest frame
      KinLib::BostDQ(1, P2, *arr, *arr);
  }

  double E=P1[0];
  // 10) Compute angle with respect to tau-/z axis & prepare R0,R matrices
  switch(frameOption){
      case 1:
          m_theta = std::acos(-PB1[3]/std::sqrt(PB1[1]*PB1[1] + PB1[2]*PB1[2] + PB1[3]*PB1[3]));
          break;
      case 2:
          m_theta = std::acos(-PB2[3]/std::sqrt(PB2[1]*PB2[1] + PB2[2]*PB2[2] + PB2[3]*PB2[3]));
          break;
      case 3:
          m_theta = std::acos(-PB1[3]/std::sqrt(PB1[1]*PB1[1] + PB1[2]*PB1[2] + PB1[3]*PB1[3]));
          break;
  }

  double ReA, ImA, ReB, ImB, ReX, ImX, ReY, ImY;

  ReA = 0.0; ImA = 0.0;
  ReB = 0.0; ImB = 0.0;
  ReX = 0.0; ImX = 0.0;
  ReY = 0.0; ImY = 0.0;

  // baseline (no loops)
  DipoleEERij dipole_calculator1(0);
  auto R0 = dipole_calculator1.calculate(E, m_theta, ReA, ImA, ReB, ImB, ReX, ImX, ReY, ImY);

  // with anomalous couplings & loops
  DipoleEERij dipole_calculator2(1);
  auto R = dipole_calculator2.calculate(E, m_theta, Ar0, Ai0, Br0, Bi0, Ar0, Ai0, Br0, Bi0);

  // 10) Extract weights
  m_wtME    = R[3][3] / R0[3][3];

  // Change the format of polarimetric vectors to match the expected format
  std::array<double,4> H1_copy = H1;
  std::array<double,4> H2_copy = H2;
  for(int k=0; k<3; ++k) {
      H1[k] = H1_copy[k+1];
      H2[k] = H2_copy[k+1];
  }
  H1[3] = H1_copy[0]; // Time component
  H2[3] = H2_copy[0]; // Time component


  // spin‐weight numerator/denominator
  double sign[4] = {1., -1., 1., -1.};
  m_wtSPIN0 = m_wtSPIN = 0.0;
  for(int i=0; i<4; ++i) {
      for(int j=0; j<4; ++j) {
          m_wtSPIN  += R[i][j]/R[3][3]  * H1[i] * H2[j] * sign[i] * sign[j];
          m_wtSPIN0 += R0[i][j]/R0[3][3]* H1[i] * H2[j] * sign[i] * sign[j];
      }
  }

  // New add by AT
  // Helicity approximated weight calulation
  double wtw[2][2] = {0.0};
  m_spinWeight_approx= 0.0;
  for (int m=0; m<2; ++m) {
      for (int n=0; n<2; ++n) {
          double sign_m = (m == 0) ? -1 : 1;
          double sign_n = (n == 0) ? -1 : 1;
          double term1 = H1[3] - sign_m * H1[2];
          double term2 = (R0[3][3] - sign_n * R0[3][2] + sign_m * R0[2][3] - sign_m * sign_n * R0[2][2])/R0[3][3];
          double term3 = H2[3] + sign_n * H2[2];
          wtw[m][n] = term1 * term2 * term3;
          m_spinWeight_approx += wtw[m][n];
      }
  }
  m_spinWeight_approx /= 4.0;  // average over 4 combinations

  // normalize to make probabilities
  double wts = wtw[0][0] + wtw[0][1] + wtw[1][0] + wtw[1][1];
  wtw[0][0]=wtw[0][0]/wts;
  wtw[0][1]=wtw[0][0]+wtw[0][1]/wts;
  wtw[1][0]=wtw[0][1]+wtw[1][0]/wts;
  wtw[1][1]=wtw[1][0]+wtw[1][1]/wts;

  double rndm = gRandom->Uniform();

  m_hel1=0, m_hel2=0;
  if(rndm<wtw[0][0]){m_hel1=-1; m_hel2=-1;}   //attribute approx helicities. Signs need to be fixed.
  else if(rndm<wtw[0][1]){m_hel1=-1; m_hel2= 1;}
  else if(rndm<wtw[1][0]){m_hel1= 1; m_hel2=-1;}
  else if(rndm<wtw[1][1]){m_hel1= 1; m_hel2= 1;}

}
