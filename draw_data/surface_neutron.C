#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TH2.h"
#include <iostream>

using namespace std;
//exiting shield- total particle 
//exiting shield- E dist of p,r,n
void surface_neutron()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("test_2.root", "read");

  TTree *TVol2 = (TTree *) P1dfile -> Get("ext_shield_neutron");
  Double_t posx;
  Double_t posy;
  Double_t posz;
    int neutroncount=0;
    Double_t sh_Pdg_sh;
int exception=0;
int againcountx=0;
  Double_t KE;
Char_t vpvol[100];


  int j;

 int s_z=0; 
 int s_mz=0;
 int s_y=0; 
 int s_my=0; 
 int s_x=0; 
 int s_mx=0;

 int side2_under1840=0;
 int side1_under1840=0;
 int side3_under1840=0;
 int side4_under1840=0;

  TVol2 -> SetBranchAddress("PartPosx",&posx);
  TVol2 -> SetBranchAddress("PartPosy",&posy);
  TVol2 -> SetBranchAddress("PartPosz",&posz);
    TVol2->SetBranchAddress("KE", &KE);
  TVol2 -> SetBranchAddress("vpvol",&vpvol); 


// TH1D *KE_front = new TH1D("KE_front", "KE of front", 50, 0, 20);
// TH1D *KE_below = new TH1D("KE_below", "KE of below", 50, 0, 20);

  TH2D *hist_front = new TH2D("hist_front", "KE of front", 50, 17, 226, 50, -80,130);
  TH2D *hist_back = new TH2D("hist_back", "KE of back", 50, 17, 226, 50, -80,130);
  TH2D *hist_side1 = new TH2D("hist_side1_x", "KE of side1", 50, 1817, 1877, 50, -80,130);
  TH2D *hist_side2 = new TH2D("hist_side2_y", "KE of side2", 50, 1817, 1877, 50, 17,226);
  TH2D *hist_side3 = new TH2D("hist_side3_mx", "KE of side3", 50, 1817, 1877, 50, -80,130);
  TH2D *hist_side4 = new TH2D("hist_side4_my", "KE of side4", 50, 1817, 1877, 50, 17,226);

     auto Entry_KE = TVol2->GetBranch("KE")->GetEntries() ;
   for (j=0;j<Entry_KE; j++){
      TVol2 -> GetEntry(j);
    if(strcmp(vpvol, "World") == 0){

      if(posz == 1872) {
          s_z += 1;
          hist_front->Fill(posx, posy);

      } else if(posz == 1822) {
          s_mz += 1;
          hist_back->Fill(posx, posy);

      } else if(abs(posy-125)<0.000000001) {
          s_y += 1;
          hist_side2->Fill(posz, posx);
          if(posz<1840){
            side2_under1840 +=1;
          }
      } else if(abs(posy+75)<0.000000001) {
          s_my += 1;
          hist_side4->Fill(posz, posx);
                    if(posz<1840){
            side4_under1840 +=1;
          }
      } else if(abs(posx-21.25)<0.000000001) {
          s_mx += 1;
          hist_side3->Fill(posz, posy);
                    if(posz<1840){
            side3_under1840 +=1;
          }
      } else if(abs(posx-221.25)<0.000000001) {
          s_x += 1;
          hist_side1->Fill(posz, posy);
                    if(posz<1840){
            side1_under1840 +=1;
          }
      } else {exception +=1;
      cout << "z: " << posz << "    y: " << posy << "    x: " << posx << endl;

      }
    neutroncount += 1;
    }
   }
int totalnum = s_x+s_y+s_z+s_mx+s_my+s_mz;
double side1_percent_1840 = static_cast<double>(side1_under1840) / s_x * 100;
double side2_percent_1840 = static_cast<double>(side2_under1840) / s_y * 100;
double side3_percent_1840 = static_cast<double>(side3_under1840) / s_mx * 100;
double side4_percent_1840 = static_cast<double>(side4_under1840) / s_my * 100;

cout << "for z: " << s_z << "    for -z: " << s_mz <<endl;
cout << "for x: " << s_x << "    for -x: " << s_mx <<endl;
cout << "for y: " << s_y << "    for -y: " << s_my <<endl;
cout << "in total  " << totalnum << endl;
cout << "in neutron  " << neutroncount << endl;
cout << "exception  " << exception << endl;
cout << "exception  for x " << againcountx << endl;
cout << endl;
cout << "For side1, z pos under 1840 is  " << side1_percent_1840 << endl;
cout << "For side2, z pos under 1840 is  " << side2_percent_1840 << endl;
cout << "For side3, z pos under 1840 is  " << side3_percent_1840 << endl;
cout << "For side4, z pos under 1840 is  " << side4_percent_1840 << endl;

   //////Draw-----///////////------------///////
  TCanvas* c2 = new TCanvas("c2", "KE comparision", 20, 20, 450, 1000);
