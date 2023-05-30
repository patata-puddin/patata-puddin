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
void ent_det1_pro_ratio()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb_det_108_new.root", "read");


  TTree *TVol2 = (TTree *) P1dfile -> Get("Detector_2");
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


 TH2D *hist = new TH2D("All", "All particle", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_p = new TH2D("proton", "proton_detector2", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_g = new TH2D("gamma", "gamma_detector2", 100, -225, 225, 100, -225, 225);
  TH2D *hist_e = new TH2D("electron", "electron_detector2", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_pge = new TH2D("p_g_e", "proton+gamma+electron_detector2", 100, -225, 225 , 100, -225, 225);
  TH2D *hist_ge = new TH2D("g_e", "gamma+electron_detector2", 100, -225, 225, 100, -225, 225);
  
  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posz-2062) < 0.000000001) && ((strcmp(vpvol_p, "Pb_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0))){           
          if( (posx< -170 && posx > -220) && (posy <100 && posy >-100)){
            hist->Fill(posx, posy);
if (sh_Pdg == 2212) {
              hist_p -> Fill(posx, posy);    
            }
            if (sh_Pdg == 22) {
              hist_g -> Fill(posx, posy);    
            }
            if (sh_Pdg == 11) {
              hist_e -> Fill(posx, posy);    
            }
            if (sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_ge ->Fill(posx, posy); 
            }
            if (sh_Pdg ==2212 || sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_pge ->Fill(posx, posy); 
            }
          }
      }
   }

   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1350, 650);
  c3->Divide(4,2);
  
  c3->cd(1)->SetLogz();
  //c3->cd(2)->SetLogz();
  // c3->cd(3)->SetLogz();
  c3->cd(4)->SetLogz();
    c3->cd(1);
    //hist->Draw("colz");

    c3->cd(2);
    hist_p->GetXaxis()->SetTitle("x(mm)");
  hist_p->GetYaxis()->SetTitle("y(mm)");
    hist_p->Draw("colz");    
  
    c3->cd(6);
    hist_g->GetXaxis()->SetTitle("x(mm)");
  hist_g->GetYaxis()->SetTitle("y(mm)");
    hist_g->Draw("colz"); 

    c3->cd(7);
    hist_e->GetXaxis()->SetTitle("x(mm)");
  hist_e->GetYaxis()->SetTitle("y(mm)");
    hist_e->Draw("colz"); 
    
    //c3->cd();
    //hist_pge->Draw("colz");

    c3->cd(3);
    TH2D *h2_ratio = (TH2D*)hist_p->Clone("h2_ratio");
    h2_ratio->Divide(hist_pge);
    h2_ratio->SetTitle("proton/(p+g+e)_detector2");
    h2_ratio->SetStats(0);  
      h2_ratio->GetXaxis()->SetTitle("x(mm)");
    h2_ratio->GetYaxis()->SetTitle("y(mm)");
    h2_ratio->Draw("colz");

   c3->cd(4);
    TH2D *h2_ratio1 = (TH2D*)hist_p->Clone("h2_ratio1");
    h2_ratio1->Divide(hist_ge);
    h2_ratio1->SetTitle("p/(g+e)_detector2");
    h2_ratio1->SetStats(0);  
    h2_ratio1->GetXaxis()->SetTitle("x(mm)");
    h2_ratio1->GetYaxis()->SetTitle("y(mm)");
    h2_ratio1->Draw("colz");
}