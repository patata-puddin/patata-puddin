#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TLatex.h"
//entering shield- total particle 
//entering shield- E dist of p,r,n
using namespace std;
void ent_det1()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Al_det_air.root", "read");


// TCanvas* c2 = new TCanvas("c2", "KE comparision", 20, 20, 450, 1000);
//   int markersize= 1;
//   int i;
//   double labelsize=0.09;  

//   //For total particle entering shield

//   gPad->SetGrid();
//   gPad->SetLogy();

//   TTree *TVol1 = (TTree *) P1dfile -> Get("Detector_1");
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

  TTree *TVol2 = (TTree *) P1dfile -> Get("Detector_1");
  Double_t sh_KE;
  Double_t sh_Pdg;
  Double_t posx, posy, posz;
  Char_t vpvol_p[100];

  int j;
  int counte;

 
  TVol2 -> SetBranchAddress("KE",&sh_KE);
  TVol2 -> SetBranchAddress("pdg",&sh_Pdg);
  TVol2 -> SetBranchAddress("px",&posx);
  TVol2 -> SetBranchAddress("py",&posy);
  TVol2 -> SetBranchAddress("pz",&posz);
  TVol2 -> SetBranchAddress("vpvol",&vpvol_p); 


  TH2D *hist_sh_2212_KE = new TH2D("Proton_KE", "Proton Energy entering detector1", 100, -225, 225 , 10, 0, 30);
  TH2D *hist_sh_22_KE = new TH2D("Gamma_KE", "Gamma Energy entering detector1", 100, -225, 225 , 10, 0, 30);
  TH2D *hist_sh_2112_KE = new TH2D("Neutron_KE", "Neutron Energy entering detector1", 100, -225, 225, 10, 0, 30);

  TH2D *hist_2212 = new TH2D("Proton", "Proton entering detector1", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_22 = new TH2D("Gamma", "Gamma entering detector1", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_2112 = new TH2D("Neutron", "Neutron entering detector1", 100, -225, 225 , 100, -225, 225);
  //TH1D *hist_DAQ_2212_KE = new TH1D("With Al Shielding", "Proton Energy entering DAQ", 100, 0, 60);
  // TH1D *hist_DAQ_22_KE = new TH1D("With Al Shielding-", "Gamma Energy entering DAQ", 40, 0, 15);
  TH1D *hist_part = new TH1D("particle", "Particle entering detector1", 1000, 0, 2300);


  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posz-2062) < 0.000000000001) && ((strcmp(vpvol_p, "Al_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0))){
        
      if(sh_Pdg == 2212) {
          // hist_sh_2212_KE -> Fill(posx, posy, sh_KE);  
          //if((abs(posx) >120)|| (abs(posy) > 120)){
              hist_2212 -> Fill(posx, posy);  
              hist_sh_2212_KE -> Fill (posx, sh_KE);
              
          //}
      }
      if(sh_Pdg == 22) {
          // hist_sh_22_KE -> Fill(posx, posy, sh_KE);  
          hist_22 -> Fill(posx, posy);  

      }
      if(sh_Pdg == 2112) {
          // hist_sh_2112_KE -> Fill(posx, posy, sh_KE);  
          hist_2112 -> Fill(posx, posy);  
      }
      if(sh_Pdg == 11){
        if((abs(posx) >120)|| (abs(posy) > 120)){
        counte += 1;
        }
      }
      }
   }
    cout << " number of electron " << counte << endl;
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

// TCanvas* c1 = new TCanvas("c1", "Histogram of Entering Particle in shield", 20, 20, 2000, 2000);

// for (int i=1; i<=hist_part->GetNbinsX(); i++) {
//     if (hist_part->GetBinContent(i) <= 0) {
//         hist_part->SetBinContent(i, 1e-9);
//     }
// }
//   c1->SetGrid();  
//   c1->SetLogy();
//   hist_part->SetFillColor(kRed);
//   hist_part->SetFillStyle(3001);
// hist_part->Draw();
// hist_part->Draw();
// hist_part->SetMinimum(1);
// hist_part->SetMaximum(1.1*hist_part->GetMaximum()); // Increase the maximum y-axis range by 10%
// hist_part->Draw("TEXT0 SAME");
// gPad->SetLogy();
   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1000, 650);
  c3->Divide(3,2);
  
  c3->cd(1)->SetLogz();
  c3->cd(4)->SetLogz();
  // c3->cd(2)->SetLogz();
  // c3->cd(3)->SetLogz();

//For Proton entering shield
c3->cd(1);

  hist_2212->GetXaxis()->SetTitle("x(mm)");
  hist_2212->GetYaxis()->SetTitle("y(mm)");
  // hist_2212->SetMaximum(2500);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_2212->Draw("colz");
  double max = hist_2212->GetMaximum();
  cout << "maximum" << max <<endl;

auto entry = hist_2212->GetEntries();
 cout << entry <<endl;
//For Gamma entering shield
c3->cd(2);

  hist_22->GetXaxis()->SetTitle("x(mm)");
  hist_22->GetYaxis()->SetTitle("y(mm)");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22->Draw("colz");


//For Neutron entering shield
c3->cd(3);

  hist_2112->GetXaxis()->SetTitle("x(mm)");
  hist_2112->GetYaxis()->SetTitle("y(mm)");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_2112->Draw("colz");

//For Proton entering shield
c3->cd(4);

  hist_sh_2212_KE->GetXaxis()->SetTitle("x(mm)");
  hist_sh_2212_KE->GetYaxis()->SetTitle("KE (MeV)");
  // hist_sh_2212_KE->SetMaximum(2500);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_2212_KE->Draw("colz");

}