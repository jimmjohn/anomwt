#include <iostream>
#include <fstream>
#include <sstream>

#include <TLatex.h>
#include <TVector3.h>
#include <TApplication.h>
#include <TMath.h>

#include "AnomWt.h"
#include "HistManager.h"
#include "EventInitilizers.h"
#include "HepMCReader.h"
#include "Observables.h"
#include "PhysicsConstants.h"

#include "HepMC3/ReaderAscii.h"
#include "HepMC3/GenEvent.h"

#include "DipoleEERij.h"



int main(int argc, char** argv) {
    TApplication theApp("App", &argc, argv);  // removes ROOT args like -b, etc.
    // std::string filename;
    // int maxEvents = 1000000; // default Modify to parse from command line if needed

    const char* filename = theApp.Argv()[1];//argv[1] will not work as TApplication eats ROOT options (like -b, -q, etc.), and rewrites argc/argv
    std::ifstream infile(filename);
    std::cout << "============================================================\n";
    std::cout << "   Demo program associated with preprint:\n";
    std::cout << "   'arXiv:2509.04400 [hep-ph]'\n";
    std::cout << "   Authors: Jim John (jim.john@ifj.edu.pl)\n";
    std::cout << "            Ananya Tapadar (ananya.tapadar@ifj.edu.pl)\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "   Purpose:\n";
    std::cout << "   Using polarimetric vectors and helicity-like quantities\n";
    std::cout << "   from HepMC3 files filled in by KKMCee.\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "   Version: Sept 4, 2025\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "   Notes:\n";
    std::cout << "   * Algorithm works for any tau decay modes.\n";
    std::cout << "   * Demo plots at present are prepared only for:\n";
    std::cout << "       tau -> pi+ pi0 nu\n";
    std::cout << "   * Other decay modes require distinct plots.\n";
    std::cout << "============================================================\n";
    if (!infile) {
        std::cout << "Error: cannot open '" << filename << "'.\n";
        return 1;
    }
    std::string line;

    EventInitilizers evtIn;
    HistManager* histSave = new HistManager();

    int nevts = 0; // Event counter
    int printEvts = 0;
    int countSelected = 0;
    double beamEnergy;
    double invariantCut = 3.0; // GeV
    double sum_m2OverE2CS = 0.0;


    //Try reading using HepMC3 Reader
    HepMC3::ReaderAscii reader(filename);
    if (reader.failed()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }
    HepMC3::GenEvent evt;
    HepMCReader readEvent;

    while (reader.read_event(evt)) {
        if (reader.failed()) break;
        // Skip empty lines

        bool selected = true;;

        if(nevts > 1000000) break; // Limit to 100000 events
        evtIn = {};
        if(nevts<printEvts){std::cout<< "\n"<< "Evt number: "<<nevts<<std::endl;}
        if(nevts%1000000==0){std::cout<< "\n"<< "Evt number: "<<nevts<<std::endl;}
        nevts++;

        readEvent.ReadAndFillEvent(evtIn, evt);

        int frameOption = 1;
        double acc_angle, y1y2;

        if(evtIn.P1[0]==0 || evtIn.P2[0]==0) continue; //skip if tau+ or tau- not found
        if(evtIn.PIPL[0]==0 || evtIn.PIPM[0]==0) continue; //skip if pi+ or pi- not found
        if(evtIn.heTaum==0 || evtIn.heTaul==0) continue; //skip if helicities not found
        if(evtIn.pvTaum_found==false || evtIn.pvTaul_found==false) continue; //skip if polarimetric vectors not found


        histSave->tauZMomenta->Fill(evtIn.P1[3]);
        histSave->tauZMomenta->Fill(evtIn.P2[3]);


        //Observables calculation
        Observables obs;
        obs.Acoplanarity(evtIn);
        acc_angle = obs.acoplanarity_angle;
        y1y2 = obs.y1 * obs.y2;

        AnomWt anomwtCS1, anomwtCS2, anomwtCS3;
        anomwtCS1.setCouplings(0.04, 0.0, 0.0, 0.0);   //Left Plot
        anomwtCS2.setCouplings(0.0, 0.0, 0.04, 0.0);   //Middle Plot
        anomwtCS3.setCouplings(0.02828, 0.0, 0.02828, 0.0); // Right Plot
        anomwtCS1.setKinematics(evtIn);
        anomwtCS2.setKinematics(evtIn);
        anomwtCS3.setKinematics(evtIn);
        anomwtCS1.setOptions(frameOption, nevts, printEvts);
        anomwtCS2.setOptions(frameOption, nevts, printEvts);
        anomwtCS3.setOptions(frameOption, nevts, printEvts);
        anomwtCS1.compute();
        anomwtCS2.compute();
        anomwtCS3.compute();


        //if(!anomwtCS1.selected())std::cout<<"selected: "<<anomwtCS1.selected()<<std::endl;
        if(anomwtCS1.hardSoft()<0.02) {
        histSave->helicity_corr->Fill(evtIn.heTaum, evtIn.heTaul);
        histSave->helicity_corr_standalone->Fill(anomwtCS1.approxHel1(), anomwtCS1.approxHel2());
        histSave->wt_corr_KT_KA->Fill(evtIn.wt, evtIn.wt_approx);
        histSave->wt_corr_KT_ST->Fill(evtIn.wt, anomwtCS1.wtSPIN0());
        histSave->wt_corr_KT_SA->Fill(evtIn.wt, anomwtCS1.spinApproxWt());
        histSave->wt_corr_KA_SA->Fill(evtIn.wt_approx, anomwtCS1.spinApproxWt());
        histSave->wt_corr_ST_SA->Fill(anomwtCS1.wtSPIN0(), anomwtCS1.spinApproxWt());
        }

        //std::cout<<"Selected events: "<<countSelected<<" out of "<<nevts<<" events"<< " hardSoft="<<anomwtCS1.hardSoft()<<std::endl;

        histSave->hardSoft_Histo->Fill(anomwtCS1.hardSoft());

        if(y1y2 > 0.0 && anomwtCS1.hardSoft()<0.02 ) {
            histSave->acoplanarity_angle1->Fill(acc_angle, anomwtCS1.wtSPIN0()/evtIn.wt);
            histSave->h_angle_01->Fill(acc_angle, anomwtCS1.wtME());
            histSave->h_angle1->Fill(acc_angle, anomwtCS1.wtSPIN()/anomwtCS1.wtSPIN0()*anomwtCS1.wtME());
        }
        if(y1y2 > 0.0 && anomwtCS2.hardSoft()<0.02) {
            histSave->acoplanarity_angle2->Fill(acc_angle, anomwtCS2.wtSPIN0()/evtIn.wt);
            histSave->h_angle_02->Fill(acc_angle, anomwtCS2.wtME());
            histSave->h_angle2->Fill(acc_angle, anomwtCS2.wtSPIN()/anomwtCS2.wtSPIN0()*anomwtCS2.wtME());
        }
        if(y1y2 > 0.0 && anomwtCS3.hardSoft()<0.02) {
            histSave->acoplanarity_angle3->Fill(acc_angle, anomwtCS3.wtSPIN0()/evtIn.wt);
            histSave->h_angle_03->Fill(acc_angle, anomwtCS3.wtME());
            histSave->h_angle3->Fill(acc_angle, anomwtCS3.wtSPIN()/anomwtCS3.wtSPIN0()*anomwtCS3.wtME());
        }

        // wtSPIN0 = anomwtCS1.wtSPIN0()/evtIn.wt*anomwtCS1.wtME();
        // wtSPIN = anomwtCS1.wtSPIN()/evtIn.wt*anomwtCS1.wtME();

        double E2CS = pow(anomwtCS1.Invariant(),2);
        if (E2CS > 0 && anomwtCS1.Invariant() < invariantCut) {
            sum_m2OverE2CS += 1 / E2CS;
            countSelected++;
        }

        //Mustral Frame
        frameOption=2;
        AnomWt anomwtPB1;
        anomwtPB1.setCouplings(0.0, 0.0, 0.0, 0.0);
        anomwtPB1.setKinematics(evtIn);
        anomwtPB1.setOptions(frameOption, nevts, printEvts);
        anomwtPB1.compute();

        frameOption=3;
        AnomWt anomwtPB2;
        anomwtPB2.setCouplings(0.0, 0.0, 0.0, 0.0);
        anomwtPB2.setKinematics(evtIn);
        anomwtPB2.setOptions(frameOption, nevts, printEvts);
        anomwtPB2.compute();


        double wtMustraal0 = anomwtPB1.prob()*anomwtPB1.wtSPIN0() + anomwtPB2.prob()*anomwtPB2.wtSPIN0();
        double wtMustraal = anomwtPB1.prob()*anomwtPB1.wtSPIN() + anomwtPB2.prob()*anomwtPB2.wtSPIN();

        double thetaMustraal;
        if(anomwtPB1.prob()>anomwtPB2.prob()) {thetaMustraal = anomwtPB1.theta();}
        else {thetaMustraal = anomwtPB2.theta();}

        //std::cout<<"Prob sum: "<<anomwtPB1.prob()+anomwtPB2.prob()<<std::endl;

        // if(prob2>0.5){
        //     wtMustraal0 = wtSPIN02;
        // } else if(prob3>0.5) {
        //     wtMustraal0 = wtSPIN03;
        // } else{
        //     wtMustraal0 = prob2*wtSPIN02 + prob3*wtSPIN03;
        // }

        if(anomwtCS1.hardSoft()<=0.2) {
            histSave->collins_soper_corr_soft->Fill(evtIn.wt, anomwtCS1.wtSPIN0());
            histSave->p1_frame_corr_soft->Fill(evtIn.wt, anomwtPB1.wtSPIN0());
            histSave->p2_frame_corr_soft->Fill(evtIn.wt, anomwtPB2.wtSPIN0());
            histSave->mustraal_corr_soft->Fill(evtIn.wt, wtMustraal0);
        } else if(anomwtCS1.hardSoft()<0.98 && anomwtCS1.hardSoft()>0.2) {
            histSave->collins_soper_corr_hard->Fill(evtIn.wt, anomwtCS1.wtSPIN0());
            histSave->p1_frame_corr_hard->Fill(evtIn.wt, anomwtPB1.wtSPIN0());
            histSave->p2_frame_corr_hard->Fill(evtIn.wt, anomwtPB2.wtSPIN0());
            histSave->mustraal_corr_hard->Fill(evtIn.wt, wtMustraal0);
        }

        beamEnergy = evtIn.beamEnergy;

        if(anomwtCS1.Invariant()<invariantCut) histSave->theta_dist_cs->Fill(cos(anomwtCS1.theta()));
        if(anomwtPB1.Invariant()<invariantCut) histSave->theta_dist_ms->Fill(cos(thetaMustraal));
        histSave->Invariant_dist->Fill(anomwtCS1.Invariant());

        //std::cout<<"cosditrctTheta: "<<std::cos(anomwtPB1.directThetaVal())<<" mustralTheta: "<<std::cos(thetaMustraal)<<std::endl;
        histSave->directTheta_dist->Fill(std::cos(anomwtPB1.directThetaVal()));
        //if(anomwtCS1.Invariant()>beamEnergy/2.0-0



    }


    double avg_m2OverE2 = 0.0;
    if (countSelected > 0) avg_m2OverE2 = pow(Physics::m_tau,2)* sum_m2OverE2CS / countSelected;
    // std::cout << "<m^2/E^2> = " << avg_m2OverE2 << std::endl;


    Int_t ba=0;
    for (double costheta = -1; costheta <= 1; costheta += 0.001) {
        ba++;
        double energy = beamEnergy/2.0;
        double theta = std::acos(costheta);
        DipoleEERij dipole_calculator3(0);
        auto RMat = dipole_calculator3.calculate(energy, theta, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        double Rtt_theory = RMat[3][3];   // no arbitrary factor
        histSave->Rtt->SetPoint(ba, costheta, Rtt_theory);
    }

    histSave->ratio_angle1 = (TH1D*)histSave->h_angle1->Clone("ratio_angle1");
    histSave->ratio_angle1->Divide(histSave->h_angle_01);
    histSave->ratio_angle2 = (TH1D*)histSave->h_angle2->Clone("ratio_angle2");
    histSave->ratio_angle2->Divide(histSave->h_angle_02);
    histSave->ratio_angle3 = (TH1D*)histSave->h_angle3->Clone("ratio_angle3");
    histSave->ratio_angle3->Divide(histSave->h_angle_03);

    histSave->collins_by_mustraal = (TH2F*)histSave->collins_soper_corr_hard->Clone("collins_by_mustraal");
    histSave->collins_by_mustraal->Divide(histSave->mustraal_corr_hard);


    // Draw all canvases
    histSave->DrawHistograms(beamEnergy, avg_m2OverE2);


//    theApp.Run();  // Keeps the GUI open

    return 0;
}
