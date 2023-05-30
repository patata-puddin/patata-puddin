#include "TGraph.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TMath.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TH2.h"
#include <iostream>
#include "TGraph2D.h"
#include "TMultiGraph.h"
#include "TLegend.h"

using namespace std;
// exiting shield- angle of p,r,n (produced in shield, or passing)
// entering shield- angle of p,r,n

void exit_produce_z_proton()
{

TFile *P1dfile =new TFile("Al.root", "read");

  //Proton made in shield, exiting shield


  TTree *TVol1 = (TTree *) P1dfile -> Get("ext_shield_proton");

  Double_t posx;
  Double_t posy;
  Double_t posz;
  Double_t pdg;
  Double_t vposx;
  Double_t vposy;
  Double_t vposz;
  Double_t tracklen;
  Char_t vpvol[100];

  // std::string sh_vol;
  std::vector<double> vp_z_vec, tracklen_vec;
  std::vector<double> vp_z_vec_front, tracklen_vec_front, vp_z_vec_back, tracklen_vec_back;
  std::vector<double> vp_z_vec_side1, tracklen_vec_side1, vp_z_vec_side2, tracklen_vec_side2;
  std::vector<double> vp_z_vec_side3, tracklen_vec_side3, vp_z_vec_side4, tracklen_vec_side4;

  int j;
  int protoncount=0;
  int exception=0;
  int frontcount=0;
  int backcount=0;
  int side1count=0;
  int side2count=0;
  int side3count=0;
  int side4count=0;

  int under1826count=0;
  int under1828count=0;
  int back1826count=0;
  int front1826count=0;
  TVol1 -> SetBranchAddress("vpx",&vposx);
  TVol1 -> SetBranchAddress("vpy",&vposy);
  TVol1 -> SetBranchAddress("vpz",&vposz);
  TVol1 -> SetBranchAddress("tracklen",&tracklen);
  TVol1 -> SetBranchAddress("PartPosx",&posx);
  TVol1 -> SetBranchAddress("PartPosy",&posy);
  TVol1 -> SetBranchAddress("PartPosz",&posz);
  TVol1 -> SetBranchAddress("vpvol",&vpvol); 


  TH1D *hist_front = new TH1D("hist_front", "KE of front", 50, 1817, 1877);
  TH1D *hist_back = new TH1D("hist_back", "KE of back", 50, 1817, 1877);
  TH1D *hist_side1 = new TH1D("hist_side1_x", "KE of side1", 50, 1817, 1877);
  TH1D *hist_side2 = new TH1D("hist_side2_y", "KE of side2", 50, 1817, 1877);
  TH1D *hist_side3 = new TH1D("hist_side3_mx", "KE of side3", 50, 1817, 1877);
  TH1D *hist_side4 = new TH1D("hist_side4_my", "KE of side4", 50, 1817, 1877);
  TH1D *hist_22_vposz = new TH1D("vp_proton_shield_z", "vp of proton exiting shield_made in Shield", 50, 1817, 1877);
  
  TH2D *hist_22_vposxz = new TH2D("vp_proton_shield_xz", "vp of proton(x,z) exiting shield_made in Shield", 50, 17, 226, 50, 1817, 1877);
  TH2D *hist_22_vposxy = new TH2D("vp_proton_shield_xy", "vp of proton(x,y) exiting shield_made in Shield", 50, 17, 226, 50, -80, 130);

  TH2D *hist_length = new TH2D("vp_length", "vp (z) of proton - travel length", 100, 1817, 1877, 200, 0.000005, 3);
  TH2D *hist_len_front = new TH2D("vp_len_front", "vp (z) of proton - travel len_FRONT", 100, 1817, 1877, 200, 0.000005, 3);
  TH2D *hist_len_back = new TH2D("vp_len_back", "vp (z) of proton - travel len_BACK", 100, 1817, 1877, 200, 0.000005, 3);
  TH2D *hist_len_side1 = new TH2D("vp_len_side1", "vp (z) of proton - travel len_side1", 100, 1817, 1877, 200, 0.000005, 3);
  TH2D *hist_len_side2 = new TH2D("vp_len_side2", "vp (z) of proton - travel len_side2", 100, 1817, 1877, 200, 0.0005, 3);
  TH2D *hist_len_side3 = new TH2D("vp_len_side3", "vp (z) of proton - travel len_side3", 100, 1817, 1877, 200, 0.0005, 3);
  TH2D *hist_len_side4 = new TH2D("vp_len_side4", "vp (z) of proton - travel len_side4", 100, 1817, 1877, 200, 0.0005, 3);

  auto Entry = TVol1->GetBranch("vpx")->GetEntries() ;
 
   for (j=0;j<Entry; j++){

        TVol1 -> GetEntry(j);

    if(strcmp(vpvol, "Al_Shield") == 0){

        protoncount += 1;

        hist_22_vposz->Fill(vposz);
        hist_22_vposxz->Fill(vposx, vposz);
        hist_22_vposxy->Fill(vposx, vposy);
        hist_length->Fill(vposz, tracklen);
        vp_z_vec.push_back(vposz);
        tracklen_vec.push_back(tracklen);

        if(posz == 1872) {
          hist_front->Fill(vposz);
          hist_len_front->Fill(vposz, tracklen);

          vp_z_vec_front.push_back(vposz);
          tracklen_vec_front.push_back(tracklen);
          frontcount += 1;
          if(vposz < 1826){
            front1826count += 1;
          }

      } else if(posz == 1822) {
          hist_back->Fill(vposz);
          hist_len_back->Fill(vposz, tracklen);

          vp_z_vec_back.push_back(vposz);
          tracklen_vec_back.push_back(tracklen);
          backcount += 1;
          if(vposz < 1826){
            back1826count += 1;
          }
      } else if(abs(posy-125)<0.000000001) {
          hist_side2->Fill(vposz);
          hist_len_side2->Fill(vposz, tracklen);

          vp_z_vec_side2.push_back(vposz);
          tracklen_vec_side2.push_back(tracklen);
          side2count += 1;

      } else if(abs(posy+75)<0.000000001) {
          hist_side4->Fill(vposz);
          hist_len_side4->Fill(vposz, tracklen);

          vp_z_vec_side4.push_back(vposz);
          tracklen_vec_side4.push_back(tracklen);
          side4count += 1;

      } else if(abs(posx-21.25)<0.000000001) {
          hist_side3->Fill(vposz);
          hist_len_side3->Fill(vposz, tracklen);

          vp_z_vec_side3.push_back(vposz);
          tracklen_vec_side3.push_back(tracklen);
          side3count += 1;

      } else if(abs(posx-221.25)<0.000000001) {
          hist_side1->Fill(vposz);
          hist_len_side1->Fill(vposz, tracklen);

          vp_z_vec_side1.push_back(vposz);
          tracklen_vec_side1.push_back(tracklen);
          side1count += 1;
      } else {exception +=1;
      // cout << "z: " << posz << "    y: " << posy << "    x: " << posx << endl;

      }
    }
   }

  for (j=0;j<Entry; j++){
        TVol1 -> GetEntry(j);
    if(strcmp(vpvol, "Al_Shield") == 0){

        if(vposz < 1826){
          under1826count +=1;
        }
        else if(vposz < 1828){
          under1828count +=1;
        }
    }
  }
auto travelfrontmin = *min_element(tracklen_vec_front.begin(), tracklen_vec_front.end());

cout << "#of proton: " << protoncount << endl;
cout << "#of exception: " << exception << endl;
cout << "#of proton produced at z<1826: " << under1826count << endl;
cout << "#of proton produced at  1826 < z<1828: " << under1828count << endl;
cout << "min of front travel length: " << travelfrontmin << endl;

cout << "exit back, z < 1826: " << back1826count << endl;
cout << "exit front, z < 1826: " << front1826count << endl;
//    // //////Draw-----///////////------------///////
  TCanvas* c2 = new TCanvas("c2", "KE for real", 20, 20, 1000, 1000);
  c2->Divide(3,3);
  
  c2->cd(1)->SetLogy();
  c2->cd(2)->SetLogy();
  c2->cd(3)->SetLogy();
  c2->cd(4)->SetLogy();
  c2->cd(5)->SetLogy();
  c2->cd(6)->SetLogy();
  c2->cd(7)->SetLogy();

//For Proton exiting shield
c2->cd(1);
if(hist_22_vposz != nullptr){
  hist_22_vposz->GetXaxis()->SetTitle("z axis (mm)");
  hist_22_vposz->GetYaxis()->SetTitle("Count");
  hist_22_vposz->SetFillColorAlpha(kGreen+3, 0.9);
  hist_22_vposz->SetLineColor(kGreen+3);
  hist_22_vposz->SetFillStyle(3004);
  hist_22_vposz->SetTitle("Position (z) of proton produced in shield");
  // hist_22_vposz->SetMaximum(10000);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vposz->Draw();
}

c2->cd(2);
if(hist_front != nullptr){
  hist_front->GetXaxis()->SetTitle("z axis (mm)");
  hist_front->GetYaxis()->SetTitle("Count");
  hist_front->SetFillColorAlpha(kGreen+3, 0.9);
  hist_front->SetLineColor(kGreen+3);
  hist_front->SetFillStyle(3004);
  hist_front->SetTitle("Position (z) of proton produced in shield_FRONT");
  // hist_front->SetMaximum(10000);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_front->Draw();
}

c2->cd(3);
if(hist_back != nullptr){
  hist_back->GetXaxis()->SetTitle("z axis (mm)");
  hist_back->GetYaxis()->SetTitle("Count");
  hist_back->SetFillColorAlpha(kGreen+3, 0.9);
  hist_back->SetLineColor(kGreen+3);
  hist_back->SetFillStyle(3004);
  hist_back->SetTitle("Position (z) of proton produced in shield_BACK");
  // hist_back->SetMaximum(10000);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_back->Draw();
}

c2->cd(4);
if(hist_side3 != nullptr){
  hist_side3->GetXaxis()->SetTitle("z axis (mm)");
  hist_side3->GetYaxis()->SetTitle("Count");
  hist_side3->SetFillColorAlpha(2, 0.08);
  hist_side3->SetLineColor(2);
  hist_side3->SetTitle("Position (z) of proton produced in shield_SIDE3");
  // hist_side3->SetMaximum(10000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_side3->Draw();
}
       c2->Update();
  TPaveStats *s1 = (TPaveStats*)hist_side3->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s1->SetX1NDC(0.5); s1->SetX2NDC(0.7);
  s1->SetTextColor(kRed);
   gPad->Modified();
   gPad->Update();

c2->cd(4);
if(hist_side1 != nullptr){
  hist_side1->GetXaxis()->SetTitle("z axis (mm)");
  hist_side1->GetYaxis()->SetTitle("Count");
  hist_side1->SetFillColorAlpha(kGreen+3, 0.9);
  hist_side1->SetLineColor(kGreen+3);
  hist_side1->SetFillStyle(3004);
  hist_side1->SetTitle("Position (z) of proton produced in shield_SIDE1");
  // hist_side1->SetMaximum(10000);
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_side1->Draw("sames");
}
       c2->Update();
  TPaveStats *s2 = (TPaveStats*)hist_side1->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s2->SetX1NDC(0.71); s2->SetX2NDC(0.91);
  s2->SetTextColor(kGreen+3);
   gPad->Modified();
   gPad->Update();
   

c2->cd(5);
if(hist_side2 != nullptr){
  hist_side2->GetXaxis()->SetTitle("z axis (mm)");
  hist_side2->GetYaxis()->SetTitle("Count");
  hist_side2->SetFillColorAlpha(2, 0.08);
  hist_side2->SetLineColor(2);
  hist_side2->SetTitle("Position (z) of proton produced in shield_SIDE2");
  // hist_side2->SetMaximum(10000);
  hist_side2->Draw();
}
       c2->Update();
  TPaveStats *s3 = (TPaveStats*)hist_side2->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s3->SetX1NDC(0.5); s3->SetX2NDC(0.7);
  s3->SetTextColor(kRed);
   gPad->Modified();
   gPad->Update();

c2->cd(5);
if(hist_side4 != nullptr){
  hist_side4->GetXaxis()->SetTitle("z axis (mm)");
  hist_side4->GetYaxis()->SetTitle("Count");
  hist_side4->SetFillColorAlpha(kGreen+3, 0.9);
  hist_side4->SetLineColor(kGreen+3);
  hist_side4->SetFillStyle(3004);
  hist_side4->SetTitle("Position (z) of proton produced in shield_SIDE4");
  // hist_side4->SetMaximum(10000);
  hist_side4->Draw("sames");
}
         c2->Update();
  TPaveStats *s4 = (TPaveStats*)hist_side4->GetListOfFunctions()->FindObject("stats"); //----------try move stats
  s4->SetX1NDC(0.71); s4->SetX2NDC(0.91);
  s4->SetTextColor(kGreen+3);
   gPad->Modified();
   gPad->Update();

// c2->cd(8)->SetLogy();
// c2->cd(8)->SetLogz();
c2->cd(8);
if(hist_22_vposxz != nullptr){
  hist_22_vposxz->GetXaxis()->SetTitle("x (mm)");
  hist_22_vposxz->GetYaxis()->SetTitle("z (mm)");
  hist_22_vposxz->SetTitle("Position (x, z) of proton produced in shield");
  // hist_22_vposxz->SetMaximum(1000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vposxz->Draw("colz");
}

c2->cd(9);
if(hist_22_vposxy != nullptr){
  hist_22_vposxy->GetXaxis()->SetTitle("x (mm)");
  hist_22_vposxy->GetYaxis()->SetTitle("y (mm)");
  hist_22_vposxy->SetTitle("Position (x, y) of proton produced in shield");
  // hist_22_vposxz->SetMaximum(1000);
  //x_hist_AQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_22_vposxy->Draw("colz");
}

cout << "ok " << hist_22_vposxy->GetEntries() << endl;
//----------graph draw ----------------------------------
    TCanvas *c1 = new TCanvas("c1", "KE c1", 20, 20, 1000, 1000);
    c1->Divide(2,3);
    c1->cd(1)->SetLogy();
    c1->cd(2)->SetLogy();
    c1->cd(3)->SetLogy();
    c1->cd(4)->SetLogy();
    c1->cd(5)->SetLogy();
    c1->cd(6)->SetLogy();

    c1->cd(1);
    auto g = new TGraph(protoncount, &vp_z_vec[0], &tracklen_vec[0]);
    g->SetTitle("vertex point - travel length;z of vertex point (mm);travel length in Al (mm)");
    g->SetMaximum(5);
    g->SetMinimum(0.000005);
    g->SetStats(kTRUE);
    g->SetMarkerStyle(7);
    g->SetMarkerSize(10);
    // g->GetXaxis()->SetRangeUser(1821.9, 1828);
    cout << g->GetN() << endl;
    g->Draw("AP");

double min = * min_element(tracklen_vec.begin(), tracklen_vec.end());
cout << "hanyi" << min << endl;

    c1->cd(2);
    auto g_b = new TGraph(backcount, &vp_z_vec_back[0], &tracklen_vec_back[0]);
    g_b->SetTitle("vertex point - travel length_BACK;z of vertex point (mm);travel length in Al (mm)");
    // g->SetMaximum(14);
    g_b->SetStats(kTRUE);
    g_b->SetMaximum(5);
    g_b->SetMinimum(0.000005);
    g_b->SetMarkerStyle(7);
    g_b->SetMarkerSize(10);
    g_b->SetMarkerColor(kBlue);
    // g_b->GetXaxis()->SetRangeUser(1821.9, 1828);
    cout << g_b->GetN() << endl;
    g_b->Draw("AP");

    c1->cd(3);
    auto g_f = new TGraph(frontcount, &vp_z_vec_front[0], &tracklen_vec_front[0]);
    g_f->SetTitle("vertex point - travel length_FRONT;z of vertex point (mm);travel length in Al (mm)");
    g_f->SetMaximum(5);
    g_f->SetMinimum(0.000005);
    g_f->SetStats(kTRUE);
    g_f->SetMarkerStyle(7);
    g_f->SetMarkerSize(10);
    g_f->SetMarkerColor(kRed);
    // g_f->GetXaxis()->SetRangeUser(1821.9, 1828);
   cout << g_f->GetN() << endl;
    g_f->Draw("AP");

//Draw multigraph of x side
    c1->cd(4);
   TMultiGraph *mg_fb = new TMultiGraph();
    mg_fb->Add(g_b);    
    mg_fb->Add(g_f);
    mg_fb->SetTitle("ertex point - travel length_Front&Back");
    mg_fb->GetXaxis()->SetTitle("z of vertex point (mm)");
    mg_fb->GetYaxis()->SetTitle("travel length in Al (mm)");
    // mg_fb->GetXaxis()->SetRangeUser(1821.9, 1828);
    mg_fb->SetMaximum(5);
    mg_fb->SetMinimum(0.000005);
    mg_fb->Draw("AP");

  TLegend *leg2 = new TLegend(0.1, 0.7, 0.3, 0.9);
  leg2->SetFillColor(0);
  leg2->AddEntry(g_b, "back (-z)", "ap");
  leg2->AddEntry(g_f, "front (+z)", "ap");
  // leg2->SetBBoxCenterX(400);
  // leg2->SetBBoxCenterY(200);
  leg2->Draw();

  // side graph
    auto g_s1 = new TGraph(side1count, &vp_z_vec_side1[0], &tracklen_vec_side1[0]);
    g_s1->SetMarkerColor(kRed);
    g_s1->SetMarkerStyle(7);
    g_s1->SetMarkerSize(10);
    g_s1->SetName("side 1 (+x)");

    auto g_s2 = new TGraph(side2count, &vp_z_vec_side2[0], &tracklen_vec_side2[0]);
    g_s2->SetMarkerColor(kBlue);
    g_s2->SetMarkerStyle(7);
    g_s2->SetMarkerSize(10);
    g_s2->SetName("side 2 (+y)");

    auto g_s3 = new TGraph(side3count, &vp_z_vec_side3[0], &tracklen_vec_side3[0]);
    g_s3->SetMarkerColor(kGreen+3);
    g_s3->SetMarkerStyle(7);
    g_s3->SetMarkerSize(10);
    g_s3->SetName("side 3 (-x)");

    auto g_s4 = new TGraph(side4count, &vp_z_vec_side4[0], &tracklen_vec_side4[0]);
    g_s4->SetMarkerStyle(7);
    g_s4->SetMarkerSize(10);
    g_s4->SetMarkerColor(kPink);
    g_s4->SetName("side 4 (-y)");

//Draw multigraph of x side
    c1->cd(5);
   TMultiGraph *mg_x = new TMultiGraph();
    mg_x->Add(g_s3);    
    mg_x->Add(g_s1);
    mg_x->SetTitle("ertex point - travel length_SIDE");
    mg_x->GetXaxis()->SetTitle("z of vertex point (mm)");
    mg_x->GetYaxis()->SetTitle("travel length in Al (mm)");
    // mg_x->GetXaxis()->SetRangeUser(1821.9, 1828);
    mg_x->SetMaximum(5);
    mg_x->SetMinimum(0.000005);
  
   mg_x->Draw("AP");

  TLegend *leg = new TLegend(0.1, 0.7, 0.3, 0.9);
  leg->SetFillColor(0);
  leg->AddEntry(g_s3, "side 3 (-x)", "ap");
  leg->AddEntry(g_s1, "side 1 (+x)", "ap");
  // leg->SetBBoxCenterX(400);
  // leg->SetBBoxCenterY(200);
  leg->Draw();

//Draw multigraph of y side
     c1->cd(6);
   TMultiGraph *mg_y = new TMultiGraph();
   mg_y->Add(g_s4);
   mg_y->Add(g_s2);
   mg_y->SetTitle("ertex point - travel length_SIDE");
   mg_y->GetXaxis()->SetTitle("z of vertex point (mm)");
   mg_y->GetYaxis()->SetTitle("travel length in Al (mm)");
  //  mg_y->GetXaxis()->SetRangeUser(1821.9, 1828);
    mg_y->SetMaximum(5);
    mg_y->SetMinimum(0.000005);
   mg_y->Draw("AP");

TLegend *leg1 = new TLegend(0.1, 0.7, 0.3, 0.9);
leg1->SetFillColor(0);
leg1->AddEntry(g_s4, "side 4 (-y)", "ap");
leg1->AddEntry(g_s3, "side 2 (+y)", "ap");
// leg1->SetBBoxCenterX(400);
// leg1->SetBBoxCenterY(200);
leg1->Draw();
  //  c1->cd(6)->BuildLegend();

/// For histogram of travel length and vp pos ------------------------------
    TCanvas *c3 = new TCanvas("c3", "KE comparision", 20, 20, 1000, 1000);
    c3->Divide(4, 2);
    // c3->cd(1)->SetLogy();
    // c3->cd(2)->SetLogy();
    // c3->cd(3)->SetLogy();
    // c3->cd(4)->SetLogy();
    // c3->cd(5)->SetLogy();
    // c3->cd(6)->SetLogy();
    // c3->cd(7)->SetLogy();
    c3->cd(1)->SetLogz();
    c3->cd(3)->SetLogz();

c3->cd(1);
if(hist_length != nullptr){
  hist_length->GetXaxis()->SetTitle("z axis (mm)");
  hist_length->GetYaxis()->SetTitle("travel length");
  // hist_length->SetStats(0);
  // hist_length->GetXaxis()->SetRangeUser(1821.9, 1828);
  hist_length->Draw("colz");
}

c3->cd(2);
if(hist_len_front != nullptr){
  hist_len_front->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_front->GetYaxis()->SetTitle("travel length");
  // hist_len_front->SetStats(0);
  // hist_len_front->GetXaxis()->SetRangeUser(1821.9, 1828);
  hist_len_front->Draw("colz");
}

c3->cd(3);
if(hist_len_back != nullptr){
  hist_len_back->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_back->GetYaxis()->SetTitle("travel length");
  //  hist_len_back->GetXaxis()->SetRangeUser(1821.9, 1828);
  // hist_len_back->SetStats(0);
 hist_len_back->Draw("colz");
}


c3->cd(4);
if(hist_len_side1 != nullptr){
  hist_len_side1->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_side1->GetYaxis()->SetTitle("travel length");
  // hist_len_side1->GetXaxis()->SetRangeUser(1821.9, 1828);
  // hist_len_side1->SetStats(0);
  hist_len_side1->Draw("colz");
}

c3->cd(5);
if(hist_len_side2 != nullptr){
  hist_len_side2->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_side2->GetYaxis()->SetTitle("travel length");
  // hist_len_side2->GetXaxis()->SetRangeUser(1821.9, 1828);
  //  hist_len_side2->SetStats(0);
  // hist_len_side2->SetMaximum(14);
 hist_len_side2->Draw("colz");
}

c3->cd(6);
if(hist_len_side3 != nullptr){
  hist_len_side3->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_side3->GetYaxis()->SetTitle("travel length");
  // hist_len_side3->GetXaxis()->SetRangeUser(1821.9, 1828);
  // hist_len_side3->SetStats(0);
  hist_len_side3->Draw("colz");
}

c3->cd(7);
if(hist_len_side4 != nullptr){
  hist_len_side4->GetXaxis()->SetTitle("z axis (mm)");
  hist_len_side4->GetYaxis()->SetTitle("travel length");
  // hist_len_side4->GetXaxis()->SetRangeUser(1821.9, 1828);
  // hist_len_side4->SetMaximum(14);
  // hist_len_side4->SetStats(0);
  hist_len_side4->Draw("colz");
}
}

