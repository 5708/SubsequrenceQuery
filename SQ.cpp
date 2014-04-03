#include <iostream>
#include "SQ.h"

// Part 1

// Part 2
void SQ::similarityQuery(double v)
{
	double up, low;
	int resultSize;
	
	up = v + epsilon;
	low = v - epsilon;
	bpt.rangeQuery(low, up);
	resultSize = bpt.rangeResult.size();
	for(int i = 0; i < bpt.rangeResult.size(); ++i)
	{
		sort((*bpt).rangeResult.begin(), (*bpt).rangeResult.end());
	}

}
void SQ::sequenceQuery(vector<double> querySequence, BPT* b)
{
	int qsSize;

	bpt = b;
	qsSize = match.size();
	for(int i = 0; i < qsSize; ++i)
	{
		similarityQuery(querySequence(i));
		match.puh_back((*bpt).rangeResult);
	}
}

void SQ::matchCheck()
{
	bool popped = true;
	
	matchEI.resize(0);
	matchEI.resize(tsNum);
	for(int i = 0; i < queryLen; ++i)
	{
		for(int j = 0; j < tsNum; ++j)
		{	
			if(matchEI[j].isempty == false)
			{
				while(popped)
				{
					popped = false;
					if(match[i][j].size() != 0)
					{
						if(match[i][j].back() > (tsLen - queryLen + i))
						{
							match[i][j].pop_back();
							popped = true;
						}
						else if(match[i+1][j].size() != 0)
						{
							if(match[i][j].back() > match[i+1][j].back())
							{
								match[i][j].pop_back();
								popped = true;
							}
						}
						else
						{
							clearMatchTS(j);
						}
					}
					else
					{
						clearMatchTS(j);
					}
				}
			}
		}
	
	}
	
}

void SQ::clearMatchTS(int tsid)
{
	for(int i = 0; i < queryLen; ++i)
	{
		match[i][tsid].clear();
	}
}
// Part 3

// Part 4
