#include "Data.h"

using namespace std;
void Data::read(string filename, int tNum, int tLen)
{
	ifstream file;
	
	tsNum = tNum;
	tsLen = tLen;
	file.open(filename);
	m.resize(0,0);
	m.resize(tsNum, tsLen);
	for(int i = 0; i < tsNum; ++i)
	{
		for(int j = 0; j < tsLen; ++j)
		{
			file >> m(i,j);
		}
	}
	file.close();
}

void Data::write(vector<int>* result)
{
	ofstream file;
	int resultSize;
	
	file.open ("output.txt");
	resultSize = (*result).size();
	for(int i = 0; i < resultSize; ++i)
		file << (*result)[i]<<"\n";
	file.close();
}