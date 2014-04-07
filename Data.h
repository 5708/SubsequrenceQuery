#ifndef _DATA_H_
#define _DATA_H_
#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <vector>
using Eigen::MatrixXd;
using namespace std;
class Data{
public:
	MatrixXd m;
	int tsNum, tsLen;
	
	void read(string filename, int tNum, int tLen);
	void write(vector<int>* result);
	
};

#endif