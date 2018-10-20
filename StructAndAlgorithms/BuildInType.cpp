#include <iostream>
#include <Windows.h>
#include "BuildInType.h"

using namespace std;

namespace StructAlgorithm
{
	void BuildInType::sizeofType()
	{
		cout<<"bool : "<<sizeof(bool)<<endl;
		cout<<"BOOL : "<<sizeof(BOOL)<<endl;

		cout<<"wchar_t £º"<<sizeof(wchar_t)<<endl;
		
		cout<<"unsigned : "<<sizeof(unsigned)<<endl;
		cout<<"long : "<<sizeof(long)<<endl;

		cout<<"jinzhi : "<<024<<"  "<<0x24<<endl;

		cout<<" L :"<<L'a'<<endl;

		cout<<"a multi-line"
			"string literal\
			using concatenation"
			<<endl;
	}
}