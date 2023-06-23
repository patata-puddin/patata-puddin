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
void ent_det2_ratio_draw_06()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("out_06_p1_Z.root", "read");


  TTree *TVol2 = (TTree *) P1dfile -> Get("Detector_2");
  Double_t sh_KE;
  Double_t sh_Pdg;
  Double_t posx, posy, posz;
  Char_t vpvol_p[100];

  int j;
  int counte;
  Double_t max=1;
  Double_t min=10000000;
  int p_count = 0 ;  
  int g_count = 0 ;  
  int count = 0 ;
  int e_count = 0 ;

  TVol2 -> SetBranchAddress("KE",&sh_KE);
  TVol2 -> SetBranchAddress("pdg",&sh_Pdg);
  TVol2 -> SetBranchAddress("px",&posx);
  TVol2 -> SetBranchAddress("py",&posy);
  TVol2 -> SetBranchAddress("pz",&posz);
  TVol2 -> SetBranchAddress("vpvol",&vpvol_p); 
//position1
  TH2D *hist_p = new TH2D("proton", "proton", 20, 1755, 2045 , 5, -125, 15);
  TH2D *hist_g = new TH2D("gamma", "gamma",   20, 1755, 2045 , 5, -125, 15);
  TH2D *hist_e = new TH2D("electron", "electron",   20, 1755, 2045 , 5, -125, 15);
  TH2D *hist_pge = new TH2D("p_g_e", "proton+gamma+electron",   20, 1755, 2045 , 5, -125, 15);
  TH2D *hist_ge = new TH2D("g_e", "gamma+electron",   20, 1755, 2045 , 5, -125, 15);
// //position3 
  // TH2D *hist_p = new TH2D("proton", "proton", 5, 1790, 1930 , 20, -123, 167);
  // TH2D *hist_g = new TH2D("gamma", "gamma", 5, 1790, 1930 , 20, -123, 167);
  // TH2D *hist_e = new TH2D("electron", "electron",  5, 1790, 1930 , 20, -123, 167);
  // TH2D *hist_pge = new TH2D("p_g_e", "proton+gamma+electron",  5, 1790, 1930 , 20, -123, 167);
  // TH2D *hist_ge = new TH2D("g_e", "gamma+electron",  5, 1790, 1930 , 20, -123, 167);

// //position2
  // TH2D *hist_p = new TH2D("proton", "proton", 20, 1830, 2120 , 5, -55, 85);
  // TH2D *hist_g = new TH2D("gamma", "gamma", 20, 1830, 2120 , 5, -55, 85);
  // TH2D *hist_e = new TH2D("electron", "electron",  20, 1830, 2120 , 5, -55, 85);
  // TH2D *hist_pge = new TH2D("p_g_e", "proton+gamma+electron",  20, 1830, 2120 , 5, -55, 85);
  // TH2D *hist_ge = new TH2D("g_e", "gamma+electron",  20, 1830, 2120 , 5, -55, 85);

  //((strcmp(vpvol_p, "World") == 0)||(strcmp(vpvol_p, "Pb_Shield") == 0)||(strcmp(vpvol_p, "Dump") == 0))
