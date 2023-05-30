#include "TGraph.h"
#include "TGraph2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TH2.h"
#include "TH3.h"

//exiting shield- total particle 
//exiting shield- E dist of p,r,n
void surface_KE()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Al.root", "read");

  TTree *TVol2 = (TTree *) P1dfile -> Get("ext_shield_proton");
  Double_t posx;
  Double_t posy;
  Double_t posz;
    int gammacount=0;
    Double_t sh_Pdg_sh;
int exception=0;
int againcountx=0;
  Double_t sh_KE_sh;
   Double_t KE_min, KE_max;
Char_t vpvol_p[100];

  int j;

 int s_z=0; 
 int s_mz=0;
 int s_y=0; 
 int s_my=0; 
 int s_x=0; 
 int s_mx=0;
  TVol2 -> SetBranchAddress("PartPosx",&posx);
  TVol2 -> SetBranchAddress("PartPosy",&posy);
  TVol2 -> SetBranchAddress("PartPosz",&posz);
  TVol2->SetBranchAddress("KE", &sh_KE_sh);
    TVol2 -> SetBranchAddress("vpvol",&vpvol_p); 


// TH1D *KE_front = new TH1D("KE_front", "KE of front", 50, 0, 20);
// TH1D *KE_below = new TH1D("KE_below", "KE of below", 50, 0, 20);

  TH3D *hist_front = new TH3D("hist_front", "KE of front", 10, 10, 250, 10, -90,135, 20, 0, 30);
  TH3D *hist_back = new TH3D("hist_back", "KE of back", 20, 10, 250, 20, -90,135, 20, 0, 30);
  TH3D *hist_side1 = new TH3D("hist_side1_x", "KE of side1", 20, 1800, 1890, 20, -90,135, 20, 0, 30);
  TH3D *hist_side2 = new TH3D("hist_side2_y", "KE of side2", 20, 1800, 1890, 20, 10,250, 20, 0, 30);
  TH3D *hist_side3 = new TH3D("hist_side3_mx", "KE of side3", 20, 1800, 1890, 20, -90,135, 20, 0, 30);
  TH3D *hist_side4 = new TH3D("hist_side4_my", "KE of side4", 20, 1800, 1890, 20, 10,250, 20, 0, 30);

    std::vector<double> x_front, x_back, x_side1, x_side2, x_side3, x_side4;
    std::vector<double> y_front, y_back, y_side1, y_side2, y_side3, y_side4;
    std::vector<double> z_front, z_back, z_side1, z_side2, z_side3, z_side4;

     auto Entry_KE = TVol2->GetBranch("KE")->GetEntries() ;
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
    // if(strcmp(vpvol_p, "World") == 0){
      if(posz == 1872) {
          s_z += 1;
          hist_front->Fill(posx, posy, sh_KE_sh);
          x_front.push_back(posx);
          y_front.push_back(posy);
          z_front.push_back(sh_KE_sh);

      } else if(posz == 1822) {
          s_mz += 1;
          hist_back->Fill(posx, posy, sh_KE_sh);
          x_back.push_back(posx);
          y_back.push_back(posy);
          z_back.push_back(sh_KE_sh);

      } else if(abs(posy-125)<0.000000001) {
          s_y += 1;
          hist_side2->Fill(posz, posx, sh_KE_sh);
          x_side2.push_back(posz);
          y_side2.push_back(posx);
          z_side2.push_back(sh_KE_sh);

      } else if(abs(posy+75)<0.000000001) {
          s_my += 1;
          hist_side4->Fill(posz, posx, sh_KE_sh);
          x_side4.push_back(posz);
          y_side4.push_back(posx);
          z_side4.push_back(sh_KE_sh);

      } else if(abs(posx-21.25)<0.000000001) {
          s_mx += 1;
          hist_side3->Fill(posz, posy, sh_KE_sh);
          x_side3.push_back(posz);
          y_side3.push_back(posy);
          z_side3.push_back(sh_KE_sh);

      } else if(abs(posx-221.25)<0.000000001) {
          s_x += 1;
          hist_side1->Fill(posz, posy, sh_KE_sh);
          x_side1.push_back(posz);
          y_side1.push_back(posy);
          z_side1.push_back(sh_KE_sh);

      } else {exception +=1;
      cout << "z: " << posz << "    y: " << posy << "    x: " << posx << endl;

      }
    gammacount += 1;
   //}
   }
int totalnum = s_x+s_y+s_z+s_mx+s_my+s_mz;
cout << "for z: " << s_z << "    for -z: " << s_mz <<endl;
cout << "for x: " << s_x << "    for -x: " << s_mx <<endl;
cout << "for y: " << s_y << "    for -y: " << s_my <<endl;
cout << "in total  " << totalnum << endl;
cout << "in gamma  " << gammacount << endl;
cout << "exception  " << exception << endl;
cout << "exception  for x " << againcountx << endl;



