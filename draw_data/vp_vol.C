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
void vp_vol()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb_108_komac_shieldO.root", "read");
TCanvas* c1 = new TCanvas("c1", "Histogram of Entering Particle in shield", 20, 20, 2000, 2000);
  c1->SetGrid();


  int markersize= 1;
  int i;
  double labelsize=0.09;  

  //For total particle entering shield

  gPad->SetGrid();
  gPad->SetLogy();

  TTree *TVol1 = (TTree *) P1dfile -> Get("Detector_2");
  TVol1 -> Draw("name>>h1","","");

  TH1F *h1 = (TH1F*)gDirectory->Get("h1");
  if(h1 != nullptr){
  h1->SetMarkerSize(markersize);
  // h1->SetLabelSize(labelsize);
  h1->LabelsOption(">");
  h1->SetStats(0);
  h1->SetTitle("vp");
  h1->SetFillColor(kRed);
  h1->SetFillStyle(3001);
  h1->Draw("Text0 same");

  int totentry1 = h1->GetNbinsX();

  cout << "For total particle entering shield" << endl;
  cout << "Bin       " << "# of particle" << endl;
  for(i=1;i<=totentry1;i++){
    int num_part1 = h1->GetBinContent(i);
    cout << i << "              " << num_part1 << endl;
  }
  }

  //Proton entering shield

//   gPad->SetGrid();
//   gPad->SetLogy();

//   TTree *TVol2 = (TTree *) P1dfile -> Get("ent_shield");
//   Double_t sh_KE;
//   Double_t sh_Pdg;
//   int j;

 
//   TVol2 -> SetBranchAddress("KE",&sh_KE);
//   TVol2 -> SetBranchAddress("pdg",&sh_Pdg);


//   TH1D *hist_sh_2212_KE = new TH1D("Proton", "Proton Energy entering shield", 100, 0, 30);
//   TH1D *hist_sh_22_KE = new TH1D("Gamma", "Gamma Energy entering shield", 40, 0, 10);
//   TH1D *hist_sh_2112_KE = new TH1D("Neutron", "Neutron Energy entering shield", 40, 0, 23);
//   //TH1D *hist_DAQ_2212_KE = new TH1D("With Al Shielding", "Proton Energy entering DAQ", 100, 0, 60);
//   // TH1D *hist_DAQ_22_KE = new TH1D("With Al Shielding-", "Gamma Energy entering DAQ", 40, 0, 15);
//   // TH1D *hist_DAQ_2112_KE = new TH1D("With Al Shielding ", "Neutron Energy entering DAQ", 40, 0, 52);


//   auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
//    for (j=0;j<Entry_KE; j++){
//       TVol2 -> GetEntry(j);

//       if(sh_Pdg == 2212) {
//           hist_sh_2212_KE -> Fill(sh_KE);  
//       }
//       if(sh_Pdg == 22) {
//           hist_sh_22_KE -> Fill(sh_KE);  
//       }
//       if(sh_Pdg == 2112) {
//           hist_sh_2112_KE -> Fill(sh_KE);  
//       }
//    }

//    // //////Draw-----///////////------------///////
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

//    c2->Update();
//    gPad->Update();
    
//   TPaveStats *s1 = (TPaveStats*)hist_sh_2212_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//    s1->SetX1NDC(0.51); s1->SetX2NDC(0.78);
//    s1->SetY1NDC(0.73); s1->SetY2NDC(0.93);
//    s1->SetTextColor(kGreen+3);
//    //s11->SetTextColor(kBlue);
//    gPad->Modified();
//    gPad->Update();



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

//    c2->Update();
//     gPad->Update();
    
//   TPaveStats *s2 = (TPaveStats*)hist_sh_22_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//    s2->SetX1NDC(0.51); s2->SetX2NDC(0.78);
//   s2->SetY1NDC(0.73); s2->SetY2NDC(0.93);
//    s2->SetTextColor(kGreen+3);
// //s11->SetTextColor(kBlue);
//    gPad->Modified();
//    gPad->Update();


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

//    c2->Update();
//     gPad->Update();
    
//   TPaveStats *s3 = (TPaveStats*)hist_sh_2112_KE->GetListOfFunctions()->FindObject("stats"); //----------try move stats
//    s3->SetX1NDC(0.51); s3->SetX2NDC(0.78);
//   s3->SetY1NDC(0.73); s3->SetY2NDC(0.93);
//    s3->SetTextColor(kGreen+3);
// //s11->SetTextColor(kBlue);
//    gPad->Modified();
//    gPad->Update();

}