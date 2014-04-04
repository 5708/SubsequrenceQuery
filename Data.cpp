#include "Data.h"

using namespace std;
void Data::read(string filename, int tsNum, int tsLen)
{
	ifstream file;
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
}