TCanvas* c1 = new TCanvas("c1", "KE comparision", 20, 20, 1000, 1000);
 c1->Divide(2, 3);
 c1->cd(1);
    if (hist_front != nullptr)
    {
        hist_front->GetXaxis()->SetTitle("x");
        hist_front->GetYaxis()->SetTitle("y");
        hist_front->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_front->SetLineColor(kGreen + 3);
        hist_front->SetFillStyle(3004);
        hist_front->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_front->SetTitle("hist of gamma at surface -FRONT");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_front->Draw("BOX2Z");
    }
 c1->cd(2);
    if (hist_back != nullptr)
    {
        hist_back->GetXaxis()->SetTitle("x");
        hist_back->GetYaxis()->SetTitle("y");
        hist_back->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_back->SetLineColor(kGreen + 3);
        hist_back->SetFillStyle(3004);
        hist_back->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_back->SetTitle("hist of gamma at surface -BACK");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_back->Draw("BOX2Z");
    }
 c1->cd(3);
    if (hist_side1 != nullptr)
    {
        hist_side1->GetXaxis()->SetTitle("z");
        hist_side1->GetYaxis()->SetTitle("y");
        hist_side1->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side1->SetLineColor(kGreen + 3);
        hist_side1->SetFillStyle(3004);
        hist_side1->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMaximum(400);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side1->SetTitle("hist of gamma at surface -SIDE 1");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side1->Draw("BOX2Z");
    }

 c1->cd(4);
    if (hist_side2 != nullptr)
    {
        hist_side2->GetXaxis()->SetTitle("z");
        hist_side2->GetYaxis()->SetTitle("x");
        hist_side2->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side2->SetLineColor(kGreen + 3);
        hist_side2->SetFillStyle(3004);
        hist_side2->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side2->SetTitle("hist of gamma at surface -SIDE 2");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side2->Draw("BOX2Z");
    }
 c1->cd(5);
    if (hist_side3 != nullptr)
    {
        hist_side3->GetXaxis()->SetTitle("z");
        hist_side3->GetYaxis()->SetTitle("y");
        hist_side3->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side3->SetLineColor(kGreen + 3);
        hist_side3->SetFillStyle(3004);
        hist_side3->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side3->SetTitle("hist of gamma at surface -SIDE 3");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side3->Draw("BOX2Z");
    }

 c1->cd(6);
    if (hist_side4 != nullptr)
    {
        hist_side4->GetXaxis()->SetTitle("z");
        hist_side4->GetYaxis()->SetTitle("x");
        hist_side4->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side4->SetLineColor(kGreen + 3);
        hist_side4->SetFillStyle(3004);
        hist_side4->SetMaximum(20);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side4->SetTitle("hist of gamma at surface -SIDE 4");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side4->Draw("BOX2Z");
    }
    //    // //////Draw-----///////////------------///////
    TCanvas *c2 = new TCanvas("c2", "KE comparision", 20, 20, 1000, 1000);
    c2->Divide(2, 3);

    c2->cd(1);
    auto g = new TGraph2D("1","",s_z, &x_front[0], &y_front[0], &z_front[0]);
    g->SetTitle("KE of surface _FRONT;x;y;KE (MeV)");
    // g->SetMaximum(14);
    // g->SetStats(kTRUE);
    cout << g->GetN() << endl;
    g->Draw("surf1z");

    c2->cd(2);
    auto g1 = new TGraph2D("2","",s_mz, &x_back[0], &y_back[0], &z_back[0]);
    // g1->SetTitle("KE of surface _BACK;x;y;KE (MeV)");
    // // g1->SetMaximum(14);
    // // g->SetStats(kTRUE);
    // cout << g1->GetN() << endl;
    // g1->Draw("surf1z");

    // c2->cd(3);
    // auto g2 = new TGraph2D(s_x, &x_side1[0], &y_side1[0], &z_side1[0]);
    // g2->SetTitle("KE of surface _SIDE1;x;y;KE (MeV)");
    // // g2->SetMaximum(14);
    // // g->SetStats(kTRUE);
    // cout << g2->GetN() << endl;
    // g2->Draw("surf1z");

    // c2->cd(4);
    // auto g3 = new TGraph2D(s_y, &x_side2[0], &y_side2[0], &z_side2[0]);
    // g3->SetTitle("KE of surface _SIDE2;x;y;KE (MeV)");
    // // g3->SetMaximum(14);
    // // g->SetStats(kTRUE);
    // cout << g3->GetN() << endl;
    // g3->Draw("surf1z");

    // c2->cd(5);
    // auto g4 = new TGraph2D(s_mx, &x_side3[0], &y_side3[0], &z_side3[0]);
    // g4->SetTitle("KE of surface _SIDE1;x;y;KE (MeV)");
    // // g4->SetMaximum(14);
    // // g->SetStats(kTRUE);
    // cout << g4->GetN() << endl;
    // g4->Draw("surf1z");

    // c2->cd(6);
    // auto g5 = new TGraph2D(s_my, &x_side4[0], &y_side4[0], &z_side4[0]);
    // g5->SetTitle("KE of surface _SIDE1;x;y;KE (MeV)");
    // // g5->SetMaximum(14);
    // // g->SetStats(kTRUE);
    // cout << g5->GetN() << endl;
    // g5->Draw("surf1z");
}