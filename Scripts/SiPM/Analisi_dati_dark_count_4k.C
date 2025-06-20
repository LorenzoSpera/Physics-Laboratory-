#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TF1.h"
#include <TDirectory.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "iostream"
#include <TLine.h>
#include <vector>
#include <limits>
#include <cmath>
#include <TMath.h>
#include <TMinuit.h>
#include "TLegend.h"
#include <fstream>

using namespace std;

void analisi_dati_sipm(TString fin, TString out) {

    
    ifstream file(fin);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    // Create a ROOT file and a TTree
    TFile* file_out = new TFile(out, "RECREATE");
    TTree* tree = new TTree("events", "Events Data");

    // Define branches
    Int_t eventi[4096]; 
    Double_t eventi_girati[4096];
    Double_t integrale, amp, bl;
    Double_t thr = 18/(2000./4096);				// 18 mV soglia trovata dalla correlazione carica ampiezza 
    bool b1 = false;
    bool b2 = false;
    bool b3 = false;
    bool b4 = false;
    Int_t count;
    tree->Branch("eventi", eventi, "eventi[4096]/I");
    tree->Branch("bl", &bl, "bl/D");
    tree->Branch("amp", &amp, "amp/D");
    tree->Branch("integrale", &integrale, "integrale/D");
    tree->Branch("eventi_girati", eventi_girati, "eventi_girati[4096]/D");
    tree->Branch("count",&count,"count/I");

    /*Double_t mean[4096],x[4096];
    for(int i=0;i<4096;i++){
      x[i]=i;
      mean[i]=0;
    }*/
    TF1* fit_func = new TF1("fitFunc", "[0]*exp(-x/[1])", 220, 1000);

   

    // Fill the tree

    Int_t ievts=0;
    while(file.good()){
        if(ievts%1000==0) cout<<"Processing event "<<ievts<<endl;
	//bl = 0; 
        integrale = 0;
	count = 0;
	amp = -100;
        for (int i = 0; i < 4096; ++i) {
            file>>eventi[i];
            if(i<100 & b1 == false){
		if (eventi[i]<thr)
			b1 = true; 	
		}
 	    if(i>100 & i < 200 & b2 == false){
		if (eventi[i]<thr)
			b2 = true; 	
		}
            if(i>900 & i < 1000 & b3 == false){
		if (eventi[i]<thr)
			b3 = true; 	
		}
	    if(i>800 & i < 900 & b4 == false){
		if (eventi[i]<thr)
			b4 = true; 	
		}
        }
	//cout << b1 << b2 << b3 << b4 << endl;
	bl = 0;
	if (b1 == false){
		for(int i = 0; i < 100; ++i)
			bl+=double(eventi[i])/100;
        }	
	if (b2 == false & bl == 0){
		for(int i = 100; i < 200; ++i)
			bl+=double(eventi[i])/100;
        }
        if (b3 == false & bl == 0){
		for(int i = 900; i < 1000; ++i)
			bl+=double(eventi[i])/100;
        }
        if (b4 == false & bl == 0){
		for(int i = 900; i < 1000; ++i)
			bl+=double(eventi[i])/100;
        }
	
	for(int i = 1; i < 4096; ++i){
	    //cout << bl << endl;
	    eventi_girati[i]=(-eventi[i] + bl)*(2000./4096);
	    if(bl-eventi[i]>thr & bl-eventi[i-1]<thr)
		count +=1;
	    //mean[i]+=eventi[i];
	    if(i > 250 & i < 400){
	      if (eventi_girati[i]>amp) amp=eventi_girati[i];
	      integrale+=double(eventi_girati[i])*4/50;
	    }
	//cout << count << endl;
	}
	b1 = false;
	b2 = false;
	b3 = false;
	b4 = false;
        ievts++;
 
    //amp= TMath::MaxElement(4096, eventi_girati);


        tree->Fill();
    }

    // Write the tree to the file
    tree->Write();

    /*for(int i=0;i<4096;i++){
      mean[i]=mean[i]/ievts;
    }

    TGraph* gMean=new TGraph(4096,x,mean);
    gMean->SetNameTitle("MeanSignal","MeanSignal");
    gMean->Write();*/
    // Close the file
    file_out->Close();

    return;
}
