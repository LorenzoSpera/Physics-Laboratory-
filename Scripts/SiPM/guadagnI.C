using namespace std;
#include <TGraph.h>


void grafica_rette(){

Double_t x[7] = {0.,1.,2.,3.,4.,5.,6.};
Double_t errors_x[7] = {0., 0., 0.,0.,0.,0.,0.};

Double_t y_53_61_int_3[7] = {0.113, 7.917, 15.54, 23.05, 30.57, 38.33, 45.56};
Double_t errors_53_61_int_3[7] = {1.673, 1.758, 1.727, 2.036, 2.277, 2.533, 2.607};

Double_t y_54_11_int_3[7] = {0.1658, 10.58, 20.77, 30.86, 40.98, 51.26, 61.09};
Double_t errors_54_11_int_3[7] = {1.809, 1.836, 1.957, 2.088, 2.194, 2.239, 2.481};

Double_t y_54_61_int_3[7] = {0.1783, 13.29, 26.18, 38.84, 51.72, 64.24, 76.41};
Double_t errors_54_61_int_3[7] = {1.71, 2.055, 2.255, 2.14, 2.552, 2.222, 3.422};

Double_t y_55_11_int_3[7] = {0.217, 16.23, 32.13, 47.84, 63.57, 79.19, 94.81};
Double_t errors_55_11_int_3[7] = {1.844, 1.954, 2.096, 2.167, 2.499, 3.028, 3.007};

Double_t y_55_61_int_3[7] = {0.2886, 18.72, 36.96, 55.31, 73.2, 90.93, 109};
Double_t errors_55_61_int_3[7] = {1.928, 2.166, 2.317, 2.64, 3.029, 3.902, 4.374};

Double_t y_56_11_int_3[7] = {0.2474, 21.07, 41.65, 62.01, 82.11, 102.5, 122.5};
Double_t errors_56_11_int_3[7] = {1.903, 2.179, 2.513, 2.572, 2.885, 3.418, 4.198};

Double_t y_56_61_int_3[7] = {0.3657, 23.18, 46.19, 78.68, 91.5, 113.7, 135.1};
Double_t errors_56_61_int_3[7] = {1.98, 2.072, 2.452, 2.718, 2.873, 3.835, 5.602};

Double_t guad[7] = {10.16, 12.74, 15.8, 18.24, 20.48};
//Double_t errors_guad[7]={}; DA TROVARE DAI FIT LINEARI
Double_t volt[7] = {53.61, 54.11, 54.61, 55.11, 55.61, 56.11, 56.61};
Double_t errors_volt[7] = {0.02, 0.02, 0.02,0.02,0.02, 0.02, 0.02}; //DA CAPIRE

//TGraphErrors * g1 =  new TGraphErrors(7, x,  y_53_61_int_3,  errors_x ,   errors_53_61_int_3  );
//g1 -> Draw();

//TGraphErrors * g2 =  new TGraphErrors(7, x,  y_54_11_int_3,  errors_x ,   errors_54_11_int_3  );
//g2 -> Draw();

//TGraphErrors * g3 =  new TGraphErrors(7, x,  y_54_61_int_3,  errors_x ,   errors_54_61_int_3  );
//g3 -> Draw();

//TGraphErrors * g4 =  new TGraphErrors(7, x,  y_55_11_int_3,  errors_x ,   errors_55_11_int_3  );
//g4 -> Draw();

//TGraphErrors * g5 =  new TGraphErrors(7, x,  y_55_61_int_3,  errors_x ,   errors_55_61_int_3  );
//g5 -> Draw();

//TGraphErrors * g6 =  new TGraphErrors(7, x,  y_56_11_int_3,  errors_x ,   errors_56_11_int_3  );
//g6 -> Draw();

//TGraphErrors * g7 =  new TGraphErrors(7, x,  y_56_61_int_3,  errors_x ,   errors_56_61_int_3  );
//g7 -> Draw();

//TGraphErrors * g_guadagni =  new TGraphErrors(7, volt, guad,  errors,   errors  );
//g_guadagni -> Draw();


Double_t freq[7] = {0.26, 14.0, 64.6, 81.5, 87.1, 106.5, 119.73};
Double_t freq_err[7] = {0.02, 0.1, 0.2, 0.3, 0.3, 0.4, 0.02};


TGraphErrors * g =  new TGraphErrors(7, volt,  freq,  errors_volt ,   freq_err);
g -> Draw();

}