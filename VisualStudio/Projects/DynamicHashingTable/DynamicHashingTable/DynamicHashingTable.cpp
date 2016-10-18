// DynamicHashingTable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Bucket {
private:
	int data[8];
	int next = 0;
public :
	int linkCount = 1;
	Bucket() {};
	bool isEmpty() { return next == 0; }
	bool add(int x) {
		if (next >= 8) return false;
		for (int i = 0; i < next; i++)if (data[i] == x)return true;
		data[next++] = x;
		return true;
	}
	bool removeByValue(int x) {
		int i;
		for (i = 0; i < next; i++) {
			if (data[i] == x) break;
		}
		if (i == next) { return false; 
		}else {
			data[i] = data[--next];
			return true;
		}
	}
	int getByIndex(int idx) {
		if (idx < next) {
			return data[idx];
		}
		return 0;
	}
	bool removeByIndex(int idx) {
		if (idx < next) {
			data[idx] = data[--next];
			return true;
		}
		return false;
	}
	

};
class DynamicHashTable {
private:
	int DEFAULT_SIZE = 4;
	int current = 4;
	Bucket **bucket;
	bool expand() {
		Bucket **old = bucket;
		bucket = new Bucket*[2 * current];
		for (int i = 0; i < current; i++) {
			bucket[i] = old[i];
			bucket[i + current] = old[i];
			bucket[i]->linkCount += 1;
		}
		current *= 2;
		return true;
	}

	bool shrink() {
		if (current == DEFAULT_SIZE)return false;
		for (int i = current / 2; i < current; i++) {
			if (bucket[i] != bucket[i + current])return false;
		}
		current /= 2;
		return true;
	}

	int hash(int x) { return (x / 8) % current; }



public:
	DynamicHashTable() {
		bucket = new Bucket*[DEFAULT_SIZE];
		for (int i = 0; i < DEFAULT_SIZE; i++)
			bucket[i] = new Bucket();
	}
	bool findValue(int x) {
		 int tmp =hash(x);
		 return (bucket[tmp]->removeByValue(x));
	}

	void insert(int x) {
		int tmp = hash(x);
		Bucket *b = bucket[tmp];
		if (b->add(x)) {}
		else {
			if (bucket[tmp]->linkCount == 1) {
				expand();
			}


			bucket[tmp]->linkCount -= 1;
			bucket[tmp] = new Bucket();
			insert(x);
			int t[8], i = 0;
			while (b->isEmpty()) {
				t[i++] = b->getByIndex(0);
				b->removeByIndex(0);
			}
			while (i > 0)
				insert(t[--i]);
		}
	}
};


	int main()
	{
		fstream out(".//DATA.txt");
		int n = 0, d = 0;
		out >> n;
		DynamicHashTable table;
		for (int i = 0; i < n; i++) {
			out >> d;
			table.insert(d);
		}
		while (true) { cin >> n; 
		if (table.findValue(n)) {
			cout << n << " is existent and I have deleted it." << endl;
		}
		else {
			cout << n << " is not existent." << endl;
		}
		}
		//system("PAUSE");
		return 0;
	}