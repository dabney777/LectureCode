// RandomNumCreater.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int randomNum(int MAX) {
	
	return ((double)rand()/RAND_MAX)*MAX;
}
int main()
{
	int max, number;
	ofstream out("C:\\Users\\Dabney\\Desktop\\DATA.txt");
	cout << "MAX=";
	cin >> max; cout << endl;
	cout << "number =" ;
	cin >> number;
	out << number<<endl;
	for (int i = 0; i < number; i++) {
		out<<randomNum(max)<<" ";
		if (i % 30 == 29)out << "\n";
	}
    return 0;
}

