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
void ent_part_angle()
{
    // gROOT->Reset();

    TFile *P1dfile = new TFile("out_noal.root", "read");

  TTree *TVol1 = (TTree *) P1dfile -> Get("Detector_2");


  Double_t KE_p, KE_g, KE_n;
  Char_t vpvol_p[100], vpvol_g[100], vpvol_n[100];
  Double_t mom_xp, mom_xg, mom_xn;
  Double_t mom_yp, mom_yg, mom_yn;
  Double_t mom_zp, mom_zg, mom_zn;
  Double_t posx, posy, posz;
  Double_t pdg;

    int j;
    int i;

    TVol1 -> SetBranchAddress("KE",&KE_p);
    TVol1 -> SetBranchAddress("vpvol",&vpvol_p); 
    TVol1 ->SetBranchAddress("mx", &mom_xp);
    TVol1 ->SetBranchAddress("my", &mom_yp);
    TVol1 ->SetBranchAddress("mz", &mom_zp);
    TVol1 ->SetBranchAddress("pdg", &pdg);
  TVol1 -> SetBranchAddress("px",&posx);
  TVol1 -> SetBranchAddress("py",&posy);
  TVol1 -> SetBranchAddress("pz",&posz);

    TH1D *hist_sh_2212_phiangle = new TH1D("Proton_phi", "Angle (phi) of Proton exiting shield", 60, -2, 362);
    TH1D *hist_sh_2212_thetaangle = new TH1D("Proton_theta", "Angle (theta) of Proton exiting shield", 60, -2, 182);

    TH1D *hist_sh_22_phiangle = new TH1D("Gamma_phi", "Angle (phi) of Gamma exiting shield", 60, -2, 362);
    TH1D *hist_sh_22_thetaangle = new TH1D("Gamma_theta", "Angle (theta) of Gamma exiting shield", 60, -2, 182);

    TH1D *hist_sh_2112_phiangle = new TH1D("Neutron_phi", "Angle (phi) of Neutron exiting shield", 60, -2, 362);
    TH1D *hist_sh_2112_thetaangle = new TH1D("Neutron_theta", "Angle (theta) of Neutron exiting shield", 60, -2, 182);


    int protoncount=0;
    int exception_2212=0;
    int countunder90_2212=0;
    int countover90_2212=0;
    int countunder1MeV_2212=0;
    int countover1MeV_2212=0;
    int under1MeVunder90_2212=0;
    int under1MeVover90_2212=0;

    int gammacount=0;
    int exception_22=0;
    int countunder90_22=0;
    int countover90_22=0;
    int countunder1MeV_22=0;
    int countover1MeV_22=0;
    int under1MeVunder90_22=0;
    int under1MeVover90_22=0;

    int neutroncount=0;
    int exception_2112=0;
    int countunder90_2112=0;
    int countover90_2112=0;
    int countunder1MeV_2112=0;
    int countover1MeV_2112=0;
    int under1MeVunder90_2112=0;
    int under1MeVover90_2112=0;

//For Proton
    auto Entry_KE_2212 = TVol1->GetBranch("KE")->GetEntries();
    for (j = 0; j < Entry_KE_2212; j++)
    {
        TVol1->GetEntry(j);
    if((abs(posx+231) < 0.0000001) && (strcmp(vpvol_p, "Detector2") != 0)){           
        if(pdg ==2212){

                protoncount += 1;
            Double_t mx_sh = TMath::Abs(mom_xp);
            Double_t my_sh = TMath::Abs(mom_yp);

            Double_t theta = TMath::ACos(mom_zp) * 180 / TMath::Pi();
            Double_t phi = TMath::ATan(my_sh/mx_sh) * 180 / TMath::Pi();

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

            //count in general----------angle
            if(theta<90){
                countunder90_2212 +=1;
            }

            else if(theta>=90){
                countover90_2212 +=1;
            }
            else{exception_2212 +=1;}
        }
        
    }
    }

// //gamma
//     auto Entry_KE_22 = TVol2->GetBranch("KE")->GetEntries();
//     for (j = 0; j < Entry_KE_22; j++)
//     {
//         TVol2->GetEntry(j);

//             gammacount += 1;
//             Double_t mx_sh = TMath::Abs(mom_xg);
//             Double_t my_sh = TMath::Abs(mom_yg);

//             Double_t theta = TMath::ACos(mom_zg) * 180 / TMath::Pi();
//             Double_t phi = TMath::ATan(my_sh/mx_sh) * 180 / TMath::Pi();

//             //For theta
//                 hist_sh_22_thetaangle->Fill(theta);
//                 theta_22_KE->Fill(theta, KE_g);


//              //For phi-----------
//             if ((mom_xg > 0) && (mom_yg > 0))
//             {     hist_sh_22_phiangle->Fill(phi);
//                 phi_22_KE->Fill(phi, KE_g);
//             }
//             else if ((mom_xg < 0) && (mom_yg > 0))
//             {
//                 Double_t phi2=180-phi;
//                 hist_sh_22_phiangle->Fill(phi2);         
//                 phi_22_KE->Fill(phi2, KE_g);
//             }
//             else if ((mom_xg < 0) && (mom_yg < 0))
//             {   Double_t phi3=180+phi;
//                 hist_sh_22_phiangle->Fill(phi3);    
//                 phi_22_KE->Fill(phi3, KE_g);
//             }
//             else if ((mom_xg > 0) && (mom_yg < 0))
//             {   Double_t phi4=360-phi;
//                 hist_sh_22_phiangle->Fill(phi4);      
//                 phi_22_KE->Fill(phi4, KE_g);
//             }
//             else 
//             {
//                 exception_22+=1;
//             }

//             //count in general----------angle
//             if(theta<90){
//                 countunder90_22 +=1;
//             }

//             else if(theta>=90){
//                 countover90_22 +=1;
//             }
//             else{exception_22 +=1;}

//             //count in general----------energy
//             if(KE_g<1){
//                 countunder1MeV_22 +=1;
//             }

//             else if(KE_g>=1){
//                 countover1MeV_22 +=1;
//             }
//             else{exception_22 +=1;}

//                 //count in general----------energy and angle
//             if(KE_g<1 && theta <90){
//                 under1MeVunder90_22 +=1;
//             }

//             else if(KE_g<1 && theta >=90){
//                 under1MeVover90_22 +=1;
//             }

//     }
        
// //neutron
//     auto Entry_KE_2112 = TVol3->GetBranch("KE")->GetEntries();
//     for (j = 0; j < Entry_KE_2112; j++)
//     {
//         TVol3->GetEntry(j);

//             neutroncount += 1;
//             Double_t mx_sh = TMath::Abs(mom_xn);
//             Double_t my_sh = TMath::Abs(mom_yn);

//             Double_t theta = TMath::ACos(mom_zn) * 180 / TMath::Pi();
//             Double_t phi = TMath::ATan(my_sh/mx_sh) * 180 / TMath::Pi();

//             //For theta
//                 hist_sh_2112_thetaangle->Fill(theta);
//                 theta_2112_KE->Fill(theta, KE_n);


//              //For phi-----------
//             if ((mom_xn > 0) && (mom_yn > 0))
//             {     hist_sh_2112_phiangle->Fill(phi);
//                 phi_2112_KE->Fill(phi, KE_n);
//             }
//             else if ((mom_xn < 0) && (mom_yn > 0))
//             {
//                 Double_t phi2=180-phi;
//                 hist_sh_2112_phiangle->Fill(phi2);         
//                 phi_2112_KE->Fill(phi2, KE_n);
//             }
//             else if ((mom_xn < 0) && (mom_yn < 0))
//             {   Double_t phi3=180+phi;
//                 hist_sh_2112_phiangle->Fill(phi3);    
//                 phi_2112_KE->Fill(phi3, KE_n);
//             }
//             else if ((mom_xn > 0) && (mom_yn < 0))
//             {   Double_t phi4=360-phi;
//                 hist_sh_2112_phiangle->Fill(phi4);      
//                 phi_2112_KE->Fill(phi4, KE_n);
//             }
//             else 
//             {
//                 exception_2112+=1;
//             }

//             //count in general----------angle
//             if(theta<90){
//                 countunder90_2112 +=1;
//             }

//             else if(theta>=90){
//                 countover90_2112 +=1;
//             }
//             else{exception_2112 +=1;}

//             //count in general----------energy
//             if(KE_n<1){
//                 countunder1MeV_2112 +=1;
//             }

//             else if(KE_n>=1){
//                 countover1MeV_2112 +=1;
//             }
//             else{exception_2112 +=1;}

//                 //count in general----------energy and angle
//             if(KE_n<1 && theta <90){
//                 under1MeVunder90_2112 +=1;
//             }

//             else if(KE_n<1 && theta >=90){
//                 under1MeVover90_2112 +=1;
//             }

//     }

cout << "Proton " << endl;
cout << "# proton: " << protoncount << endl;
cout << "# under 90: " << countunder90_2212 << endl;
cout << "# over 90: " << countover90_2212 << endl;
cout << "exception: " << exception_2212 << endl;

// cout << "/n Gamma " << endl;
// cout << "# gamma: " << gammacount << endl;
// cout << "# under 90: " << countunder90_22 << endl;
// cout << "# over 90: " << countover90_22 << endl;
// cout << "# under 1MeV: " << countunder1MeV_22 << endl;
// cout << "# over 1MeV: " << countover1MeV_22 << endl;
// cout << "# under 1MeV && under 90: " << under1MeVunder90_22 << endl;
// cout << "# under 1MeV && over 90: " << under1MeVover90_22 << endl;
// cout << "exception: " << exception_22 << endl;

// cout << "/n Neutron " << endl;
// cout << "# Neutron: " << neutroncount << endl;
// cout << "# under 90: " << countunder90_2112 << endl;
// cout << "# over 90: " << countover90_2112 << endl;
// cout << "# under 1MeV: " << countunder1MeV_2112 << endl;
// cout << "# over 1MeV: " << countover1MeV_2112 << endl;
// cout << "# under 1MeV && under 90: " << under1MeVunder90_2112 << endl;
// cout << "# under 1MeV && over 90: " << under1MeVover90_2112 << endl;
// cout << "exception: " << exception_2112 << endl;


    // //////Draw-----///////////------------///////-----------////////
    TCanvas *c2 = new TCanvas("c2", "KE comparision", 20, 20, 1000, 1000);
    c2->Divide(3,2);

    TCanvas *c1 = new TCanvas("c1", "KE comparision", 20, 20, 1200, 900);
    c1->Divide(3, 2);


    c2->cd(1)->SetLogy();
    c2->cd(2)->SetLogy();
    c2->cd(3)->SetLogy();    
    c2->cd(4)->SetLogy();
    c2->cd(5)->SetLogy();
    c2->cd(6)->SetLogy();  

    // c2->cd(4)->SetLogy();

//angle plot---------------------------------
    c2->cd(1);
    if (hist_sh_2212_thetaangle != nullptr)
    {
        hist_sh_2212_thetaangle->GetXaxis()->SetTitle("theta angle");
        hist_sh_2212_thetaangle->GetYaxis()->SetTitle("Count");
        hist_sh_2212_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_sh_2212_thetaangle->SetLineColor(kGreen + 3);
        hist_sh_2212_thetaangle->SetFillStyle(3004);
        // hist_sh_2212_thetaangle->SetMaximum(9000);
        hist_sh_2212_thetaangle->SetMinimum(1);
        hist_sh_2212_thetaangle->SetTitle("theta angle of Proton exiting shield");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_sh_2212_thetaangle->Draw();
    }

    // c2->cd(2);
    // if (hist_sh_22_thetaangle != nullptr)
    // {
    //     hist_sh_22_thetaangle->GetXaxis()->SetTitle("theta angle");
    //     hist_sh_22_thetaangle->GetYaxis()->SetTitle("Count");
    //     hist_sh_22_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
    //     hist_sh_22_thetaangle->SetLineColor(kGreen + 3);
    //     hist_sh_22_thetaangle->SetFillStyle(3004);
    //     // hist_sh_22_thetaangle_x->SetMaximum(400);
    //     // hist_sh_22_thetaangle_x->SetMinimum(1);
    //     hist_sh_22_thetaangle->SetTitle("theta angle of Gamma exiting shield");
    //     // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
    //     hist_sh_22_thetaangle->Draw();
    // }

    // c2->cd(3);
    // if (hist_sh_2112_thetaangle != nullptr)
    // {
    //     hist_sh_2112_thetaangle->GetXaxis()->SetTitle("theta angle");
    //     hist_sh_2112_thetaangle->GetYaxis()->SetTitle("Count");
    //     hist_sh_2112_thetaangle->SetFillColorAlpha(kGreen + 3, 0.9);
    //     hist_sh_2112_thetaangle->SetLineColor(kGreen + 3);
    //     hist_sh_2112_thetaangle->SetFillStyle(3004);
    //     // hist_sh_22_thetaangle_x->SetMaximum(400);
    //     hist_sh_2112_thetaangle->SetMinimum(1);
    //     hist_sh_2112_thetaangle->SetTitle("theta angle of Neutron exiting shield");
    //     // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
    //     hist_sh_2112_thetaangle->Draw();
    // }

    c2->cd(4);
    if (hist_sh_2212_phiangle != nullptr)
    {
        hist_sh_2212_phiangle->GetXaxis()->SetTitle("phi angle");
        hist_sh_2212_phiangle->GetYaxis()->SetTitle("Count");
        hist_sh_2212_phiangle->SetFillColorAlpha(kGreen + 3, 0.9);
        hist_sh_2212_phiangle->SetLineColor(kGreen + 3);
        hist_sh_2212_phiangle->SetFillStyle(3004);
        hist_sh_2212_phiangle->SetMinimum(1);
        hist_sh_2212_phiangle->SetTitle("phi angle of Proton exiting shield");
        // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
        hist_sh_2212_phiangle->Draw();
    }
    // c2->cd(5);
    // if (hist_sh_22_phiangle != nullptr)
    // {
    //     hist_sh_22_phiangle->GetXaxis()->SetTitle("phi angle");
    //     hist_sh_22_phiangle->GetYaxis()->SetTitle("Count");
    //     hist_sh_22_phiangle->SetFillColorAlpha(kGreen + 3, 0.9);
    //     hist_sh_22_phiangle->SetLineColor(kGreen + 3);
    //     hist_sh_22_phiangle->SetFillStyle(3004);
    //     hist_sh_22_phiangle->SetTitle("phi angle of Gamma exiting shield");
    //     // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
    //     hist_sh_22_phiangle->Draw();
    // }
    // c2->cd(6);
    // if (hist_sh_22_phiangle != nullptr)
    // {
    //     hist_sh_2112_phiangle->GetXaxis()->SetTitle("phi angle");
    //     hist_sh_2112_phiangle->GetYaxis()->SetTitle("Count");
    //     hist_sh_2112_phiangle->SetFillColorAlpha(kGreen + 3, 0.9);
    //     hist_sh_2112_phiangle->SetLineColor(kGreen + 3);
    //     hist_sh_2112_phiangle->SetFillStyle(3004);
    //     hist_sh_2112_phiangle->SetTitle("phi angle of Neutron exiting shield");
    //     // x_hist_DAQ_2212_KE->SetFillColorAlpha(4,0.1);
    //     hist_sh_2112_phiangle->Draw();
    // }
    // c2->cd(5)->SetLogy();

 

}