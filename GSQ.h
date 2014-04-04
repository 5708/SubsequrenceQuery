#ifndef _GSQ_H_
#define _GSQ_H_
#include <iostream>

using namespace std;
class GSQ{
public:
	vector<BPT> forest; // The result of globalScan
	vector<int> matchResult; // The result of globalQuery
	void globalScan(string filename);
	void globalQuery(double lat, double lon, double D, vector<double> qs);
	
};

#endif