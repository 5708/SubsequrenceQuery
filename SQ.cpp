#include "SQ.h"
using namespace std;
// Part 1

// Part 2
void SQ::similarityQuery(double v)
{
	double up, low;
	int resultSize, tseID, tstID;
	
	up = v + epsilon;
	low = v - epsilon;
	(*bpt).rangeQuery(low, up);
	singleMatch.resize(0);
	singleMatch.resize(tsNum);
	resultSize = bpt.rangeResult.size();
	for(int i = 0; i < (*bpt).rangeResult.size(); ++i)
	{
		tseID = (*bpt).rangeResult[i] / 100;
		tstID = (*bpt).rangeResult[i] - 100*tseID;
		singleMatch[tseID].push_back(tseID);
	}
}
void SQ::sequenceQuery(vector<double> querySequence, BPT* b)
{
	int qsSize;

	bpt = b;
	qsSize = querySequence.size();
	for(int i = 0; i < qsSize; ++i)
	{
		similarityQuery(querySequence(i));
		match.puh_back(singleMatch);
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
						if(match[i][j].front() < i + 1)
						{
							match[i][j].erase(match.begin());
							popped = true;
						}
						else if(((i - 1) >= 0) && (match[i][j].front() < match[i-1][j].front()))
						{
							match[i][j].erase(match.begin());
							popped = true;
						}
						else if(match[i][j].back() > (tsLen - queryLen + i + 1))
						{
							match[i][j].pop_back();
							popped = true;
						}
						else if(((i+1) < queryLen) && (match[i+1][j].size() != 0))
						{
							if(match[i][j].back() > match[i+1][j].back())
							{
								match[i][j].pop_back();
								popped = true;
							}
						}
						else if((i+1) != queryLen)
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
	matchEI[tsid] = true;
}
// Part 3

// Part 4
