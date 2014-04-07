#ifndef _SQ_H_
#define _SQ_H_
#include <iostream>
#include <vector>
#include "Pixel.h"
#include "BPT.h"
#include "EmptyIndex.h"
using namespace std;

class SQ
{
public:
	vector<Pixel> pixels;
	double epsilon;
	vector<vector<int>> singleMatch;
	vector<vector<vector<int>>> match;
	BPT *bpt;
	int queryLen, tsLen, tsNum;
	vector<EmptyIndex> matchEI;

	//Part 1
	void initialBPT();
	
	//Part 2
	void similarityQuery(double v);
	void sequenceQuery(vector<double> querySequence, BPT *b);
	void matchCheck();
	void clearMatchTS();
	
	//Part 3
	vector<matchIndex> subsequencyMatch();
	
	//Part 40


};

#endif