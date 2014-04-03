#include <iostream>
#include <vector>
#include "Pixel.h"
#include "BPT.h"

using namespace std;

class SQ
{
public:
	vector<Pixel> pixels;
	double epsilon;
	vector<vector<vector<int>>> match;
	BPT bpt;

	//Part 1
	void initialBPT();
	//Part 2
	vector<vector<int>>(double v);
	void sequenceQuery(vector<double> querySequence);
	//Part 3
	vector<matchIndex> subsequencyMatch();
	//Part 40


};