const Int_t nx = 6;
const char *people[nx] = {"z", "-z","y", "-y", "x", "-x" };

int i;
TH1F *h = new TH1F("neutron", "exit surface of neutron", nx,0,nx);

for (i=1;i<=s_z;i++) {
 h->Fill(people[0],1);
 }
for (i=1;i<=s_mz;i++) {
 h->Fill(people[1],1);
 }
for (i=1;i<=s_y;i++) {
 h->Fill(people[2],1);
 }
for (i=1;i<=s_my;i++) {
 h->Fill(people[3],1);
 }
for (i=1;i<=s_x;i++) {
 h->Fill(people[4],1);
 }
for (i=1;i<=s_mx;i++) {
 h->Fill(people[5],1);
 }


  h->SetFillColorAlpha(2, 0.4);
  h->SetLineColor(2);
  // h->SetFillStyle(3004);
  h->SetBarWidth(0.22);
  h->SetBarOffset(0.3);
  // h->SetStats(11);
  gStyle->SetOptStat(11);
  h->SetLabelSize(0.1);
  // h->SetMinimum(0);


// h->LabelsDeflate();
h->SetMarkerSize(2);
h->Draw("bar Text90");
// h->SetMaximum(10000000);
// h->SetMinimum(1);
gPad->SetLogy();
gPad->SetGrid();

TCanvas* c1 = new TCanvas("c1", "KE comparision", 20, 20, 1000, 1000);
 c1->Divide(2, 3);

 c1->cd(1)->SetLogz();
 c1->cd(2)->SetLogz();
 c1->cd(3)->SetLogz();
 c1->cd(4)->SetLogz();
 c1->cd(5)->SetLogz();
 c1->cd(6)->SetLogz();

 c1->cd(1);
    if (hist_front != nullptr)
    {
        hist_front->GetXaxis()->SetTitle("x");
        hist_front->GetYaxis()->SetTitle("y");
        hist_front->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_front->SetLineColor(kGreen + 3);
        hist_front->SetFillStyle(3004);
        hist_front->SetMaximum(4);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_front->SetTitle("hist of neutron at surface -FRONT");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_front->Draw("colz");
    }
 c1->cd(2);
    if (hist_back != nullptr)
    {
        hist_back->GetXaxis()->SetTitle("x");
        hist_back->GetYaxis()->SetTitle("y");
        hist_back->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_back->SetLineColor(kGreen + 3);
        hist_back->SetFillStyle(3004);
        hist_back->SetMaximum(4);
        // hist_back->SetMinimum(1);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_back->SetTitle("hist of neutron at surface -BACK");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_back->Draw("colz");
    }
 c1->cd(3);
    if (hist_side1 != nullptr)
    {
        hist_side1->GetXaxis()->SetTitle("z");
        hist_side1->GetYaxis()->SetTitle("y");
        hist_side1->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side1->SetLineColor(kGreen + 3);
        hist_side1->SetFillStyle(3004);
        hist_side1->SetMaximum(4);
        // hist_sh_22_thetaangle_x->SetMaximum(400);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side1->SetTitle("hist of neutron at surface -SIDE 1");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side1->Draw("colz");
    }

 c1->cd(4);
    if (hist_side2 != nullptr)
    {
        hist_side2->GetXaxis()->SetTitle("z");
        hist_side2->GetYaxis()->SetTitle("x");
        hist_side2->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side2->SetLineColor(kGreen + 3);
        hist_side2->SetFillStyle(3004);
        hist_side2->SetMaximum(4);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side2->SetTitle("hist of neutron at surface -SIDE 2");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side2->Draw("colz");
    }
 c1->cd(5);
    if (hist_side3 != nullptr)
    {
        hist_side3->GetXaxis()->SetTitle("z");
        hist_side3->GetYaxis()->SetTitle("y");
        hist_side3->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side3->SetLineColor(kGreen + 3);
        hist_side3->SetFillStyle(3004);
        hist_side3->SetMaximum(4);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side3->SetTitle("hist of neutron at surface -SIDE 3");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side3->Draw("colz");
    }

 c1->cd(6);
    if (hist_side4 != nullptr)
    {
        hist_side4->GetXaxis()->SetTitle("z");
        hist_side4->GetYaxis()->SetTitle("x");
        hist_side4->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_side4->SetLineColor(kGreen + 3);
        hist_side4->SetFillStyle(3004);
        hist_side4->SetMaximum(4);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        hist_side4->SetTitle("hist of neutron at surface -SIDE 4");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_side4->Draw("colz");
    }
}