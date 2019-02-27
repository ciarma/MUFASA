#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"


//This program reads a .dat of muons and
//returns a .dat of muons after they
//went through ONLY ONE TARGET.
//Multiple scattering is applied.

void MSmuon(string nome_mu="ciao",int n_tgt=0,double l_tgt=0,string tgt="be"){

  ifstream in;
  ofstream out;

  double sigma_theta,rnd1,rnd2;
  int debug=0;
  //Double_t l_tgt; //target len in m
  Double_t X0; //pdg[g cm^-2]
  Double_t rho; //pdg[g cm^-3]
  double A; //pdg
  double Z;
  Double_t X0_tgt;

  double berillio[] = {l_tgt,65.19,1.848,9.01218,4};
  double idrogeno[] = {l_tgt,63.04,0.071,1.008,1};
  double litio[] = {l_tgt,82.78,0.534,6.94,3};
  double carbonio[] = {l_tgt,42.70,2.267,12.0107,6};
  
  //string proprieta [] = {"l_tgt","X0","rho","A","Z"}; 
  if(tgt=="be"){
    l_tgt = berillio[0]; //target len in m
    X0 = berillio[1]; //pdg[g cm^-2]
    rho = berillio[2]; //pdg[g cm^-3]
    A = berillio[3]; //pdg
    Z = berillio[4];
    X0_tgt = X0/rho;
    if(debug>1)cout<<endl;
    if(debug>1)cout<<"Be"<<endl;
    if(debug>1)cout<<"l_tgt: "<<l_tgt<<" [m] ("<<l_tgt/(X0_tgt/100)*100<<"% di X0_tgt)"<<endl;
    if(debug>1)cout<<"X0_tgt: "<<X0_tgt/100<<" [m]"<<endl;
    if(debug>1)cout<<endl;
  }
  if(tgt=="h2"){
    l_tgt = idrogeno[0]; //target len in m
    X0 = idrogeno[1]; //pdg[g cm^-2]
    rho = idrogeno[2]; //pdg[g cm^-3]
    A = idrogeno[3]; //pdg
    Z = idrogeno[4];
    X0_tgt = X0/rho;
    if(debug>1)cout<<endl;
    if(debug>1)cout<<"H2"<<endl;
    if(debug>1)cout<<"l_tgt: "<<l_tgt<<" [m] ("<<l_tgt/(X0_tgt/100)*100<<"% di X0_tgt)"<<endl;
    if(debug>1)cout<<"X0_tgt: "<<X0_tgt/100<<" [m]"<<endl;
    if(debug>1)cout<<endl;
  }
  if(tgt=="li"){
    l_tgt = litio[0]; //target len in m
    X0 = litio[1]; //pdg[g cm^-2]
    rho = litio[2]; //pdg[g cm^-3]
    A = litio[3]; //pdg
    Z = litio[4];
    X0_tgt = X0/rho;
    if(debug>1)cout<<endl;
    if(debug>1)cout<<"Li"<<endl;
    if(debug>1)cout<<"l_tgt: "<<l_tgt<<" [m] ("<<l_tgt/(X0_tgt/100)*100<<"% di X0_tgt)"<<endl;
    if(debug>1)cout<<"X0_tgt: "<<X0_tgt/100<<" [m]"<<endl;
    if(debug>1)cout<<endl;
  }
  if(tgt=="c"){
    l_tgt = carbonio[0]; //target len in m
    X0 = carbonio[1]; //pdg[g cm^-2]
    rho = carbonio[2]; //pdg[g cm^-3]
    A = carbonio[3]; //pdg
    Z = carbonio[4];
    X0_tgt = X0/rho;
    if(debug>1)cout<<endl;
    if(debug>1)cout<<"C"<<endl;
    if(debug>1)cout<<"l_tgt: "<<l_tgt<<" [m] ("<<l_tgt/(X0_tgt/100)*100<<"% di X0_tgt)"<<endl;
    if(debug>1)cout<<"X0_tgt: "<<X0_tgt/100<<" [m]"<<endl;
    if(debug>1)cout<<endl;
  }

  gRandom = new TRandom3(0);


  //////////////////////////////////////////////////////////
  ////////////   BEGINNING OF THE CODE   ///////////////////
  //////////////////////////////////////////////////////////
  
  
  if(debug>1)cout<<"temporary muon TTree generation"<<endl;
  //only contains particle coming from the
  //target number 'n_tgt' (in input, parte da 0)
  
  TTree mu("mu","info sui muoni");
  int partID,turn,turn0;
  double x, px, y, py, ct, dE_E, s, E, w, z;
  mu.Branch("partID",&partID); //ID particella
  mu.Branch("turn",&turn); // 
  mu.Branch("x",&x); // m
  mu.Branch("px",&px); // px/p0
  mu.Branch("y",&y);
  mu.Branch("py",&py);
  mu.Branch("ct",&ct); // -ct? m
  mu.Branch("dE_E",&dE_E); //
  mu.Branch("s",&s);
  mu.Branch("E",&E); // GeV
  mu.Branch("w",&w);
  mu.Branch("z",&z); // m
  mu.Branch("turn0",&turn0);//turn of birth, remains unchanged
  
  in.open(nome_mu);
  while (1) {
    if(!in.good()) break;
    in >>partID>>turn>>x>>px>>y>>py>>ct>>dE_E>>s>>E>>w>>z>>turn0;
    if(turn==n_tgt)mu.Fill();     
  }
  in.close();

  int nentries = mu.GetEntries();
  cout<<"Muons coming from target number "<<n_tgt<<endl;
  cout<<"Number of muons: "<<nentries<<endl;
  cout<<endl;
  if(debug>1)cout<<"Start cycling through the muons"<<endl;

  out.open(nome_mu,ios::app);

  for(int i=0;i<nentries;i++){
    mu.GetEntry(i);

    //multiple scattering
    
    sigma_theta=0.0136/E*sqrt(l_tgt*100/X0_tgt)*0.9;
	 
    rnd1=gRandom->Gaus(0,1);
    rnd2=gRandom->Gaus(0,1);
    x = x + sigma_theta*l_tgt*(rnd1/sqrt(12)+rnd2/2);
    px = px + sigma_theta*rnd2;
    
    rnd1=gRandom->Gaus(0,1);
    rnd2=gRandom->Gaus(0,1);
    y = y + sigma_theta*l_tgt*(rnd1/sqrt(12)+rnd2/2);
    py = py + sigma_theta*rnd2;

    //writing the output

    turn=turn+1;
    out<<partID<<" "<<turn<<" "<<x<<" "<<px<<" "<<y<<" "<<py<<" "<<ct<<" "<<dE_E<<" "<<s<<" "<<E<<" "<<w<<" "<<z<<" "<<turn0<<endl;


  }//fine for entries
  out.close();

}//FINE
