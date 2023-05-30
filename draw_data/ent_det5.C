#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"

//entering shield- total particle 
//entering shield- E dist of p,r,n
using namespace std;
void ent_det5()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb_det.root", "read");
// TCanvas* c1 = new TCanvas("c1", "Histogram of Entering Particle in shield", 20, 20, 2000, 2000);
//   c1->SetGrid();


//   int markersize= 1;
//   int i;
//   double labelsize=0.09;  

//   //For total particle entering shield

//   gPad->SetGrid();
//   gPad->SetLogy();

//   TTree *TVol1 = (TTree *) P1dfile -> Get("Detector_2");
//   TVol1 -> Draw("name>>h1","","");

//   TH1F *h1 = (TH1F*)gDirectory->Get("h1");

//   if(h1 != nullptr){
//   h1->SetMarkerSize(markersize);
//   // h1->SetLabelSize(labelsize);
//   h1->LabelsOption(">");
//   h1->SetStats(0);
//   h1->SetTitle("Total particle entering shield");
//   h1->SetFillColor(kRed);
//   h1->SetFillStyle(3001);
//   h1->Draw("Text0 same");

//   int totentry1 = h1->GetNbinsX();

//   cout << "For total particle entering shield" << endl;
//   cout << "Bin       " << "# of particle" << endl;
//   for(i=1;i<=totentry1;i++){
//     int num_part1 = h1->GetBinContent(i);
//     cout << i << "              " << num_part1 << endl;
//   }
//   }


//   gPad->SetGrid();
//   gPad->SetLogy();

  TTree *TVol2 = (TTree *) P1dfile -> Get("Detector_5");
  Double_t sh_KE;
  Double_t sh_Pdg;
  Double_t posx, posy, posz;
  Char_t vpvol_p[100];

  int j;
  int exception =0 ;
 
  TVol2 -> SetBranchAddress("KE",&sh_KE);
  TVol2 -> SetBranchAddress("pdg",&sh_Pdg);
  TVol2 -> SetBranchAddress("px",&posx);
  TVol2 -> SetBranchAddress("py",&posy);
  TVol2 -> SetBranchAddress("pz",&posz);
  TVol2 -> SetBranchAddress("vpvol",&vpvol_p); 


  // TH3D *hist_sh_2212_KE = new TH3D("Proton_KE", "Proton Energy entering detector5", 100, -225, 225 , 100, -225, 225, 10, 0, 30);
  // TH3D *hist_sh_22_KE = new TH3D("Gamma_KE", "Gamma Energy entering detector5", 100, -225, 225 , 100, -225, 225, 10, 0, 30);
  // TH3D *hist_sh_2112_KE = new TH3D("Neutron_KE", "Neutron Energy entering detector5", 100, -225, 225 , 100, -225, 225, 10, 0, 30);

  TH2D *hist_2212 = new TH2D("Proton", "Proton entering detector5", 100, 1622, 2072 , 100, -225, 225);
  TH2D *hist_22 = new TH2D("Gamma", "Gamma entering detector5", 100, 1622, 2072 , 100, -225, 225);
  TH2D *hist_2112 = new TH2D("Neutron", "Neutron entering detector5", 100, 1622, 2072 , 100, -225, 225);
  //TH1D *hist_DAQ_2212_KE = new TH1D("With Al Shielding", "Proton Energy entering DAQ", 100, 0, 60);
  // TH1D *hist_DAQ_22_KE = new TH1D("With Al Shielding-", "Gamma Energy entering DAQ", 40, 0, 15);
  // TH1D *hist_DAQ_2112_KE = new TH1D("With Al Shielding ", "Neutron Energy entering DAQ", 40, 0, 52);


  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if( (abs(posy+215) < 0.000000000001)  && ((strcmp(vpvol_p, "Pb_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0))){
            if(sh_Pdg == 2212) {
          // hist_sh_2212_KE -> Fill(posx, posy, sh_KE);  
          hist_2212 -> Fill(posz, posx);  
            }
            if(sh_Pdg == 22) {
          // hist_sh_22_KE -> Fill(posx, posy, sh_KE);  
          hist_22 -> Fill(posz, posx);  

            }
            if(sh_Pdg == 2112) {
          // hist_sh_2112_KE -> Fill(posx, posy, sh_KE);  
          hist_2112 -> Fill(posz, posx);  
            }
      }
   }

   // //////Draw-----///////////------------///////
//   TCanvas* c2 = new TCanvas("c2", "KE comparision", 20, 20, 450, 1000);
//   c2->Divide(1,3);
  
//   c2->cd(1)->SetLogy();
//   c2->cd(2)->SetLogy();
//   c2->cd(3)->SetLogy();

// //For Proton entering shield
// c2->cd(1);

//   hist_sh_2212_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_sh_2212_KE->GetYaxis()->SetTitle("Count");
//   hist_sh_2212_KE->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_2212_KE->SetLineColor(kGreen+3);
//   hist_sh_2212_KE->SetFillStyle(3004);
//   hist_sh_2212_KE->SetTitle("E dist of PROTON entering shield");
//   //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
//   hist_sh_2212_KE->Draw();


// //For Gamma entering shield
// c2->cd(2);

//   hist_sh_22_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_sh_22_KE->GetYaxis()->SetTitle("Count");
//   hist_sh_22_KE->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_22_KE->SetLineColor(kGreen+3);
//   hist_sh_22_KE->SetFillStyle(3004);
//   hist_sh_22_KE->SetTitle("E dist of GAMMA entering shield");
//   //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
//   hist_sh_22_KE->Draw();


// //For Neutron entering shield
// c2->cd(3);

//   hist_sh_2112_KE->GetXaxis()->SetTitle("Energy (MeV)");
//   hist_sh_2112_KE->GetYaxis()->SetTitle("Count");
//   hist_sh_2112_KE->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_2112_KE->SetLineColor(kGreen+3);
//   hist_sh_2112_KE->SetFillStyle(3004);
//   hist_sh_2112_KE->SetTitle("E dist of NEUTRON entering shield");
//   //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
//   hist_sh_2112_KE->Draw();



   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1000, 350);
  c3->Divide(3,1);
  
  // c3->cd(1)->SetLogz();
  // c3->cd(2)->SetLogz();
  // c3->cd(3)->SetLogz();

//For Proton entering shield
c3->cd(1);

  hist_2212->GetXaxis()->SetTitle("z(mm)");
  hist_2212->GetYaxis()->SetTitle("x(mm)");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_2212->Draw("colz");


//For Gamma entering shield
c3->cd(2);

  hist_22->GetXaxis()->SetTitle("z(mm)");
  hist_22->GetYaxis()->SetTitle("x(mm)");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22->Draw("colz");


//For Neutron entering shield
c3->cd(3);

  hist_2112->GetXaxis()->SetTitle("z(mm)");
  hist_2112->GetYaxis()->SetTitle("x(mm)");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_2112->Draw("colz");

}