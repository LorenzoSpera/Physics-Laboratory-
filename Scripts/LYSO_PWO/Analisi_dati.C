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

void analisi_dati_scintillatore_inorganico(TString fin, TString out) {

    
    ifstream file(fin);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    // Create a ROOT file and a TTree
    TFile* file_out = new TFile(out, "RECREATE");
    TTree* tree = new TTree("events", "Events Data");

    // Define branches
    Int_t eventi[1024]; 
    Double_t eventi_girati[1024];
    Double_t bl, integrale, amp;
    tree->Branch("eventi", eventi, "eventi[1024]/I");
    tree->Branch("bl", &bl, "bl/D");
    tree->Branch("amp", &amp, "amp/D");
    tree->Branch("integrale", &integrale, "integrale/D");
    tree->Branch("eventi_girati", eventi_girati, "eventi_girati[1024]/D");

    TF1* fit_func = new TF1("fitFunc", "[0]*exp(-x/[1])", 220, 1000);

    //Double_t thr=400/(2000./4096);

    // Fill the tree

    Int_t ievts=0;
    while(file.good()){
        if(ievts%1000==0) cout<<"Processing event "<<ievts<<endl;
        bl=0;
        integrale = 0;
	amp = -100;
        for (int i = 0; i < 1024; ++i) {
            file>>eventi[i];
            if(i<100){
                bl+=double(eventi[i])/100;
            }
        }
        ievts++;
        for (int i = 0; i < 1024; ++i) {
            
            eventi_girati[i]=(-eventi[i] + bl)*(2000./4096); 
	    integrale+=double(eventi_girati[i])*4/50;
        }

	amp= TMath::MaxElement(1024, eventi_girati);


        tree->Fill();
    }

    // Write the tree to the file
    tree->Write();

    // Close the file
    file_out->Close();

    return;
}
