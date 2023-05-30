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
void ent_det2_energy()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("komac.root", "read");


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


  TH1D *KE_p = new TH1D("proton_KE", "proton_KE dist", 30,0,30);
  TH1D *KE_g = new TH1D("gamma_KE", "gamma_KE dist", 30,0,30);
  TH1D *KE_e = new TH1D("electron_KE", "electron_KE dist", 30,0,30);

  TH1D *KE_p_over = new TH1D("p_KE_over", "proton_KE dist_over 1847", 30,0,30);
  TH1D *KE_g_over = new TH1D("g_KE_over", "gamma_KE dist_over 1847", 30,0,30);
  TH1D *KE_e_over = new TH1D("e_KE_over", "electron_KE dist_over 1847", 30,0,30);
  // TH1D *hist_pge = new TH1D("p_g_e", "proton+gamma+electron", 6, 1847, 2467 , 8, -440, 440);
  // TH1D *hist_ge = new TH1D("g_e", "gamma+electron_dump", 6, 1847, 2467 , 8, -440, 440);

  // TH3D *hist_p = new TH3D("proton", "proton", 6, 1847, 2467 , 8, -440, 440, 10,0,30);
  // TH3D *hist_g = new TH3D("gamma", "gamma",  6, 2000, 2467 , 8, 0, 440, 10,0,30);
  // TH3D *hist_e = new TH3D("electron", "electron",  6, 2000, 2467 , 8, 0, 440, 10,0,30);
  // TH3D *hist_pge = new TH3D("p_g_e", "proton+gamma+electron",  6, 2000, 2467 , 8, 0, 440, 10,0,30);
  // TH3D *hist_ge = new TH3D("g_e", "gamma+electron",  6, 2000, 2467 , 8, 0, 440, 10,0,30);
  TH2D *hist_p = new TH2D("proton", "proton entry_combi2", 6, 1750, 2050 , 9,-174, 126);
  TH2D *hist_p_energy = new TH2D("proton_energy", "proton total energy_combi2", 6, 1750, 2050 , 9,-174, 126);
  TH2D *hist_e = new TH2D("electron", "electron entry_combi2",6, 1750, 2050 , 9,-174, 126);
  TH2D *hist_e_energy = new TH2D("electron_energy", "electron total energy_combi2", 6, 1750, 2050 , 9,-174, 126);
  TH2D *hist_g = new TH2D("gamma", "gamma entry_combi2", 6, 1750, 2050 , 9,-174, 126);
  TH2D *hist_g_energy = new TH2D("gamma_energy", "gamma total energy_combi2", 6, 1750, 2050 , 9,-174, 126);

  

  auto Entry_KE = TVol2->GetBranch("pdg")->GetEntries() ;
 
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
      if((abs(posx+231) < 0.0000001) && (strcmp(vpvol_p, "Detector2") != 0)){           
           //if((posz >1627  && posz<2067) && (posy> -220 && posy < 220)){
            if (sh_Pdg == 2212) {
              // hist_p -> Fill(posz, posy, sh_KE);    
             x_p.push_back(posz);
             y_p.push_back(posy);
             z_p.push_back(sh_KE);
             KE_p->Fill(sh_KE);
             //if(posz > 1847){
              KE_p_over->Fill(sh_KE);
                           p_count +=1;
              hist_p -> Fill(posz, posy);    
              hist_p_energy->Fill(posz, posy, sh_KE);   

             //}
            }
            if (sh_Pdg == 22) {
              // hist_g -> Fill(posz, posy, sh_KE);    
             x_g.push_back(posz);
             y_g.push_back(posy);
             z_g.push_back(sh_KE);
             KE_g->Fill(sh_KE);
             //if(posz > 1847){
              KE_g_over->Fill(sh_KE);
                           g_count +=1;
              hist_g -> Fill(posz, posy);    
              hist_g_energy->Fill(posz, posy, sh_KE);   

             //}
            }
            if (sh_Pdg == 11) {
              // hist_e -> Fill(posz, posy, sh_KE);    
             x_e.push_back(posz);
             y_e.push_back(posy);
             z_e.push_back(sh_KE);
             KE_e->Fill(sh_KE);
             //if(posz > 1847){
              KE_e_over->Fill(sh_KE);
                           e_count +=1;
              hist_e -> Fill(posz, posy);    
              hist_e_energy->Fill(posz, posy, sh_KE);  

             //}
            }
            if (sh_Pdg ==2212 || sh_Pdg ==22 || sh_Pdg ==11 ){
              // hist_pge ->Fill(posz, posy, sh_KE); 
            }
            if (sh_Pdg ==22 || sh_Pdg ==11 ){
              // hist_ge ->Fill(posz, posy, sh_KE); 
            }
          //}
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
  c3->cd(4)->SetLogy();
  c3->cd(5)->SetLogy();

    std::cout <<"proton over 1847: " <<p_count<< "\n";
    std::cout <<"gamma over 1847: " <<g_count<< "\n";
    std::cout <<"electron over 1847: " <<e_count<< "\n";
// c3->cd(1);
//     auto g = new TGraph2D("1","",p_count, &x_p[0], &y_p[0], &z_p[0]);
//     g->SetTitle("KE dist of proton;z;y;KE (MeV)");
//     // g->SetMaximum(14);
//     // g->SetStats(kTRUE);
//     cout << g->GetN() << endl;
//     g->Draw("LEGO0");

// Proton, gamma, electron energy dist of all
    c3->cd(4);
  KE_p->GetXaxis()->SetTitle("KE (MeV)");
  KE_p->GetYaxis()->SetTitle("Count");
  KE_p->SetLineColor(kRed);
  KE_p->SetLineWidth(3);
  KE_p->SetMinimum(1);
  KE_p->Draw();  

   c3->Update();
   gPad->Update();
    TPaveStats *s1 = (TPaveStats*)KE_p->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s1->SetX1NDC(0.21); s1->SetX2NDC(0.41);
   s1->SetY1NDC(0.78); s1->SetY2NDC(0.93);
   s1->SetTextColor(kRed);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


      c3->cd(4);
  KE_g->GetXaxis()->SetTitle("KE (MeV)");
  KE_g->GetYaxis()->SetTitle("Count");
  KE_g->SetLineColor(kGreen+3);
  KE_g->SetLineWidth(3);
  KE_g->Draw("sames");  

     c3->Update();
   gPad->Update();
    TPaveStats *s2 = (TPaveStats*)KE_g->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s2->SetX1NDC(0.41); s2->SetX2NDC(0.61);
   s2->SetY1NDC(0.78); s2->SetY2NDC(0.93);
   s2->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

      c3->cd(4);
  KE_e->GetXaxis()->SetTitle("KE (MeV)");
  KE_e->GetYaxis()->SetTitle("Count");
  KE_e->SetLineColor(kBlue);
  KE_e->SetLineWidth(3);
  KE_e->Draw("sames");  

     c3->Update();
   gPad->Update();
    TPaveStats *s3 = (TPaveStats*)KE_e->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s3->SetX1NDC(0.61); s3->SetX2NDC(0.81);
   s3->SetY1NDC(0.78); s3->SetY2NDC(0.93);
   s3->SetTextColor(kBlue);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


// Proton, gamma, electron energy dist of posz over 1847
    c3->cd(5);
  KE_p_over->GetXaxis()->SetTitle("KE (MeV)");
  KE_p_over->GetYaxis()->SetTitle("Count");
  KE_p_over->SetLineColor(kRed);
  KE_p_over->SetLineWidth(3);
  KE_p_over->SetMinimum(1);
  KE_p_over->Draw();  

   c3->Update();
   gPad->Update();
    TPaveStats *s4 = (TPaveStats*)KE_p_over->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s4->SetX1NDC(0.21); s4->SetX2NDC(0.41);
   s4->SetY1NDC(0.78); s4->SetY2NDC(0.93);
   s4->SetTextColor(kRed);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


      c3->cd(5);
  KE_g_over->GetXaxis()->SetTitle("KE (MeV)");
  KE_g_over->GetYaxis()->SetTitle("Count");
  KE_g_over->SetLineColor(kGreen+3);
  KE_g_over->SetLineWidth(3);
  KE_g_over->Draw("sames");  

     c3->Update();
   gPad->Update();
    TPaveStats *s5 = (TPaveStats*)KE_g_over->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s5->SetX1NDC(0.41); s5->SetX2NDC(0.61);
   s5->SetY1NDC(0.78); s5->SetY2NDC(0.93);
   s5->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

      c3->cd(5);
  KE_e_over->GetXaxis()->SetTitle("KE (MeV)");
  KE_e_over->GetYaxis()->SetTitle("Count");
  KE_e_over->SetLineColor(kBlue);
  KE_e_over->SetLineWidth(3);
  KE_e_over->Draw("sames");  

     c3->Update();
   gPad->Update();
    TPaveStats *s6 = (TPaveStats*)KE_e_over->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s6->SetX1NDC(0.61); s6->SetX2NDC(0.81);
   s6->SetY1NDC(0.78); s6->SetY2NDC(0.93);
   s6->SetTextColor(kBlue);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

//////////////////////for dist
TCanvas* c2= new TCanvas("c2", "KE comparision", 20, 20, 1300, 900);
  c2->Divide(3,3);

c2->cd(1);
    hist_p->GetXaxis()->SetTitle("z(mm)");
  hist_p->GetYaxis()->SetTitle("y(mm)");
    hist_p->SetMarkerSize(2);
    hist_p->Draw("text same0 colz");   

c2->cd(2);
    hist_p_energy->GetXaxis()->SetTitle("z(mm)");
  hist_p_energy->GetYaxis()->SetTitle("y(mm)");
    hist_p_energy->SetMarkerSize(2);
    hist_p_energy->Draw("text same0 colz");   

    c2->cd(3);
    TH2D *h2_ratio = (TH2D*)hist_p_energy->Clone("h2_ratio");
    h2_ratio->Divide(hist_p);
    h2_ratio->SetTitle("proton mean energy");
    h2_ratio->SetStats(0);  
      h2_ratio->GetXaxis()->SetTitle("z(mm)");
    h2_ratio->GetYaxis()->SetTitle("y(mm)");
    h2_ratio->Draw(" text same0 colz");

c2->cd(4);
    hist_g->GetXaxis()->SetTitle("z(mm)");
  hist_g->GetYaxis()->SetTitle("y(mm)");
    hist_g->SetMarkerSize(2);
    hist_g->Draw("text same0 colz");   

c2->cd(5);
    hist_g_energy->GetXaxis()->SetTitle("z(mm)");
  hist_g_energy->GetYaxis()->SetTitle("y(mm)");
    hist_g_energy->SetMarkerSize(2);
    hist_g_energy->Draw("text same0 colz");   

    c2->cd(6);
    TH2D *h1_ratio = (TH2D*)hist_g_energy->Clone("h1_ratio");
    h1_ratio->Divide(hist_g);
    h1_ratio->SetTitle("gamma mean energy");
    h1_ratio->SetStats(0);  
      h1_ratio->GetXaxis()->SetTitle("z(mm)");
    h1_ratio->GetYaxis()->SetTitle("y(mm)");
    h1_ratio->Draw(" text same0 colz");


c2->cd(7);
    hist_e->GetXaxis()->SetTitle("z(mm)");
  hist_e->GetYaxis()->SetTitle("y(mm)");
    hist_e->SetMarkerSize(2);
    hist_e->Draw("text same0 colz");   

c2->cd(8);
    hist_e_energy->GetXaxis()->SetTitle("z(mm)");
  hist_e_energy->GetYaxis()->SetTitle("y(mm)");
    hist_e_energy->SetMarkerSize(2);
    hist_e_energy->Draw("text same0 colz");   

    c2->cd(9);
    TH2D *h3_ratio = (TH2D*)hist_e_energy->Clone("h3_ratio");
    h3_ratio->Divide(hist_e);
    h3_ratio->SetTitle("electron mean energy");
    h3_ratio->SetStats(0);  
      h3_ratio->GetXaxis()->SetTitle("z(mm)");
    h3_ratio->GetYaxis()->SetTitle("y(mm)");
    h3_ratio->Draw(" text same0 colz");
}