#include <iostream>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>

#include "include/Dataset.h"

using namespace std;

int Nminus1Plotter(unsigned int id){

  gROOT->Reset();
  gStyle->SetOptStat(0);

  cout << "Running N-1 Histo Producer for the '" << Dataset::toTString(id) << "' sample" << endl;
  cout << "Datatset is : " << Dataset::fullDatasetName(id) << "\n" << endl;

  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.03);
  
  TString rootstring = Dataset::fullDatasetName(id);
  TString dirname = ".";

  rootstring = dirname + "/" + rootstring;

  delete gROOT->GetListOfFiles()->FindObject(rootstring);
  
  TFile *rootfile = new TFile(rootstring);

  Float_t weight = 0.308;    // This could change

  TString histos = "InvMass,DeltaEtaJJ,DeltaPhiJJ,EtaDP,CJVEt,Jet1PT,Jet2PT,JetEta1,JetEta2,MET,Njets30";
  TObjArray* tokens = histos.Tokenize(",");
  Int_t n = tokens->GetEntries();

  TString styles = "hist, E, l, CONTZ";
  TObjArray* styletokens = styles.Tokenize(",");
  Int_t m = styletokens->GetEntries();
  
  TCanvas c1("c1","Draw histos",0, 0, 1000, 800);
  c1.Divide( 4, TMath::Nint(n/4 .));

  c1.cd();
  c1.SaveAs(Dataset::pdfTitler(id)+".pdf");

  for(Int_t i=0; i<n; i++)
{ 
  TString style = ((TObjString*) styletokens->At(0))->String();
  TString plot  = ((TObjString*) tokens->At(i))->String();

  TH1F *hi = (TH1F*)rootfile->Get(plot);

  cout << "plot " << plot << endl;

  c1.cd(i+1);
  hi->Draw(style);
  gPad->SetLogy();



}
  

  c1.cd();
  c1.SaveAs(Dataset::pdfTitler(id)+".pdf");

  return 0;

}
 
    
