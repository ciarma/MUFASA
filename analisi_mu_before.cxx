#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"


//Questo programma legge un .dat di muoni
//e produce i grafici di debug.
//
//Il file di input deve essere inserito così
//root -l -x "analisi_mu_before.cxx(\"pos_Be00mm50.dat\")"

void analisi_mu_before(string nomefile="ciao"){

  int partID,turn;
  double x, px, y, py, ct, dE_E, s, E, w, z, turn0, l_tot;

  //definizione istogrammi

  TH1D *hxx = new TH1D("hxx","x",4000,-1e-3,1e-3);
  TH1D *hpx = new TH1D("hpx","px",4000,-2e-3,2e-3);
  TH1D *hyy = new TH1D("hyy","y",4000,-1e-3,1e-3);
  TH1D *hpy = new TH1D("hpy","py",4000,-2e-3,2e-3);
  TH1D *hct = new TH1D("hct","ct",4000,-0.015,0.015);
  TH1D *hdE = new TH1D("hdE","dE/E",500,-0.5,0.5);
  TH1D *hEE = new TH1D("hEE","Energia",400,10,30);
  TH1D *hAL = new TH1D("hAL","Alive",3000,0,2999);
  TH1D *hww = new TH1D("hww","weight",100,0,250);
  TH1D *hzz = new TH1D("hzz","z_prod",100,0,0.35);//max circa 10*l_tgt
  TH1D *ht0 = new TH1D("ht0","turn0",15,0,14);
  TH1D *hll = new TH1D("hll","l_tot",4000,0,79);

  TH2D *hpxx = new TH2D("hpxx","px:x",4000,-2e-3,2e-3,4000,-1e-3,1e-3);
  TH2D *hpyy = new TH2D("hpyy","py:y",4000,-2e-3,2e-3,4000,-1e-3,1e-3);
  TH2D *hpxdE = new TH2D("hpxdE","px:dE_E",80,-2e-3,2e-3,80,-0.25,0.25);

  //lettura file e fill istogrammi

  ifstream in;
  in.open(nomefile);
  cout<<"Apertura del file "<<nomefile<<endl;

  double mu_tot=0;
  while (1) {
    in >>partID>>turn>>x>>px>>y>>py>>ct>>dE_E>>s>>E>>w>>z>>turn0;
    hxx->Fill(x);
    hpx->Fill(px);
    hyy->Fill(y);
    hpy->Fill(py);
    hct->Fill(ct);
    hdE->Fill(dE_E);
    hEE->Fill(E*(1+dE_E));
    hAL->Fill(partID);
    hpxx->Fill(px,x);
    hpyy->Fill(py,y);
    hpxdE->Fill(px,dE_E);
    hww->Fill(w);
    hzz->Fill(z);
    ht0->Fill(turn0);

    mu_tot=mu_tot+w;
    
    if(!in.good()) break;
  }

  cout<<"sum w = "<<mu_tot<<endl;
  cout<<"eff = "<<mu_tot/3e11<<endl;

  //draw degli istogrammi
  /*
   TCanvas *Cxx = new TCanvas("x [m]");
   hxx->Draw();*/
   TCanvas *Cpx = new TCanvas("Px [rad]");
   hpx->Draw();
   /*TCanvas *Cyy = new TCanvas("y [m]");
   hyy->Draw();
   TCanvas *Cpy = new TCanvas("Py [rad]");
   hpy->Draw();
   TCanvas *Cct = new TCanvas("ct");
   hct->Draw();*/
   TCanvas *CdE = new TCanvas("dE_E [GeV]");
   hdE->Draw();
   TCanvas *CEE = new TCanvas("E [GeV]");
   hEE->Draw();
   TCanvas *Cww = new TCanvas("weight");
   hww->Draw();
   TCanvas *Czz = new TCanvas("z [m]");
   hzz->Draw();
   TCanvas *Ct0 = new TCanvas("turn0");
   ht0->Draw();
   TCanvas *Cpxx = new TCanvas("px:x");
   hpxx->GetXaxis()->SetTitle("p_x [rad]");
   hpxx->GetYaxis()->SetTitle("x [m]");
   hpxx->Draw();
   TCanvas *Cpyy = new TCanvas("py:y");
   hpyy->GetXaxis()->SetTitle("p_y [rad]");
   hpyy->GetYaxis()->SetTitle("y [m]");
   hpyy->Draw();
   TCanvas *CpxdE = new TCanvas("px:E");
   hpxdE->Draw("col");
   TCanvas *Ctot = new TCanvas();
   Ctot->Divide(3,2);
   Ctot->cd(1);
   hEE->Draw();
   Ctot->cd(4);
   hww->Draw();
   Ctot->cd(2);
   hpxx->Draw();
   Ctot->cd(5);
   hpyy->Draw();
   Ctot->cd(3);
   ht0->Draw();
   Ctot->cd(6);
   hzz->Draw();
   
}//FINE
