#ifndef _BPT_H_
#define _BPT_H_
#include <iostream>
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;
class BPT
{
public:
	vector<int> rangeResult;
	
	void BPTbuild(MatrixXd *m);
	void rangeQuery(double low, up);

}

#endif
