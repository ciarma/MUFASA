#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"


//This program reads a .dat of muons
//AFTER multiple scattering has been applied
//for ALL the targets. Decay probability is
//calculated using the birth target information
//and the lenght they traveled up to the end.
//a .dat muon file is generated.

void DECAYmuon(string nome_mu="ciao",int N_TGT=0,double l_tgt=0,double cell=5){

  ifstream in;
  ofstream out;
  string nome_out = "out_"+nome_mu;

  int partID,turn,turn0,alive,totali;
  double x, px, y, py, ct, dE_E, s, E, w, z, boh;
  double l_tot,gamma,beta,t,hit,prob;
  double m_mu = 0.1056583745; // GeV
  double e = 2.718218828;
  double c = 299792458; // m/s

  gRandom = new TRandom3(0);

  in.open(nome_mu);
  out.open(nome_out);
  alive=0;
  totali=0;
  while (1) {
    if(!in.good()) break;
    in >>partID>>turn>>x>>px>>y>>py>>ct>>dE_E>>s>>E>>w>>z>>turn0;
    if(turn==N_TGT){//ONLY the muons transported through ALL tgts
    totali=totali+1;
    l_tot=cell*(N_TGT-1-turn0)+l_tgt*(N_TGT-1-turn0)+l_tgt-z;
    gamma=E*(1+dE_E)/m_mu;
    beta=sqrt(1-1/pow(gamma,2));
    t=2.2e-6*gamma;// [s]
    //cout<<gamma<<" "<<t<<" "<<t*beta*c<<endl;

    prob = pow(e,-l_tot/(t*beta*c)); //survive probability
    hit = gRandom->Uniform(0,1);
    if(hit<prob){
      alive=alive+1;
      out<<partID<<" "<<turn<<" "<<x<<" "<<px<<" "<<y<<" "<<py<<" "<<ct<<" "<<dE_E<<" "<<s<<" "<<E<<" "<<w<<" "<<z<<" "<<turn0<<" "<<l_tot<<endl;
    }//fine if(hit<prob)
    }//fine if(turn==n_tgt)
    
  }
  cout<<"Alive muons "<<alive<<" out of "<<totali<<endl;
  in.close();
  out.close();


}//FINE
