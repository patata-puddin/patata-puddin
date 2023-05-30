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
void ent_det1_gam()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb_det.root", "read");


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


  TH2D *hist_56 = new TH2D("Gamma_56", "5-6MeV gamma_detector1", 100, -225, 225 , 100, -225, 225);
  TH2D *hist = new TH2D("Gamma", "gamma_detector1", 100, -225, 225 , 100, -225, 225);
  

  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posz-2062) < 0.000000000001) && ((strcmp(vpvol_p, "Pb_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0))){           
      if(sh_Pdg == 22) {
          //if((abs(posx) >120)|| (abs(posy) > 120)){
            hist->Fill(posx, posy);

            if (sh_KE >= 5 && sh_KE <= 6) {
              hist_56 -> Fill(posx, posy);    
          //}
            }
      }
   }
   }

   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1000, 350);
  c3->Divide(3,1);
  
  c3->SetLogz();
    c3->cd(1);
    hist->Draw("colz");

    c3->cd(2);
    hist_56->Draw("colz2");

    c3->cd(3);
    TH2D *h2_ratio = (TH2D*)hist_56->Clone("h2_ratio");
    h2_ratio->Divide(hist);
    h2_ratio->SetTitle("5-6MeV gamma ratio_detector1");
    h2_ratio->SetStats(0);
    h2_ratio->Draw("colz2");
}