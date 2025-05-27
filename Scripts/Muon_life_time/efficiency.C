// root
// .L efficienza_B.C
// Analisi_dati()

#include <iostream>
#include <vector>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TMath.h>

// No more std
using namespace std;

vector<double> func_bi(const double a[], const double b[], int size) {
    vector<double> e(size);
    for (int i = 0; i < size; i++) {
        if (b[i] != 0) { 
            e[i] = a[i] / b[i];
        }
    }
    return e;
}

vector<double> func_deA(const double a[], const double b[], int size) {
    vector<double> e(size);
    for (int i = 0; i < size; i++) {
        if (b[i] != 0) { 
            e[i] = (a[i]+1) / (b[i]+2);
        }
    }
    return e;
}

void Analisi_dati() {
    double V_A = 1799;
    double V_C = 1803;

    //t=2min

    vector<double> N_ABC = {1, 5, 3, 10, 25, 28, 101, 147, 222, 229, 239, 255, 236, 237, 253, 235, 234, 246, 244, 249, 227, 246, 237, 239, 234};
    vector<double> N_AC = {297, 314, 298, 314, 292, 283, 314, 276, 328, 294, 291, 314, 306, 305, 301, 300, 300, 301, 291, 307, 269, 302, 295, 283, 277};
    vector<double> V_B = {1298, 1325, 1350, 1399, 1425, 1455, 1502, 1525, 1555, 1601, 1623, 1649, 1701, 1725, 1755, 1803, 1825, 1852, 1899, 1928, 1949, 1999, 2022, 2054, 2101};

    int size = N_ABC.size(); 

    vector<double> efficiency = func_bi(N_ABC.data(), N_AC.data(), size);

    vector<double> errors_bi(size);
    for (int i = 0; i < size; i++) {
        errors_bi[i] = sqrt(efficiency[i] * (1 - efficiency[i]) / N_AC[i]);
    }

    //Efficienza ed errori de Agostini

    vector<double> efficiency_deA = func_deA(N_ABC.data(), N_AC.data(), size);
    vector<double>errors_deA(size);
    for (int i = 0; i < size; i++) {
        errors_deA[i] = sqrt(efficiency_deA[i] * (1 - efficiency_deA[i]) / (N_AC[i]+3));
    }

    double errorV = 6.5;
    vector<double> errors_V(V_B.size(), errorV);


    TCanvas* canvas = new TCanvas("c1", "Efficienza vs V_B (binomial)", 800, 600);
    TGraphErrors* graph = new TGraphErrors(size, V_B.data(), efficiency.data(), errors_V.data(), errors_bi.data());

    graph->SetTitle("Efficienza vs V_B (binomial);Voltaggio B1 [V];Efficienza");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kBlue);
    graph->Draw();

    graph->GetXaxis()->SetTitleSize(0.04);
    graph->GetYaxis()->SetTitleSize(0.04);

    //Istogrammi

    TH1D* h_NAC = new TH1D("A_AND_C",";; Eventi", 200, 0, 400);
    TH1D* h_NABC = new TH1D("A_AND_C_AND_B",";; Eventi", 200, 0, 400);

    for (int i = 0; i < size; i++) {
        h_NAC->Fill(N_AC[i]);
        h_NABC->Fill(N_ABC[i]);
    }
    TCanvas* c2 = new TCanvas("c2", "Istogramma A AND C", 800, 600);
    h_NAC->Draw();

    TCanvas* c3 = new TCanvas("c3", "Istogramma (A AND C) AND B", 800, 600);
    h_NABC->Draw();

    //Efficienza

    TH1D* h_eff = new TH1D("Efficenza", "Efficienza;Efficienza;Eventi", 200, 0, 1);

    for (int i = 0; i < size; i++) {
        if (N_AC[i] != 0) { 
            double eff = N_ABC[i] / N_AC[i];
            h_eff->Fill(eff); 
        }
    }

    TCanvas* c4 = new TCanvas("c4", "Istogramma Efficienze", 800, 600);
    h_eff->Draw();

    //Fit

    TF1 *FitFunction = new TF1("FitFunction", "0.5*[0]*(1+TMath::Erf((x-[1])/sqrt(2)/[2]))", 0, 1);
    FitFunction->SetParameters(8.15451e-01, 1.50878e+03 , 5.58678e+01); //valori trovati dopo aver disegnato il grafico: "Tools"->"Fit Panel"->"Type: User Func"->"Fit" 

    //Valor medio: 1.50878e+03
    //Sigma: 5.58678e+01
    //Voglio stare in un regime statico dove, anche se il voltaggio oscilla l'efficienza è stabile. Quindi mi sposto dal valor medio (dove bastano piccole oscillazioni dl voltaggio per far variare di tanto l'efficienza) di qualche Sigma.

    graph->Fit("FitFunction","R");
    TCanvas* c5 = new TCanvas("c5", "Fit efficienze", 800, 600);
    graph->Draw("AP");
    FitFunction->Draw("same");


    // de Agostini

    TCanvas* c_deA = new TCanvas("c_deA", "deAgostini", 800, 600);
    TGraphErrors* graph_deA = new TGraphErrors(size, V_B.data(), efficiency_deA.data(), errors_V.data(), errors_deA.data());

    graph_deA->SetTitle("deAgostini Efficienza vs V_B;Voltaggio B1 [V];Efficienza (#epsilon_{B})");
    graph_deA->SetMarkerStyle(20);
    graph_deA->SetMarkerSize(1);
    graph_deA->SetMarkerColor(kBlue);
    graph_deA->Draw();

    graph_deA->GetXaxis()->SetTitleSize(0.04);
    graph_deA->GetYaxis()->SetTitleSize(0.04);

    graph_deA->Fit("FitFunction","R");
    TCanvas* c6 = new TCanvas("c6", "Fit efficienze de Agostini", 800, 600);
    graph_deA->Draw("AP");
    FitFunction->Draw("same");

}