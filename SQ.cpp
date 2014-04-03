#include <iostream>
#include "SQ.h"

// Part 1

// Part 2
void SQ::similarityQuery(double v)
{
	double up, low;
	up = v + epsilon;
	low = v - epsilon;
	bpt.rangeQuery(low, up);

}
void SQ::sequenceQuery(vector<double> querySequence)
{
	int qsSize;

	qsSize = match.size();
	for(int i = 0; i < qsSize; ++i)
	{
		similarityQuery(querySequence(i));
		match.puh_back(bpt.rangeResult);
	}
}

// Part 3

// Part 4
