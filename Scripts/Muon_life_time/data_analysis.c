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

void analisi_dati_mu3(TString fin1, TString fin2, TString fin3, TString out) {
    
    ifstream file1(fin1);
    ifstream file2(fin2);
    ifstream file3(fin3);

    if (!file1.is_open() || !file2.is_open() || !file3.is_open()) {
        cerr << "Error opening files." << endl;
        return;
    }


    Double_t thr=400/(2000./4096);
    
    // Create a ROOT file and a TTree
    TFile* file = new TFile(out, "RECREATE");
    TTree* tree = new TTree("events", "Events Data");

    // Define branches
    Int_t start[8192], stop1[8192], stop2[8192];
    Double_t blStart, blStop1, blStop2;
    Int_t startTime,stop1Time,stop2Time;
    tree->Branch("start", start, "start[8192]/I");
    tree->Branch("stop1", stop1, "stop1[8192]/I");
    tree->Branch("stop2", stop2, "stop2[8192]/I");
    tree->Branch("startTime", &startTime, "startTime/I");
    tree->Branch("stop1Time", &stop1Time, "stop1Time/I");
    tree->Branch("stop2Time", &stop2Time, "stop2Time/I");
    tree->Branch("blStart", &blStart, "blStart/D");
    tree->Branch("blStop1", &blStop1, "blStop1/D");
    tree->Branch("blStop2", &blStop2, "blStop2/D");


    // Fill the tree
    Int_t ievts=0;
    while(file1.good() && file2.good() && file3.good()){
        if(ievts%1000==0) cout<<"Processing event "<<ievts<<endl;
        blStart=0;
        blStop1=0;
        blStop2=0;
        bool findStart=false;
        bool findStop1=false;
        bool findStop2=false;
        startTime=-99;
        stop1Time=-99;
        stop2Time=-99;
        for (int i = 0; i < 8192; ++i) {
            file1>>start[i];
            file2>>stop1[i];
            file3>>stop2[i];
            if(i<100){
                blStart+=double(start[i])/100;
                blStop1+=double(stop1[i])/100;
                blStop2+=double(stop2[i])/100;
            }
            else if (i<7100 && (blStart-start[i])>thr && !findStart){
                startTime=i;
                findStart=true;
            }
            else if (i>7050 && i<7150 && (blStop1-stop1[i])>thr && !findStop1){
                stop1Time=i;
                findStop1=true;
            }
            else if (i>7050 && i<7150 && (blStop2-stop2[i])>thr && !findStop2){
                stop2Time=i;
                findStop2=true;
            }
        }
        ievts++;
        tree->Fill();
    }

    // Write the tree to the file
    tree->Write();
    // Close the file
    file->Close();

    return;
}

