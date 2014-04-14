#include "SQ.h"

/*
// Part 1

// Part 2
void SQ::similarityQuery(double v)
{
	double up, low;
	int resultSize, tseID, tstID;
	
	up = v + epsilon;
	low = v - epsilon;
	(*bpt).rangeQuery(low, up);
	singleMatch = (*bpt).rangeResult;
	sort(singleMatch.begin(), singleMatch.end());
}
void SQ::sequenceQuery(vector<double> qs)
{
	int qsSize;

	qsSize = qs.size();
	match.resize(0);
	for(int i = 0; i < qsSize; ++i)
	{
		similarityQuery(qs[i]);
		match.push_back(singleMatch);
	}
}

void SQ::matchCheck()
{
	vector<int> top, bot;
	int qsSize, eraseBoundBot, eraseBoundTop, topM, botM, botID, topID;
	
	
	for(int i = 0; i < qsSize; ++i)
	{
		top.push_back(match[i][0]);
		bot.push_back(match[i].back());
	}
	
	topM = top[0];
	topID = 0;
	botM = bot[0];
	botID = 0;
	for(int i = 1; i < qsSize; ++i)
	{
		if(topM > top[i])
		{
			topM = top[i];
			topID = i;
		}
		if(botM > bot[i])
		{
			botM = bot[i];
			botID = i;
		}
	}


	for(int i = 0; i < qsSize; ++i)
	{
		eraseBoundTop = search(match[i],topM - topID + i);
		match[i].erase(match[i].begin(),match[i].begin()+eraseBoundTop);

		eraseBoundBot = search(match[i], botM - botID + i + 1);
		match[i].erase(match[i].end() - match[i].size() + eraseBoundBot, match[i].end());
	}

	
}

int SQ::search(vector<int> d, int v)
{
	int s = d.size();

	for(int i = 0; i < s; ++i)
	{
		if(d[i] >= v)
		{
			return i;
		}
	}
	return s-1;

}
void SQ::query(vector<double> querySequence, BPT *b, double e)
{
	epsilon = e;
	bpt = b;
	sequenceQuery(querySequence);
	matchCheck();
	
}
// Part 3

// Part 4
*/