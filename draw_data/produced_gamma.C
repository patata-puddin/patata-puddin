#include "TGraph.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TMath.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TH2.h"
#include <iostream>
#include "TGraph2D.h"
#include "TMultiGraph.h"
#include "TLegend.h"

using namespace std;
// exiting shield- angle of p,r,n (produced in shield, or passing)
// entering shield- angle of p,r,n

void produced_gamma()
{

TFile *P1dfile =new TFile("test_4.root", "read");

  //Proton made in shield, exiting shield


  TTree *TVol1 = (TTree *) P1dfile -> Get("made_shield_gamma");

  Double_t mx;
  Double_t my;
  Double_t mz;
  Double_t vposx;
  Double_t vposy;
  Double_t vposz;
  Double_t KE;

  // std::string sh_vol;

  int j;
  int gammacount=0;
  int exception=0;

  int under1826count=0;
  int under1828count=0;
  int back1826count=0;
  int front1826count=0;
  TVol1 -> SetBranchAddress("vpx",&vposx);
  TVol1 -> SetBranchAddress("vpy",&vposy);
  TVol1 -> SetBranchAddress("vpz",&vposz);
  TVol1 -> SetBranchAddress("vpmx",&mx);
  TVol1 -> SetBranchAddress("vpmy",&my);
  TVol1 -> SetBranchAddress("vpmz",&mz);
  TVol1 -> SetBranchAddress("KE",&KE);


  TH2D *hist_22_vposxz = new TH2D("vp_gamma_shield_xz", "vp of gamma(x,z)_made in Shield", 50, 17, 226, 50, 1817, 1877);
  TH2D *hist_22_vposxy = new TH2D("vp_gamma_shield_xy", "vp of gamma(x,y)_made in Shield", 50, 17, 226, 50, -80, 130);
  TH2D *hist_22_vpos_E = new TH2D("vp_gamma_shield_E", "vp - KE of gamma ", 50, 1817, 1877, 50, 0, 14);
    TH1D *hist_sh_22_phiangle = new TH1D("Gamma_phi", "Angle (phi) of Gamma produced shield", 60, -2, 362);
    TH1D *hist_sh_22_thetaangle = new TH1D("Gamma_theta", "Angle (theta) of Gamma exiting shield", 60, -2, 182);
    TH2D *theta_22_KE = new TH2D("Gamma_theta_KE", "Gamma KE of theta", 50, -5, 185, 60, 0, 15);

  auto Entry = TVol1->GetBranch("proc")->GetEntries() ;
 
   for (j=0;j<Entry; j++){

        TVol1 -> GetEntry(j);

        gammacount += 1;
            Double_t mx_sh = TMath::Abs(mx);
            Double_t my_sh = TMath::Abs(my);

            Double_t theta = TMath::ACos(mz) * 180 / TMath::Pi();
            Double_t phi = TMath::ATan(my_sh/mx_sh) * 180 / TMath::Pi();

        
        hist_sh_22_thetaangle->Fill(theta);
        theta_22_KE->Fill(theta, KE);

        hist_22_vposxz->Fill(vposx, vposz);
        hist_22_vposxy->Fill(vposx, vposy);
        hist_22_vpos_E->Fill(vposz, KE);

         //For phi-----------
            if ((mx > 0) && (my > 0))
            {     hist_sh_22_phiangle->Fill(phi);
            }
            else if ((mx < 0) && (my > 0))
            {
                Double_t phi2=180-phi;
                hist_sh_22_phiangle->Fill(phi2);         
            }
            else if ((mx < 0) && (my < 0))
            {   Double_t phi3=180+phi;
                hist_sh_22_phiangle->Fill(phi3);    
            }
            else if ((mx > 0) && (my < 0))
            {   Double_t phi4=360-phi;
                hist_sh_22_phiangle->Fill(phi4);      
            }
            else 
            {
                exception+=1;
            }
   }

  for (j=0;j<Entry; j++){
        TVol1 -> GetEntry(j);

        if(vposz < 1826){
          under1826count +=1;
        }
        else if(vposz < 1828){
          under1828count +=1;
        }
    
}

cout << "#of gamma: " << gammacount << endl;
cout << "#of gamma produced at z<1826: " << under1826count << endl;
cout << "#of gamma produced at  1826 < z<1828: " << under1828count << endl;



//    // //////Draw-----///////////------------///////
  TCanvas* c2 = new TCanvas("c2", "KE for real", 20, 20, 1000, 1000);
  c2->Divide(2,3);
  
 
c2->cd(1)->SetLogz();
c2->cd(2)->SetLogz();
c2->cd(3)->SetLogz();
c2->cd(3)->SetLogy();
c2->cd(4)->SetLogy();

c2->cd(1);
if(hist_22_vposxz != nullptr){
  hist_22_vposxz->GetXaxis()->SetTitle("x (mm)");
  hist_22_vposxz->GetYaxis()->SetTitle("z (mm)");
  hist_22_vposxz->SetTitle("Position (x, z) of gamma produced in shield");
  // hist_22_vposxz->SetMaximum(1000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vposxz->Draw("colz");
}

c2->cd(2);
if(hist_22_vposxy != nullptr){
  hist_22_vposxy->GetXaxis()->SetTitle("x (mm)");
  hist_22_vposxy->GetYaxis()->SetTitle("y (mm)");
  hist_22_vposxy->SetTitle("Position (x, y) of gamma produced in shield");
  // hist_22_vposxz->SetMaximum(1000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vposxy->Draw("colz");
}

c2->cd(3);
if(hist_22_vpos_E != nullptr){
  hist_22_vpos_E->GetXaxis()->SetTitle("z (mm)");
  hist_22_vpos_E->GetYaxis()->SetTitle("KE (MeV)");
  // hist_22_vposxz->SetMaximum(1000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vpos_E->Draw("colz");
}

    c2->cd(4);
    if (hist_sh_22_thetaangle != nullptr)
    {
        hist_sh_22_thetaangle->GetXaxis()->SetTitle("theta angle");
        hist_sh_22_thetaangle->GetYaxis()->SetTitle("Count");
        hist_sh_22_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_sh_22_thetaangle->SetLineColor(kGreen + 3);
        hist_sh_22_thetaangle->SetFillStyle(3004);
        // hist_sh_22_thetaangle_x->SetMaximum(400);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_sh_22_thetaangle->SetTitle("theta angle of Gamma produced in shield");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_sh_22_thetaangle->Draw();
    }
    c2->cd(5);
theta_22_KE->GetXaxis()->SetTitle("theta angle");
theta_22_KE->GetYaxis()->SetTitle("KE (MeV)");
theta_22_KE->GetXaxis()->SetLabelSize(0.05);
theta_22_KE->GetYaxis()->SetLabelSize(0.05);
// theta_22_KE->SetMaximum(70);
// theta_KE->GetXaxis()->SetTitleSize(0.05);
// theta_KE->GetYaxis()->SetTitleSize(0.05);
theta_22_KE->Draw("colz");
//   gPad->SetLogz();
  gPad->SetLogy();

    c2->cd(6);
hist_sh_22_phiangle->GetXaxis()->SetTitle("phi angle");
hist_sh_22_phiangle->GetYaxis()->SetTitle("count");
hist_sh_22_phiangle->GetXaxis()->SetLabelSize(0.05);
hist_sh_22_phiangle->GetYaxis()->SetLabelSize(0.05);
// theta_KE->GetXaxis()->SetTitleSize(0.05);
// theta_KE->GetYaxis()->SetTitleSize(0.05);
hist_sh_22_phiangle->Draw("colz");
//   gPad->SetLogz();
  gPad->SetLogy();
}

