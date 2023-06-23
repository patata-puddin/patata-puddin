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
void test_energy()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb_108_new_dump.root", "read");


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
  int e_count = 0 ;
    std::vector<double> x_p, x_g, x_e;
    std::vector<double> y_p, y_g, y_e;
    std::vector<double> z_p, z_g, z_e;

  TVol2 -> SetBranchAddress("KE",&sh_KE);
  TVol2 -> SetBranchAddress("pdg",&sh_Pdg);
  TVol2 -> SetBranchAddress("px",&posx);
  TVol2 -> SetBranchAddress("py",&posy);
  TVol2 -> SetBranchAddress("pz",&posz);
  TVol2 -> SetBranchAddress("vpvol",&vpvol_p); 


  TH2D *hist_p = new TH2D("proton", "proton entry", 6, 1847, 2467 , 8, -440, 440);
  TH2D *hist_p_energy = new TH2D("proton_energy", "proton total energy", 6, 1847, 2467 , 8, -440, 440);
  TH2D *hist_e = new TH2D("electron", "electron entry", 6, 1847, 2467 , 8, -440, 440);
  TH2D *hist_e_energy = new TH2D("electron_energy", "electron total energy", 6, 1847, 2467 , 8, -440, 440);
  TH2D *hist_g = new TH2D("gamma", "gamma entry", 6, 1847, 2467 , 8, -440, 440);
  TH2D *hist_g_energy = new TH2D("gamma_energy", "gamma total energy", 6, 1847, 2467 , 8, -440, 440);

  

  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posx-215) < 0.0000001) && ((strcmp(vpvol_p, "Pb_Shield") == 0) ||(strcmp(vpvol_p, "World") == 0))){           
           //if((posz >1627  && posz<2067) && (posy> -220 && posy < 220)){
            if (sh_Pdg == 2212) {
              hist_p -> Fill(posz, posy);    
              p_count +=1;
              hist_p_energy->Fill(posz, posy, sh_KE);   
             
            }
            if (sh_Pdg == 22) {
              hist_g -> Fill(posz, posy);    
              g_count +=1;
              hist_g_energy->Fill(posz, posy, sh_KE);   
             }
            
            if (sh_Pdg == 11) {
              hist_e -> Fill(posz, posy);    
              e_count +=1;
              hist_e_energy->Fill(posz, posy, sh_KE);  
            }
      }
      }
   

   // //////Draw-----///////////------------///////
  TCanvas* c3= new TCanvas("c3", "KE comparision", 20, 20, 1300, 900);
  c3->Divide(3,3);

cout << "electron: " << e_count << endl;
c3->cd(1);
    hist_p->GetXaxis()->SetTitle("z(mm)");
  hist_p->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_p->SetMarkerSize(2);
    hist_p->Draw("text same0 colz");   

c3->cd(2);
    hist_p_energy->GetXaxis()->SetTitle("z(mm)");
  hist_p_energy->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_p_energy->SetMarkerSize(2);
    hist_p_energy->Draw("text same0 colz");   

    c3->cd(3);
    TH2D *h2_ratio = (TH2D*)hist_p_energy->Clone("h2_ratio");
    h2_ratio->Divide(hist_p);
    h2_ratio->SetTitle("proton mean energy");
    h2_ratio->SetStats(0);  
      h2_ratio->GetXaxis()->SetTitle("z(mm)");
    h2_ratio->GetYaxis()->SetTitle("y(mm)");
    h2_ratio->Draw(" text same0 colz");

c3->cd(4);
    hist_g->GetXaxis()->SetTitle("z(mm)");
  hist_g->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_g->SetMarkerSize(2);
    hist_g->Draw("text same0 colz");   

c3->cd(5);
    hist_g_energy->GetXaxis()->SetTitle("z(mm)");
  hist_g_energy->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_g_energy->SetMarkerSize(2);
    hist_g_energy->Draw("text same0 colz");   

    c3->cd(6);
    TH2D *h1_ratio = (TH2D*)hist_g_energy->Clone("h1_ratio");
    h1_ratio->Divide(hist_g);
    h1_ratio->SetTitle("gamma mean energy");
    h1_ratio->SetStats(0);  
      h1_ratio->GetXaxis()->SetTitle("z(mm)");
    h1_ratio->GetYaxis()->SetTitle("y(mm)");
    h1_ratio->Draw(" text same0 colz");


c3->cd(7);
    hist_e->GetXaxis()->SetTitle("z(mm)");
  hist_e->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_e->SetMarkerSize(2);
    hist_e->Draw("text same0 colz");   

c3->cd(8);
    hist_e_energy->GetXaxis()->SetTitle("z(mm)");
  hist_e_energy->GetYaxis()->SetTitle("y(mm)");
      //hist_p->SetStats(0);  
  // hist_p->SetMaximum(83);
  // auto mad = hist_p->GetMaximum();
  //   cout << mad << endl;
    hist_e_energy->SetMarkerSize(2);
    hist_e_energy->Draw("text same0 colz");   

    c3->cd(9);
    TH2D *h3_ratio = (TH2D*)hist_e_energy->Clone("h3_ratio");
    h3_ratio->Divide(hist_e);
    h3_ratio->SetTitle("electron mean energy");
    h3_ratio->SetStats(0);  
      h3_ratio->GetXaxis()->SetTitle("z(mm)");
    h3_ratio->GetYaxis()->SetTitle("y(mm)");
    h3_ratio->Draw(" text same0 colz");
}