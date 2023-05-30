#include "TGraph.h"
#include "TString.h"

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TStyle.h"
#include "TPaveStats.h"

using namespace std;
//exiting shield- E dist of p,r,n (produced in shield, or passing)
//entering shield- E dist of p,r,n
void exit_part_vol()
{
    gROOT->Reset();

TFile *P1dfile =new TFile("Pb.root", "read");

  //Proton exiting shield

int x; // for canvas number


  TTree *TVol1 = (TTree *) P1dfile -> Get("ext_shield_proton");
  TTree *TVol2 = (TTree *) P1dfile -> Get("ext_shield_gamma");
  TTree *TVol3 = (TTree *) P1dfile -> Get("ext_shield_neutron");

  Double_t KE_p, KE_g, KE_n;
  Char_t vpvol_p[100], vpvol_g[100], vpvol_n[100];

  // std::string sh_vol;


  int j;
  int exception=0;
 
  TVol1 -> SetBranchAddress("KE",&KE_p);
  TVol1 -> SetBranchAddress("vpvol",&vpvol_p); 

  TVol2 -> SetBranchAddress("KE",&KE_g);
  TVol2 -> SetBranchAddress("vpvol",&vpvol_g); 

  TVol3 -> SetBranchAddress("KE",&KE_n);
  TVol3 -> SetBranchAddress("vpvol",&vpvol_n);



  TH1D *hist_sh_2212_KE_vpshield = new TH1D("Proton_shield", "Proton E, exiting shield_made in Shield", 100, 0, 30);
  TH1D *hist_sh_2212_KE_vpworld = new TH1D("Proton_world", "Proton E, exiting shield_made in World", 100, 0, 30);

  TH1D *hist_sh_22_KE_vpshield = new TH1D("Gamma_shield", "Gamma Energy exiting shield_made in Shield", 40, 0, 15);
  TH1D *hist_sh_22_KE_vpworld = new TH1D("Gamma_world", "Gamma Energy exiting shield_made in World", 40, 0, 15);

  TH1D *hist_sh_2112_KE_vpshield = new TH1D("Neutron_shield", "Neutron Energy exiting shield_made in Shield", 40, 0, 23);
  TH1D *hist_sh_2112_KE_vpworld = new TH1D("Neutron_world", "Neutron Energy exiting shield_made in World", 40, 0, 23);

  //For Proton
  auto Entry_KE_p = TVol1->GetBranch("KE")->GetEntries() ;
   for (j=0;j<Entry_KE_p; j++){
      TVol1 -> GetEntry(j);

         if(strcmp(vpvol_p, "Pb_Shield") == 0){
            hist_sh_2212_KE_vpshield -> Fill(KE_p);  
         }
         else if(strcmp(vpvol_p, "World") == 0){
            hist_sh_2212_KE_vpworld -> Fill(KE_p);
         }
         else{exception += 1;}
   }

//For gamma
  auto Entry_KE_g = TVol2->GetBranch("KE")->GetEntries() ;
   for (j=0;j<Entry_KE_g; j++){
      TVol2 -> GetEntry(j);

         if(strncmp(vpvol_g, "Pb_Shield", 9) == 0){
            hist_sh_22_KE_vpshield -> Fill(KE_g);  
         }
         else if(strcmp(vpvol_g, "World") == 0){
            hist_sh_22_KE_vpworld -> Fill(KE_g);
         }
         else{exception += 1;}
   }
//For neutron
  auto Entry_KE_n = TVol3->GetBranch("KE")->GetEntries() ;
   for (j=0;j<Entry_KE_n; j++){
      TVol3 -> GetEntry(j);

         if(strcmp(vpvol_n, "Pb_Shield") == 0){
            hist_sh_2112_KE_vpshield -> Fill(KE_n);  
         }
         else if(strcmp(vpvol_n, "World") == 0){
            hist_sh_2112_KE_vpworld -> Fill(KE_n);
         }
         else{exception += 1;}

   }

cout << "exception is: " << exception << endl;
// auto Entry_KE_2 = TVol2->GetBranch("sh_KE")->GetEntries() ;
 
//    for (j=0;j<Entry_KE_2; j++){
//       TVol2 -> GetEntry(j);

//       if(sh_Pdg_wo == 2212 ) {
//           hist_sh_2212_KE_vpworld -> Fill(sh_KE_wo);  
//           // cout << sh_vol << endl;
//       }



//       if(sh_Pdg_wo == 22 ) {
//           hist_sh_22_KE_vpworld -> Fill(sh_KE_wo);  
//       }


//       if(sh_Pdg_wo == 2112) {
//           hist_sh_2112_KE_vpworld -> Fill(sh_KE_wo);  
//       }

//    }

//    // //////Draw-----///////////------------///////
  TCanvas* c2 = new TCanvas("c2", "KE comparision", 20, 20, 450, 1000);
  c2->Divide(1,3);
  
  c2->cd(1)->SetLogy();
  c2->cd(2)->SetLogy();
  c2->cd(3)->SetLogy();
//For Proton exiting shield
c2->cd(1);
if(hist_sh_2212_KE_vpworld != nullptr){
  hist_sh_2212_KE_vpworld->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_2212_KE_vpworld->GetYaxis()->SetTitle("Count");
  hist_sh_2212_KE_vpworld->SetFillColorAlpha(kGreen+3, 0.9);
  hist_sh_2212_KE_vpworld->SetLineColor(kGreen+3);
  hist_sh_2212_KE_vpworld->SetFillStyle(3004);
//   hist_sh_2212_KE_vpworld->SetMaximum(400);
  hist_sh_2212_KE_vpworld->SetMinimum(1);
  hist_sh_2212_KE_vpworld->SetTitle("E dist of PROTON exiting shield_made in World");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_2212_KE_vpworld->Draw();

   c2->Update();
   gPad->Update();
    
  TPaveStats *s1 = (TPaveStats*)hist_sh_2212_KE_vpworld->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s1->SetX1NDC(0.61); s1->SetX2NDC(0.78);
   s1->SetY1NDC(0.73); s1->SetY2NDC(0.93);
   s1->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

}

//For Proton exiting shield
c2->cd(1);
if(hist_sh_2212_KE_vpworld != nullptr){
  hist_sh_2212_KE_vpshield->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_2212_KE_vpshield->GetYaxis()->SetTitle("Count");
//   hist_sh_2212_KE_vpshield->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_2212_KE_vpshield->SetLineColor(kGreen+3);
//   hist_sh_2212_KE_vpshield->SetFillStyle(3004);
//   hist_sh_2212_KE_vpshield->SetMaximum(400);
  hist_sh_2212_KE_vpshield->SetMinimum(1);
  hist_sh_2212_KE_vpshield->SetTitle("E dist of PROTON exiting shield_made in Shield");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_2212_KE_vpshield->Draw("sames");

   //c1->Update();
   gPad->Update();
    
  TPaveStats *s4 = (TPaveStats*)hist_sh_2212_KE_vpshield->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s4->SetX1NDC(0.79); s4->SetX2NDC(0.96);
   s4->SetY1NDC(0.73); s4->SetY2NDC(0.93);
   // s4->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

}

//For Gamma exiting shield
c2->cd(2);

  hist_sh_22_KE_vpshield->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_22_KE_vpshield->GetYaxis()->SetTitle("Count");
//   hist_sh_22_KE_vpshield->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_22_KE_vpshield->SetLineColor(kGreen+3);
//   hist_sh_22_KE_vpshield->SetFillStyle(3004);
  hist_sh_22_KE_vpshield->SetTitle("E dist of GAMMA exiting shield_made in Shield");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_22_KE_vpshield->Draw();

   //c1->Update();
    gPad->Update();
    
  TPaveStats *s5 = (TPaveStats*)hist_sh_22_KE_vpshield->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s5->SetX1NDC(0.79); s5->SetX2NDC(0.96);
   s5->SetY1NDC(0.73); s5->SetY2NDC(0.93);
//s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


//For Neutron exiting shield
c2->cd(3);

  hist_sh_2112_KE_vpshield->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_2112_KE_vpshield->GetYaxis()->SetTitle("Count");
//   hist_sh_2112_KE_vpshield->SetFillColorAlpha(kGreen+3, 0.9);
//   hist_sh_2112_KE_vpshield->SetLineColor(kGreen+3);
//   hist_sh_2112_KE_vpshield->SetFillStyle(3004);
  hist_sh_2112_KE_vpshield->SetTitle("E dist of NEUTRON exiting shield_made in Shield");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_2112_KE_vpshield->Draw();

   //c1->Update();
    gPad->Update();
    
  TPaveStats *s6 = (TPaveStats*)hist_sh_2112_KE_vpshield->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s6->SetX1NDC(0.79); s6->SetX2NDC(0.96);
   s6->SetY1NDC(0.73); s6->SetY2NDC(0.93);
//s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();





//For Gamma exiting shield
c2->cd(2);

  hist_sh_22_KE_vpworld->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_22_KE_vpworld->GetYaxis()->SetTitle("Count");
  hist_sh_22_KE_vpworld->SetFillColorAlpha(kGreen+3, 0.9);
  hist_sh_22_KE_vpworld->SetLineColor(kGreen+3);
  hist_sh_22_KE_vpworld->SetFillStyle(3004);
  hist_sh_22_KE_vpworld->SetTitle("E dist of GAMMA exiting shield_made in World");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_22_KE_vpworld->Draw("sames");

   c2->Update();
    gPad->Update();
    
  TPaveStats *s2 = (TPaveStats*)hist_sh_22_KE_vpworld->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s2->SetX1NDC(0.61); s2->SetX2NDC(0.78);
  s2->SetY1NDC(0.73); s2->SetY2NDC(0.93);
   s2->SetTextColor(kGreen+3);
//s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


//For Neutron exiting shield
c2->cd(3);

  hist_sh_2112_KE_vpworld->GetXaxis()->SetTitle("Energy (MeV)");
  hist_sh_2112_KE_vpworld->GetYaxis()->SetTitle("Count");
  hist_sh_2112_KE_vpworld->SetFillColorAlpha(kGreen+3, 0.9);
  hist_sh_2112_KE_vpworld->SetLineColor(kGreen+3);
  hist_sh_2112_KE_vpworld->SetFillStyle(3004);
  hist_sh_2112_KE_vpworld->SetTitle("E dist of NEUTRON exiting shield_made in World");
  //x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
  hist_sh_2112_KE_vpworld->Draw("sames");

   c2->Update();
    gPad->Update();
    
  TPaveStats *s3 = (TPaveStats*)hist_sh_2112_KE_vpworld->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s3->SetX1NDC(0.61); s3->SetX2NDC(0.78);
  s3->SetY1NDC(0.73); s3->SetY2NDC(0.93);
   s3->SetTextColor(kGreen+3);
//s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();


   //    // //////Draw-----///////////------------///////
  TCanvas* c1 = new TCanvas("c1", "KE comparision", 20, 20, 450, 1000);
  c1->Divide(1,3);
  
  c1->cd(1)->SetLogy();
  c1->cd(2)->SetLogy();
  c1->cd(3)->SetLogy();



}