//      if((abs(posx+225) < 0.0000001) && ((strcmp(vpvol_p, "Detector2") != 0))){           

  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posx+231) < 0.0000001) && ((strcmp(vpvol_p, "Detector2") != 0))){           
           //if((posz >1627  && posz<2067) && (posy> -220 && posy < 220)){
          
            if (sh_Pdg == 2212) {
              hist_p -> Fill(posz, posy);    
              p_count +=1;


            }
            if (sh_Pdg == 22) {
              hist_g -> Fill(posz, posy);    
              g_count +=1;

            }
            if (sh_Pdg == 11) {
              hist_e -> Fill(posz, posy);    
               e_count +=1;

            }
            if (sh_Pdg ==2212 || sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_pge ->Fill(posz, posy); 
            }
            if (sh_Pdg ==22 || sh_Pdg ==11 ){
              hist_ge ->Fill(posz, posy); 
            }
                      if (posz > max) {
      max = posy;
    }
              if (posz < min) {
      min = posy;
    }

          
    //       if (posz > max) {
    //   max = posz;
    // }
    //           if (posz < min) {
    //   min = posz;
    // }
      }
   }

   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1300, 900);
  c3->Divide(3,2);
  
    std::cout <<"max: " <<max<< "\n";
    std::cout <<"min: " <<min<< "\n";
    std::cout <<"proton: " <<p_count<< "\n";
    std::cout <<"gamma: " <<g_count<< "\n";
    std::cout <<"electron: " <<e_count<< "\n";
    std::cout <<"total: " <<count<< "\n";

  //c3->cd(1)->SetLogz();
  //c3->cd(2)->SetLogz();
  // c3->cd(3)->SetLogz();
  //c3->cd(4)->SetLogz();
    //c3->cd(1);
    //hist->Draw("colz");

    c3->cd(1);
    hist_p->GetXaxis()->SetTitle("z(mm)");
    hist_p->GetYaxis()->SetTitle("y(mm)");
    //hist_p->SetStats(0);  
    // hist_p->SetMaximum(83);
    hist_p->SetMarkerSize(2);
    hist_p->Draw("text89 same0 colz");    

    // std::cout <<"max: " <<max<< "\n";
    // std::cout <<"min: " <<min<< "\n";

    c3->cd(2);
    hist_g->GetXaxis()->SetTitle("z(mm)");
    hist_g->GetYaxis()->SetTitle("y(mm)");
    //hist_g->SetStats(0);
    // hist_g->SetMaximum(206);
    hist_g->SetMarkerSize(2);
    hist_g->Draw("text89 same colz"); 

    c3->cd(3);
    hist_e->GetXaxis()->SetTitle("z(mm)");
    hist_e->GetYaxis()->SetTitle("y(mm)");
    //hist_e->SetStats(0);
    hist_e->SetMarkerSize(2);
    hist_e->Draw("text89 same0 colz"); 

// gStyle->SetPaintTextFormat("1.2f");
//-----------------do this to make format long
    c3->cd(4);
    TH2D *h2_ratio = (TH2D*)hist_p->Clone("h2_ratio");
    h2_ratio->Divide(hist_pge);
    h2_ratio->Scale(100.0);
    h2_ratio->SetTitle("proton/(p+g+e)");
    h2_ratio->SetStats(0);  
    h2_ratio->GetXaxis()->SetTitle("z(mm)");
    h2_ratio->GetYaxis()->SetTitle("y(mm)");
    h2_ratio->Draw(" text89 same0 colz");

  //  c3->cd(5);
  //   TH2D *h2_ratio1 = (TH2D*)hist_p->Clone("h2_ratio1");
  //   h2_ratio1->Divide(hist_ge);
  //   h2_ratio1->SetTitle("p/(g+e)");
  //   h2_ratio1->SetStats(0);  
  //   h2_ratio1->GetXaxis()->SetTitle("z(mm)");
  //   h2_ratio1->GetYaxis()->SetTitle("y(mm)");
  //   h2_ratio1->Draw("text same0 colz");

    c3->cd(5);
    TH2D *h2_ratio2 = (TH2D*)hist_g->Clone("h2_ratio2");
    h2_ratio2->Divide(hist_pge);
    h2_ratio2->SetTitle("gamma/(p+g+e)");
    h2_ratio2->Scale(100.0);
    h2_ratio2->SetStats(0);  
    h2_ratio2->GetXaxis()->SetTitle("z(mm)");
    h2_ratio2->GetYaxis()->SetTitle("y(mm)");
    h2_ratio2->Draw(" text89 same0 colz");

    c3->cd(6);
    TH2D *h2_ratio3 = (TH2D*)hist_e->Clone("h2_ratio3");
    h2_ratio3->Divide(hist_pge);
    h2_ratio3->SetTitle("electron/(p+g+e)");
    h2_ratio3->SetStats(0);  
    h2_ratio3->Scale(100.0);
    h2_ratio3->GetXaxis()->SetTitle("z(mm)");
    h2_ratio3->GetYaxis()->SetTitle("y(mm)");
    h2_ratio3->Draw(" text89 same0 colz");
}