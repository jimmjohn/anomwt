#pragma once
#include <array>
#include <string>
#include <TH1D.h>
#include <TH2F.h>
#include <TMath.h>


class HistManager {
public:
  HistManager() = default;
  ~HistManager();
  // Histograms
    TH2F* helicity_corr = new TH2F("helicity_corr", "Helicity1 vs Helicity2;Helicity1;Helicity2", 3, -1.5, 1.5, 3, -1.5, 1.5);
    TH2F* helicity_corr_standalone = new TH2F("helicity_corr_standalone", "Helicity1 vs Helicity2 (Standalone);Helicity1_StandAlone;Helicity2_StandAlone", 3, -1.5, 1.5, 3, -1.5, 1.5);
    TH2F* wt_corr_KT_KA = new TH2F("wt_corr_KT_KA", "wt correlation (KT-KA);wt_KT;wt_KA", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* wt_corr_KT_ST = new TH2F("wt_corr_KT_ST", "wt correlation (KT-ST);wt_KT;wt_ST", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* wt_corr_KT_SA = new TH2F("wt_corr_KT_SA", "wt correlation (KT-SA);wt_KT;wt_SA", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* wt_corr_KA_SA = new TH2F("wt_corr_KA_SA", "wt correlation (KA-SA);wt_KA;wt_SA", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* wt_corr_ST_SA = new TH2F("wt_corr_ST_SA", "wt correlation (ST-SA);wt_ST;wt_SA", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* acoplanarity_angle1 = new TH2F("acoplanarity_angle1", "Acoplanarity angle;#theta_{1};#theta_{2}", 100, 0.5, TMath::Pi()/2., 100, 0, 4.0);
    TH1D* h_angle1 = new TH1D("angle1", "Acoplanarity angle1", 100, 0, 2.0*TMath::Pi());
    TH1D* h_angle_01 = new TH1D("angle_01", "Acoplanarity angle01", 100, 0, 2.0*TMath::Pi());
    TH2F* acoplanarity_angle2 = new TH2F("acoplanarity_angle2", "Acoplanarity angle;#theta_{1};#theta_{2}", 100, 0.5, TMath::Pi()/2., 100, 0, 4.0);
    TH1D* h_angle2 = new TH1D("angle2", "Acoplanarity angle2", 100, 0, 2.0*TMath::Pi());
    TH1D* h_angle_02 = new TH1D("angle_02", "Acoplanarity angle02", 100, 0, 2.0*TMath::Pi());
    TH2F* acoplanarity_angle3 = new TH2F("acoplanarity_angle3", "Acoplanarity angle;#theta_{1};#theta_{2}", 100, 0.5, TMath::Pi()/2., 100, 0, 4.0);
    TH1D* h_angle3 = new TH1D("angle3", "Acoplanarity angle3", 100, 0, 2.0*TMath::Pi());
    TH1D* h_angle_03 = new TH1D("angle_03", "Acoplanarity angle03", 100, 0, 2.0*TMath::Pi());
    TH1D* hardSoft_Histo = new TH1D("hardSoft", "hardSoft",100,0.,2.);
    TH2F* collins_soper_corr = new TH2F("collins_soper_corr", "Collins Soper Correlation;wt_KKMCee;wt_StandAlone", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* p1_frame_corr = new TH2F("p1_frame_corr", "P1 Frame Correlation;wt_KKMCee;wt_StandAlone", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* p2_frame_corr = new TH2F("p2_frame_corr", "P2 Frame Correlation;wt_KKMCee;wt_StandAlone", 100, 0, 4.0, 100, 0, 4.0);
    TH2F* mustraal_corr = new TH2F("mustraal_corr", "Mustraal Correlation;wt_KKMCee;wt_StandAlone", 100, 0, 4.0, 100, 0, 4.0);


    TH1D* ratio_angle1 = nullptr;
    TH1D* ratio_angle2 = nullptr;
    TH1D* ratio_angle3 = nullptr;
    TH2F* collins_by_mustraal = nullptr;

    void DrawHistograms();

};