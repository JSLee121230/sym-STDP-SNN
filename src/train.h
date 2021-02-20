#ifndef _TRAIN_H_
#define _TRAIN_H_

#include "gnuplot.h"
#include "model.h"
#include "../global.h"
#include <stddef.h> 
#include <vector>
using namespace std;

#define N_rand 256

#define preN_EI NExc
#define postN_EI NInh
#define preN_IE NInh
#define postN_IE NExc
#define preN_CE NCla
#define postN_CE NExc
#define connN_E2I NExc 
#define connN_I2E NInh *(NExc - 1) 

#define INPUT_INTENSITY_INIT 2
#define Cla_INPUT_INTENSITY_INIT 0.2 //khz

#define LastTrain 0
#define NowTrain 1
#define NowTest 2
#define FinalTest 0

extern long int imageNum;
// ------------------------------------------------------------------------------
//  visualization
// ------------------------------------------------------------------------------
vector<vector<float>> PEVisual(WIDTH *NExc_Sqrt, vector<float>(HEIGHT *NExc_Sqrt));
vector<vector<float>> ECVisual(ECw_X, vector<float>(ECw_Y));
vector<vector<float>> ECVisual_inferred(ECw_X, vector<float>(ECw_Y));
vector<vector<float>> CEVisual(ECw_Y, vector<float>(ECw_X));
vector<vector<float>> CEVisual_inferred(ECw_Y, vector<float>(ECw_X));

int str2int(string s);
void convertRateToRandomNumberThreshold(vector<float> rateKHz_pattern, uint64_t *pattern, int Num);
void get_rand_g(float *p, long int n, int g_max);
void get_rand(uint64_t *p, long int n, int max);
void get_inputdata(string datapath, vector<vector<float>> &images, vector<float> &labels, vector<vector<float>> &images_test, vector<float> &labels_test);
void rewrite_gEI_gIE();
void rewrite_gCE();
void reset_Cla_para();
void feed_to_networks(vector<float> image, vector<float> &FR_khz, float input_intensity);
void Cla_feed_to_networks(int label, vector<float> &cla_FR_khz, float cla_input_intensity);
void reset_ratesPPoi(vector<float> &FR_khz);
void reset_ratesPCla(vector<float> &cla_FR_khz);
#endif