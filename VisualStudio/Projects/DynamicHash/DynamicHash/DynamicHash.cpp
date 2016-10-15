// DynamicHash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
class 

int main()
{


	istringstream istr;
	system("md .\\testtt");
	istr.str(".\\a\\b.txt");
	ofstream out;
	
	out.open(istr.str(),ofstream::out);
	
	cout << out.is_open() << endl;
	for (int i = 0; i < 100; i++) {
		out << i << "";
	}
	
	
	system("PAUSE");
    return 0;
}

