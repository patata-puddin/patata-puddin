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

using namespace std;
// exiting shield- angle of p,r,n (produced in shield, or passing)
// entering shield- angle of p,r,n
// right, left, 구분 없음
// only for produced in shield
void exit_angle_proton()
{
    // gROOT->Reset();

    TFile *P1dfile = new TFile("Al.root", "read");

  TTree *TVol1 = (TTree *) P1dfile -> Get("ext_shield_proton");


  Double_t KE_p;
  Char_t vpvol_p[100];
  Double_t mom_xp, mom_yp, mom_zp;


    int j;
    int i;

    TVol1 -> SetBranchAddress("KE",&KE_p);
    TVol1 -> SetBranchAddress("vpvol",&vpvol_p); 
    TVol1 ->SetBranchAddress("mx", &mom_xp);
    TVol1 ->SetBranchAddress("my", &mom_yp);
    TVol1 ->SetBranchAddress("mz", &mom_zp);



    TH1D *hist_2212_phiangle = new TH1D("Initial+made_shield", "phi of Proton exiting", 60, -2, 362);
    TH1D *hist_2212_thetaangle = new TH1D("Initial+made_shield ", "theta of Proton exiting", 60, -2, 182);

    TH1D *hist_sh_2212_phiangle = new TH1D("made_shield", "phi of Proton exiting_made shield", 60, -2, 362);
    TH1D *hist_sh_2212_thetaangle = new TH1D("made_shield ", "theta of Proton exiting_made shield", 60, -2, 182);

 

    int protoncount=0;
    int exception_2212=0;
    int countunder90_2212=0;
    int countover90_2212=0;
    int countunder1MeV_2212=0;
    int countover1MeV_2212=0;
    int under1MeVunder90_2212=0;
    int under1MeVover90_2212=0;



//For Proton
    auto Entry_KE_2212 = TVol1->GetBranch("KE")->GetEntries();
    for (j = 0; j < Entry_KE_2212; j++)
    {
        TVol1->GetEntry(j);

        protoncount += 1;
            Double_t mx_sh = TMath::Abs(mom_xp);
            Double_t my_sh = TMath::Abs(mom_yp);

            Double_t theta = TMath::ACos(mom_zp) * 180 / TMath::Pi();
            Double_t phi = TMath::ATan(my_sh/mx_sh) * 180 / TMath::Pi();

            //theta
            hist_2212_thetaangle->Fill(theta);

             //For phi-----------
            if ((mom_xp > 0) && (mom_yp > 0))
            {     hist_2212_phiangle->Fill(phi);
            }
            else if ((mom_xp < 0) && (mom_yp > 0))
            {
                Double_t phi2=180-phi;
                hist_2212_phiangle->Fill(phi2);         
            }
            else if ((mom_xp < 0) && (mom_yp < 0))
            {   Double_t phi3=180+phi;
                hist_2212_phiangle->Fill(phi3);    
            }
            else if ((mom_xp > 0) && (mom_yp < 0))
            {   Double_t phi4=360-phi;
                hist_2212_phiangle->Fill(phi4);      
            }
            else 
            {
                exception_2212+=1;
            }
            
            if(strcmp(vpvol_p, "Al_Shield") == 0){
            //For theta
                hist_sh_2212_thetaangle->Fill(theta);
            
             //For phi-----------
            if ((mom_xp > 0) && (mom_yp > 0))
            {     hist_sh_2212_phiangle->Fill(phi);
            }
            else if ((mom_xp < 0) && (mom_yp > 0))
            {
                Double_t phi2=180-phi;
                hist_sh_2212_phiangle->Fill(phi2);         
            }
            else if ((mom_xp < 0) && (mom_yp < 0))
            {   Double_t phi3=180+phi;
                hist_sh_2212_phiangle->Fill(phi3);    
            }
            else if ((mom_xp > 0) && (mom_yp < 0))
            {   Double_t phi4=360-phi;
                hist_sh_2212_phiangle->Fill(phi4);      
            }
            else 
            {
                exception_2212+=1;
            }
            }
            //count in general----------angle
            if(theta<90){
                countunder90_2212 +=1;
            }

            else if(theta>=90){
                countover90_2212 +=1;
            }
            else{exception_2212 +=1;}

            //count in general----------energy
            if(KE_p<1){
                countunder1MeV_2212 +=1;
            }

            else if(KE_p>=1){
                countover1MeV_2212 +=1;
            }
            else{exception_2212 +=1;}
            

                //count in general----------energy and angle
            if(KE_p<1 && theta <90){
                under1MeVunder90_2212 +=1;
            }

            else if(KE_p<1 && theta >=90){
                under1MeVover90_2212 +=1;
            }
            
    }



cout << "Proton " << endl;
cout << "# proton: " << protoncount << endl;
cout << "# under 90: " << countunder90_2212 << endl;
cout << "# over 90: " << countover90_2212 << endl;
cout << "# under 1MeV: " << countunder1MeV_2212 << endl;
cout << "# over 1MeV: " << countover1MeV_2212 << endl;
cout << "# under 1MeV && under 90: " << under1MeVunder90_2212 << endl;
cout << "# under 1MeV && over 90: " << under1MeVover90_2212 << endl;
cout << "exception: " << exception_2212 << endl;


    // //////Draw-----///////////------------///////-----------////////
    TCanvas *c2 = new TCanvas("c2", "KE comparision", 20, 20, 1000, 1000);
    c2->Divide(1,2);
    c2->cd(1)->SetGrid();
    c2->cd(2)->SetGrid();

    c2->cd(1)->SetLogy();
    c2->cd(2)->SetLogy();


    // c2->cd(4)->SetLogy();

//angle plot
    c2->cd(1);
    if (hist_2212_thetaangle != nullptr)
    {
        hist_2212_thetaangle->GetXaxis()->SetTitle("theta angle");
        hist_2212_thetaangle->GetYaxis()->SetTitle("Count");
        hist_2212_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_2212_thetaangle->SetLineColor(kGreen + 3);
        hist_2212_thetaangle->SetFillStyle(3004);
        // hist_2212_thetaangle->SetMaximum(9000);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_2212_thetaangle->Draw();
           c2->Update();
   gPad->Update();
    
  TPaveStats *s1 = (TPaveStats*)hist_2212_thetaangle->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s1->SetX1NDC(0.61); s1->SetX2NDC(0.78);
   s1->SetY1NDC(0.73); s1->SetY2NDC(0.93);
   s1->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();

    }

    c2->cd(2);
    if (hist_sh_2212_phiangle != nullptr)
    {
        hist_2212_phiangle->GetXaxis()->SetTitle("phi angle");
        hist_2212_phiangle->GetYaxis()->SetTitle("Count");
        hist_2212_phiangle->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_2212_phiangle->SetLineColor(kGreen + 3);
        hist_2212_phiangle->SetFillStyle(3004);
        hist_2212_phiangle->SetMinimum(1);
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_2212_phiangle->Draw();

                   c2->Update();
    gPad->Update();
          TPaveStats *s3 = (TPaveStats*)hist_2212_phiangle->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s3->SetX1NDC(0.61); s3->SetX2NDC(0.78);
  s3->SetY1NDC(0.73); s3->SetY2NDC(0.93);
   s3->SetTextColor(kGreen+3);
//s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();
    }

    c2->cd(1);
    if (hist_sh_2212_thetaangle != nullptr)
    {
        hist_sh_2212_thetaangle->GetXaxis()->SetTitle("theta angle");
        hist_sh_2212_thetaangle->GetYaxis()->SetTitle("Count");
        // hist_sh_2212_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
        // hist_sh_2212_thetaangle->SetLineColor(kGreen + 3);
        // hist_sh_2212_thetaangle->SetFillStyle(3004);
        // hist_sh_2212_thetaangle->SetMaximum(9000);
        // hist_sh_22_thetaangle_x->SetMinimum(1);
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_sh_2212_thetaangle->Draw("sames");
        c2->Update();
            gPad->Update();
          TPaveStats *s2 = (TPaveStats*)hist_sh_2212_thetaangle->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s2->SetX1NDC(0.79); s2->SetX2NDC(0.96);
   s2->SetY1NDC(0.73); s2->SetY2NDC(0.93);
//    s2->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();
    }

 

    c2->cd(2);
    if (hist_sh_2212_phiangle != nullptr)
    {
        hist_sh_2212_phiangle->GetXaxis()->SetTitle("phi angle");
        hist_sh_2212_phiangle->GetYaxis()->SetTitle("Count");
                hist_sh_2212_phiangle->SetMinimum(1);

        // hist_sh_2212_phiangle->SetFillColorAlpha(kGreen + 3, 0.9);
        // hist_sh_2212_phiangle->SetLineColor(kGreen + 3);
        // hist_sh_2212_phiangle->SetFillStyle(3004);
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_sh_2212_phiangle->Draw("sames");

                c2->Update();
            gPad->Update();
          TPaveStats *s4 = (TPaveStats*)hist_sh_2212_phiangle->GetListOfFunctions()->FindObject("stats"); //----------try move stats
   s4->SetX1NDC(0.79); s4->SetX2NDC(0.96);
   s4->SetY1NDC(0.73); s4->SetY2NDC(0.93);
//    s2->SetTextColor(kGreen+3);
   //s11->SetTextColor(kBlue);
   gPad->Modified();
   gPad->Update();
    }
}