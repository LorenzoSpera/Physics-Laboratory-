#import <TGraph.h>
#include <TCanvas.h>
using namespace std;

void grafica_guadagno(){
    // Double_t x_54_61[10] = {13.37, 25.49, 38.38, 50.46, 62.72, 75.15, 87.23, 99.6, 111.7, 123.6};
    // Double_t y_54_61[10] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
    // Double_t errors_54_61[10] = {2.905, 3.031, 3.362, 2.928, 3.532, 3.794, 3.859, 3.865, 4.923, 5.088};

    // TGraphErrors *g = new TGraphErrors(x_54_61, errors_54_61, y_54_61, errors_54_61);
    // g -> Draw();
    Double_t x_54_61[10] = {13.37, 25.49, 38.38, 50.46, 62.72, 75.15, 87.23, 99.6, 111.7, 123.6};
    Double_t y_54_61[10] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
    Double_t ex[10] = {0};  // errori nulli sull'asse x
    Double_t errors_54_61[10] = {2.905, 3.031, 3.362, 2.928, 3.532, 3.794, 3.859, 3.865, 4.923, 5.088};

    TCanvas *c = new TCanvas("c", "Grafico Guadagno", 800, 600);
    TGraphErrors *g = new TGraphErrors(10, y_54_61, x_54_61, ex, errors_54_61);
    //g->SetTitle("Guadagno;Tensione (V);Guadagno");
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);
    g->Draw("AP");
}