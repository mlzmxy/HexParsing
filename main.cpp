#include <iostream>
#include <vector>

#include "HexParsing.h"

using namespace std;

int main()
{
	HexParsing hp("D:\\WorkSpace\\TestHexParsing\\test.hex", 0x320000, 4 * 32 * 1024);
	if (hp.Convert())
	{
		cout << "转换成功！" << endl;
		vector<unsigned short int> result = hp.GetDataMap();
	}
	else
	{
		cout << hp.GetErrorMsg().c_str() << endl;
	}
	system("pause");
}