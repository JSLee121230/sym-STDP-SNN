#ifndef _FILE_READ_H_
#define _FILE_READ_H_

#include <iostream>
using namespace std;
float str2float(string s);
void read_gP2E_from_file(string path, float *tmp_gP2E);
void read_thetaPExc_from_file(string path, float *tmp_thetaPExc);
void read_gC2E_from_file(string path, float *tmp_gC2E);

#endif