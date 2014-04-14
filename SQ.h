#ifndef _SQ_H_
#define _SQ_H_
#include <iostream>
#include "BPT.h"
#include <vector>
#include <algorithm>



using namespace std;


class SQ
{
	double epsilon;
	vector<int> singleMatch;
	vector<vector<int>> match;
	BPT *bpt;
	int queryLen, tsLen, tsNum;
	vector<int> result;

	void query(vector<double> querySequence, BPT *b, double epsilon);
	//Part 1
	//void initialBPT();
	
	//Part 2
	void similarityQuery(double v);
	void sequenceQuery(vector<double> querySequence);
	void matchCheck();
	int search(vector<int> d, int v);
	
	//Part 3
	vector<int> subsequencyMatch_B();
	vector<int> subsequencyMatch_S();
	
	//Part 40


};

#endif