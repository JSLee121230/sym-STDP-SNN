#include "file_read.h"
#include "../global.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
float str2float(string s)
{
    float num;
    stringstream ss(s);
    ss >> num;
    return num;
}
void read_gP2E_from_file(string path, float *tmp_gP2E)
{
    string str_gP2E;
    ifstream gP2E_file(path);
    if (gP2E_file)
    {
        cout << "Read from " << path << "..." << endl;
        for (int i = 0; i < NPoi; i++)
        {
            for (int j = 0; j < NExc; j++)
            {
                gP2E_file >> str_gP2E;
                tmp_gP2E[i * NExc + j] = str2float(str_gP2E);
            }
        }
        gP2E_file.close();
    }
    else
    {
        cout << "open " << path << " error!" << endl;
    }
}
void read_thetaPExc_from_file(string path, float *tmp_thetaPExc)
{
    string str_theta;
    ifstream theta_file(path);
    if (theta_file)
    {
        cout << "Read from " << path << "..." << endl;
        for (int i = 0; i < NExc; i++)
        {
            theta_file >> str_theta;
            tmp_thetaPExc[i] = str2float(str_theta);
        }
        theta_file.close();
    }
    else
    {
        cout << "open " << path << " error!" << endl;
    }
}
void read_gC2E_from_file(string path, float *tmp_gC2E)
{
    string str_gC2E;
    ifstream gC2E_file(path);
    if (gC2E_file)
    {
        cout << "Read from " << path << "..." << endl;
        for (int i = 0; i < NExc; i++)
        {
            for (int j = 0; j < NCla; j++)
            {
                gC2E_file >> str_gC2E;
                tmp_gC2E[i * NCla + j] = str2float(str_gC2E);
            }
        }
        gC2E_file.close();
    }
    else
    {
        cout << "open " << path << " error!" << endl;
    }
}