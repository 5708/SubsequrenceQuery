#ifndef _DATA_H_
#define _DATA_H_
#include <iostream>
#include <Eigen/Dense>
#include <fstream>

using namespace std;
class DATA{
public:
	MatrixXd m;
	
	void read(string filename, int tsNum, int tsLen);
	void write(vector<int> result);
	
};

#endif