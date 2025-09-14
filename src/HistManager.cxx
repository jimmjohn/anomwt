#include "HistManager.h"

#include <TMath.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TPostScript.h>
#include <TLatex.h>
#include <TLine.h>


HistManager::~HistManager() {
}

void HistManager::DrawHistograms() {
    TDirectory* currentDir = gDirectory;

    // Create a new directory for the histograms
    TDirectory* histDir = currentDir->mkdir("Histograms");
    histDir->cd();
    //TPostScript ps("output_histos.ps",111);
    //ps.Range(20,30); //ps.Range(10,20);

        // Draw the histogram
    TCanvas* c1 = new TCanvas("c1", "Helicity Correlation", 800, 600);
    helicity_corr->SetStats(0);
    helicity_corr->GetXaxis()->SetTitle("Helicity of #tau^{-}");
    helicity_corr->GetYaxis()->SetTitle("Helicity of #tau^{+}");
    helicity_corr->SetTitle("Helicity Correlation at 10 GeV with spin weight");
    helicity_corr->GetXaxis()->CenterTitle();
    helicity_corr->GetYaxis()->CenterTitle();
    helicity_corr->SetMarkerStyle(20);
    helicity_corr->SetMarkerColor(kBlack);
    c1->SetGrid();
    helicity_corr->Draw("COLZ TEXT");
    c1->Update();

    //ps.NewPage();
    TCanvas* c2 = new TCanvas("c2", "WT Correlation", 800, 600);
    wt_corr_KT_KA->SetStats(0);
    wt_corr_KT_KA->GetXaxis()->SetTitle("SpinWT");
    wt_corr_KT_KA->GetYaxis()->SetTitle("SpinWThelApprox");
    wt_corr_KT_KA->SetTitle("SpinWT Correlation at 10.58 GeV without spin weight");
    wt_corr_KT_KA->GetXaxis()->CenterTitle();
    wt_corr_KT_KA->GetYaxis()->CenterTitle();
    wt_corr_KT_KA->SetMarkerStyle(20);
    wt_corr_KT_KA->SetMarkerSize(0.5);
    wt_corr_KT_KA->SetMarkerColor(kBlue);
    c2->SetGrid();
    wt_corr_KT_KA->Draw("COLZ");
    TLatex tex;
    tex.SetTextSize(0.04);
    tex.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_KT_KA->GetCorrelationFactor()));
    c2->Update();

    //ps.NewPage();
    // Draw acoplanarity angle
    TCanvas* c3 = new TCanvas("c3", "Acoplanarity Angle", 800, 600);
    acoplanarity_angle1->SetStats(0);
    acoplanarity_angle1->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    acoplanarity_angle1->GetYaxis()->SetTitle("Spin Weight");
    acoplanarity_angle1->SetTitle("Acoplanarity Angle vs Spin Weight at 10 GeV with spin weight");
    acoplanarity_angle1->GetXaxis()->CenterTitle();
    acoplanarity_angle1->GetYaxis()->CenterTitle();
    acoplanarity_angle1->SetMarkerStyle(20);
    acoplanarity_angle1->SetMarkerSize(0.5);
    acoplanarity_angle1->SetMarkerColor(kRed);
    c3->SetGrid();
    acoplanarity_angle1->Draw("COLZ");
    c3->Update();

    //ps.NewPage();
    TCanvas* c4 = new TCanvas("c4", "Acoplanarity Angle 0 vs Spin Weight", 800, 600);
    // h_angle_0->SetStats(0);
    // h_angle_0->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    // h_angle_0->GetYaxis()->SetTitle("Events");
    // h_angle_0->SetTitle("Acoplanarity Angle vs Events at 10 GeV without spin weight");
    // h_angle_0->GetXaxis()->CenterTitle();
    // h_angle_0->GetYaxis()->CenterTitle();
    h_angle_01->SetMarkerStyle(20);
    h_angle_01->SetMarkerSize(0.5);
    h_angle_01->SetMarkerColor(kBlue);
    c4->SetGrid();
    h_angle_01->Draw("E1");
    c4->Update();

    //ps.NewPage();
    TCanvas* c5 = new TCanvas("c5", "Acoplanarity Angle vs Spin Weight", 800, 600);
    //h_angle->SetStats(0);
    //h_angle->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    //h_angle->GetYaxis()->SetTitle("Events");
    //h_angle->SetTitle("Acoplanarity Angle vs Events at 10 GeV with spin weight");
    h_angle1->GetXaxis()->CenterTitle();
    h_angle1->GetYaxis()->CenterTitle();
    h_angle1->SetMarkerStyle(20);
    h_angle1->SetMarkerSize(0.5);
    h_angle1->SetMarkerColor(kRed);
    c5->SetGrid();
    h_angle1->Draw("E1");
    c5->Update();

    //ps.NewPage();
    TCanvas* c6 = new TCanvas("c6", "Ratio of Acoplanarity Angles", 1200, 600);
    c6->Divide(3,1);
    c6->cd(1);
    ratio_angle1->SetStats(0);
    //ratio_angle->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    ratio_angle1->GetXaxis()->SetTitle("#phi (radians)");
    ratio_angle1->GetYaxis()->SetTitle("wt_{spin}");
    ratio_angle1->SetTitle("");
    ratio_angle1->GetXaxis()->CenterTitle();
    ratio_angle1->GetYaxis()->CenterTitle();
    ratio_angle1->GetXaxis()->SetLabelSize(0.05);
    ratio_angle1->GetYaxis()->SetLabelSize(0.05);
    ratio_angle1->GetXaxis()->SetTitleSize(0.05);
    ratio_angle1->GetYaxis()->SetTitleSize(0.05);
    ratio_angle1->GetYaxis()->SetRangeUser(0.99,1.01);
    ratio_angle1->SetMarkerStyle(20);
    ratio_angle1->SetMarkerSize(0.5);
    ratio_angle1->SetMarkerColor(kGreen);
    //ratio_angle1->GetXaxis()->SetLabelSize(0.0);
    //ratio_angle->GetXaxis()->SetNdivisions(6);
    gPad->SetLeftMargin(0.2);
    gPad->SetGridx(true);
    ratio_angle1->GetXaxis()->SetNdivisions(4, kFALSE);
    ratio_angle1->GetXaxis()->ChangeLabel(1, -1, -1, -1, -1, -1, "0");
    ratio_angle1->GetXaxis()->ChangeLabel(2, -1, -1, -1, -1, -1, "#pi/2");
    ratio_angle1->GetXaxis()->ChangeLabel(3, -1, -1, -1, -1, -1, "#pi");
    ratio_angle1->GetXaxis()->ChangeLabel(4, -1, -1, -1, -1, -1, "3#pi/2");
    ratio_angle1->GetXaxis()->ChangeLabel(5, -1, -1, -1, -1, -1, "2#pi");
    ratio_angle1->Draw("HIST");
    // Horizontal guide at y=1 across the full x-range
    TLine* y1 = new TLine(0, 1.0, 2*TMath::Pi(), 1.0);
    y1->SetLineStyle(2);       // dashed
    y1->SetLineWidth(1);
    // y1->SetLineColor(kGray+2); // optional
    y1->Draw("same");
    gPad->Update(); // Update the pad to reflect the new axis

    c6->cd(2);
    ratio_angle2->SetStats(0);
    //ratio_angle->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    ratio_angle2->GetXaxis()->SetTitle("#phi (radians)");
    ratio_angle2->GetYaxis()->SetTitle("wt_{spin}");
    ratio_angle2->SetTitle("");
    ratio_angle2->GetXaxis()->CenterTitle();
    ratio_angle2->GetYaxis()->CenterTitle();
    ratio_angle2->GetXaxis()->SetLabelSize(0.05);
    ratio_angle2->GetYaxis()->SetLabelSize(0.05);
    ratio_angle2->GetXaxis()->SetTitleSize(0.05);
    ratio_angle2->GetYaxis()->SetTitleSize(0.05);
    ratio_angle2->GetYaxis()->SetRangeUser(0.99,1.01);
    ratio_angle2->SetMarkerStyle(20);
    ratio_angle2->SetMarkerSize(0.5);
    ratio_angle2->SetMarkerColor(kGreen);
    gPad->SetGridx(true);
    gPad->SetLeftMargin(0.2);
    ratio_angle2->GetXaxis()->SetNdivisions(4, kFALSE);
    ratio_angle2->GetXaxis()->ChangeLabel(1, -1, -1, -1, -1, -1, "0");
    ratio_angle2->GetXaxis()->ChangeLabel(2, -1, -1, -1, -1, -1, "#pi/2");
    ratio_angle2->GetXaxis()->ChangeLabel(3, -1, -1, -1, -1, -1, "#pi");
    ratio_angle2->GetXaxis()->ChangeLabel(4, -1, -1, -1, -1, -1, "3#pi/2");
    ratio_angle2->GetXaxis()->ChangeLabel(5, -1, -1, -1, -1, -1, "2#pi");
    ratio_angle2->Draw("HIST");
    y1->Draw("same");
    gPad->Update(); // Update the pad to reflect the new axis


    c6->cd(3);
    ratio_angle3->SetStats(0);
    //ratio_angle->GetXaxis()->SetTitle("Acoplanarity Angle (degrees)");
    ratio_angle3->GetXaxis()->SetTitle("#phi (radians)");
    ratio_angle3->GetYaxis()->SetTitle("wt_{spin}");
    ratio_angle3->SetTitle("");
    ratio_angle3->GetXaxis()->CenterTitle();
    ratio_angle3->GetYaxis()->CenterTitle();
    ratio_angle3->GetXaxis()->SetLabelSize(0.05);
    ratio_angle3->GetYaxis()->SetLabelSize(0.05);
    ratio_angle3->GetXaxis()->SetTitleSize(0.05);
    ratio_angle3->GetYaxis()->SetTitleSize(0.05);
    ratio_angle3->GetYaxis()->SetRangeUser(0.99,1.01);
    ratio_angle3->SetMarkerStyle(20);
    ratio_angle3->SetMarkerSize(0.5);
    ratio_angle3->SetMarkerColor(kGreen);
    gPad->SetGridx(true);
    gPad->SetLeftMargin(0.2);
    ratio_angle3->GetXaxis()->SetNdivisions(4, kFALSE);
    ratio_angle3->GetXaxis()->ChangeLabel(1, -1, -1, -1, -1, -1, "0");
    ratio_angle3->GetXaxis()->ChangeLabel(2, -1, -1, -1, -1, -1, "#pi/2");
    ratio_angle3->GetXaxis()->ChangeLabel(3, -1, -1, -1, -1, -1, "#pi");
    ratio_angle3->GetXaxis()->ChangeLabel(4, -1, -1, -1, -1, -1, "3#pi/2");
    ratio_angle3->GetXaxis()->ChangeLabel(5, -1, -1, -1, -1, -1, "2#pi");
    ratio_angle3->Draw("HIST");
    y1->Draw("same");
    gPad->Update(); // Update the pad to reflect the new axis
    c6->Update();

    //ps.NewPage();
    TCanvas* c7 = new TCanvas("c7","weight_correlations",1200,1200);
    c7->Divide(2,2);
    c7->cd(1);
    collins_soper_corr->Draw("colz");
    c7->cd(2);
    p1_frame_corr->Draw("colz");
    c7->cd(3);
    p2_frame_corr->Draw("colz");
    c7->cd(4);
    mustraal_corr->Draw("colz");
    c7->Update();

    //ps.NewPage();
    TCanvas* c8 = new TCanvas("c8", "hardSoft" ,800,600);
    c8->cd();
    hardSoft_Histo->Draw();
    c8->Update();

    //ps.NewPage();
    TCanvas* c9 = new TCanvas("c9", "collins_by_mustraal" ,800,600);
    c9->cd();
    collins_by_mustraal->SetTitle("collins_by_mustraal");
    collins_by_mustraal->GetZaxis()->SetRangeUser(0,2.);
    collins_by_mustraal->Draw("colz");
    c9->Update();


    TCanvas* c10 = new TCanvas("c10", "Helicity Correlation_Standalone", 800, 600);
    helicity_corr_standalone->SetStats(0);
    helicity_corr_standalone->GetXaxis()->CenterTitle();
    helicity_corr_standalone->GetYaxis()->CenterTitle();
    helicity_corr_standalone->SetMarkerStyle(20);
    helicity_corr_standalone->SetMarkerColor(kBlack);
    c10->SetGrid();
    helicity_corr_standalone->Draw("COLZ TEXT");
    c10->Update();

    //ps.NewPage();
    TCanvas* c11 = new TCanvas("c11", "WT Correlation KT KA", 800, 600);
    wt_corr_KT_KA->SetStats(0);
    wt_corr_KT_KA->GetXaxis()->CenterTitle();
    wt_corr_KT_KA->GetYaxis()->CenterTitle();
    wt_corr_KT_KA->SetMarkerStyle(20);
    wt_corr_KT_KA->SetMarkerSize(0.5);
    wt_corr_KT_KA->SetMarkerColor(kBlue);
    c11->SetGrid();
    wt_corr_KT_KA->Draw("COLZ");
    TLatex texx;
    texx.SetTextSize(0.04);
    texx.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_KT_KA->GetCorrelationFactor()));
    c11->Update();

    TCanvas* c12 = new TCanvas("c12", "WT Correlation KT ST", 800, 600);
    wt_corr_KT_ST->SetStats(0);
    wt_corr_KT_ST->GetXaxis()->CenterTitle();
    wt_corr_KT_ST->GetYaxis()->CenterTitle();
    wt_corr_KT_ST->SetMarkerStyle(20);
    wt_corr_KT_ST->SetMarkerSize(0.5);
    wt_corr_KT_ST->SetMarkerColor(kBlue);
    c12->SetGrid();
    wt_corr_KT_ST->Draw("COLZ");
    TLatex texx2;
    texx2.SetTextSize(0.04);
    texx2.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_KT_ST->GetCorrelationFactor()));
    c12->Update();

    TCanvas* c13 = new TCanvas("c13", "WT Correlation KT SA", 800, 600);
    wt_corr_KT_SA->SetStats(0);
    wt_corr_KT_SA->GetXaxis()->CenterTitle();
    wt_corr_KT_SA->GetYaxis()->CenterTitle();
    wt_corr_KT_SA->SetMarkerStyle(20);
    wt_corr_KT_SA->SetMarkerSize(0.5);
    wt_corr_KT_SA->SetMarkerColor(kBlue);
    c13->SetGrid();
    wt_corr_KT_SA->Draw("COLZ");
    TLatex texx3;
    texx3.SetTextSize(0.04);
    texx3.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_KT_SA->GetCorrelationFactor()));
    c13->Update();

    TCanvas* c14 = new TCanvas("c14", "WT Correlation KA SA", 800, 600);
    wt_corr_KA_SA->SetStats(0);
    wt_corr_KA_SA->GetXaxis()->CenterTitle();
    wt_corr_KA_SA->GetYaxis()->CenterTitle();
    wt_corr_KA_SA->SetMarkerStyle(20);
    wt_corr_KA_SA->SetMarkerSize(0.5);
    wt_corr_KA_SA->SetMarkerColor(kBlue);
    c14->SetGrid();
    wt_corr_KA_SA->Draw("COLZ");
    TLatex texx4;
    texx4.SetTextSize(0.04);
    texx4.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_KA_SA->GetCorrelationFactor()));
    c14->Update();

    TCanvas* c15 = new TCanvas("c15", "WT Correlation KA SA", 800, 600);
    wt_corr_ST_SA->SetStats(0);
    wt_corr_ST_SA->GetXaxis()->CenterTitle();
    wt_corr_ST_SA->GetYaxis()->CenterTitle();
    wt_corr_ST_SA->SetMarkerStyle(20);
    wt_corr_ST_SA->SetMarkerSize(0.5);
    wt_corr_ST_SA->SetMarkerColor(kBlue);
    c15->SetGrid();
    wt_corr_ST_SA->Draw("COLZ");
    TLatex texx5;
    texx5.SetTextSize(0.04);
    texx5.DrawLatexNDC(0.15, 0.8, Form("Correlation Factor: %.2f", wt_corr_ST_SA->GetCorrelationFactor()));
    c15->Update();


    TCanvas* c16 = new TCanvas("c16", "Theta Distribution", 800, 600);
    theta_dist->SetStats(0);
    theta_dist->GetXaxis()->SetTitle("#theta (radians)");
    theta_dist->GetYaxis()->SetTitle("Events");
    theta_dist->SetTitle("Theta Distribution");
    theta_dist->GetXaxis()->CenterTitle();
    theta_dist->GetYaxis()->CenterTitle();
    theta_dist->SetMarkerStyle(20);
    theta_dist->SetMarkerSize(0.5);
    theta_dist->SetMarkerColor(kMagenta);
    theta_dist->Scale(150.0/theta_dist->Integral()); // Normalize to unit area
    //theta_dist->GetYaxis()->SetRangeUser(0, theta_dist->GetMaximum()*4.0);
    function->SetLineColor(kRed);
    function->SetLineWidth(2);
    c16->SetGrid();
    theta_dist->Draw("");
    function->Draw("same");
    Rtt->Draw("P same");
    c16->Update();

    TCanvas* c17 = new TCanvas("c17", "Invariant Mass Distribution", 800, 600);
    Invariant_dist->SetStats(0);
    Invariant_dist->GetXaxis()->SetTitle("Invariant Mass (GeV)");
    Invariant_dist->GetYaxis()->SetTitle("Events");
    Invariant_dist->SetTitle("Invariant Mass Distribution");
    Invariant_dist->GetXaxis()->CenterTitle();
    Invariant_dist->GetYaxis()->CenterTitle();
    Invariant_dist->SetMarkerStyle(20);
    Invariant_dist->SetMarkerSize(0.5);
    Invariant_dist->SetMarkerColor(kMagenta);
    c17->SetGrid();
    Invariant_dist->Draw("");
    c17->Update();


    TCanvas* c18 = new TCanvas("c18", "Rtt Distribution", 800, 600);
    Rtt->SetStats(0);
    Rtt->GetXaxis()->SetTitle("cos(#theta)");
    Rtt->GetYaxis()->SetTitle("Events");
    Rtt->SetTitle("Rtt Distribution");
    Rtt->GetXaxis()->CenterTitle();
    Rtt->GetYaxis()->CenterTitle();
    Rtt->SetMarkerStyle(20);
    Rtt->SetMarkerSize(0.5);
    Rtt->SetMarkerColor(kMagenta);
    c18->SetGrid();
    Rtt->Draw("AP");
    c18->Update();

    TCanvas* c19 = new TCanvas("c19", "Tau Z Momenta", 800, 600);
    tauZMomenta->SetStats(0);
    tauZMomenta->GetXaxis()->SetTitle("Momentum (GeV)");
    tauZMomenta->GetYaxis()->SetTitle("Events");
    tauZMomenta->SetTitle("Tau Z Momenta Distribution");
    tauZMomenta->GetXaxis()->CenterTitle();
    tauZMomenta->GetYaxis()->CenterTitle();
    tauZMomenta->SetMarkerStyle(20);
    tauZMomenta->SetMarkerSize(0.5);
    tauZMomenta->SetMarkerColor(kMagenta);
    c19->SetGrid();
    tauZMomenta->Draw("");
    c19->Update();

    //ps.Close();


    // after you draw c1..c9
    c1->Print("output_histos.pdf[");  // open
    c1->Print("output_histos.pdf");   // page 1
    c2->Print("output_histos.pdf");   // page 2
    c3->Print("output_histos.pdf");
    c4->Print("output_histos.pdf");
    c5->Print("output_histos.pdf");
    c6->Print("output_histos.pdf");
    c7->Print("output_histos.pdf");
    c8->Print("output_histos.pdf");
    c9->Print("output_histos.pdf");
    c10->Print("output_histos.pdf");  // last page
    c11->Print("output_histos.pdf");
    c12->Print("output_histos.pdf");
    c13->Print("output_histos.pdf");
    c14->Print("output_histos.pdf");
    c15->Print("output_histos.pdf");
    c16->Print("output_histos.pdf");
    c17->Print("output_histos.pdf");
    c18->Print("output_histos.pdf");
    c19->Print("output_histos.pdf");
    c19->Print("output_histos.pdf]");  // close


    c7->SaveAs("soft_photons.png");

    currentDir->cd();
}
