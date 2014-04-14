#ifndef _BPT_H_
#define _BPT_H_
#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace std;
using Eigen::MatrixXd;

class BPT
{
public:
	vector<int> rangeResult;
	
	void BPTbuild(MatrixXd *m);
	void rangeQuery(double low, double up);

};
#endif
