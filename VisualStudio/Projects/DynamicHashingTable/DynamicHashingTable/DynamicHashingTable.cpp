// DynamicHashingTable.cpp : Defines the entry point for the console application.
//ACM paper:Dynamic-Sized Nonblocking Hash Tables   Author:Yujie Liu

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
	int quantity() { return next; }
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
	int readByIndex(int idx) {
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
	int history = 4;
	Bucket **bucket;
	bool expand() {
		Bucket **old = bucket;
		bucket = new Bucket*[2 * current];
		for (int i = 0; i < current; i++) {
			bucket[i] = old[i];
			bucket[i + current] = old[i];
			bucket[i]->linkCount += 1;
		}
		history = current;
		current *= 2;
		return true;
	}

	bool shrink() {
		if (current == DEFAULT_SIZE)return false;
		for (int i =0 ; i < current/2+1; i++) {
				if ((bucket[i] != bucket[i + current / 2+1])
					&&(bucket[i]->quantity() + bucket[i + current / 2+1]->quantity() > 8)) return false;
		}
		for (int i = 0; i < current/2; i++) {
			if (bucket[i] != bucket[i + current / 2+1]) {
				for (int j = 0; j < bucket[i + current / 2+1]->quantity(); j++) {
					bucket[i]->add(bucket[i + current / 2 + 1]->readByIndex(j));
				}
					
				
			}else {
				bucket[i]->linkCount -= 1;
			}

		}
		history = current;
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
	void del(int x) {
		int tmp = hash(x);
		Bucket *b = bucket[tmp];
		bucket[tmp]->removeByValue(x);
		shrink();
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
				t[i++] = b->readByIndex(0);
				b->removeByIndex(0);
			}
			while (i > 0)
				insert(t[--i]);
		}
	}
};


	int main()
	{
		DynamicHashTable table;
		fstream out(".//DATA.txt");
		int n = 0, d = 0;
		out >> n;
		
		for (int i = 0; i < n; i++) {
			out >> d;
			table.insert(d);
		}
		out.close();
		fstream out1(".//DATA.txt");
		out1 >> n;

		for (int i = 0; i < n; i++) {
			out1 >> d;
			if (table.findValue(d)) {
				cout << d << " is existent and I have deleted it." << endl;
				table.del(d);
			}
			else {
				cout << d << " is not existent." << endl;
			}
		}

		/*while (true) {
			
			cin >> n; 
		if (table.findValue(n)) {
			cout << n << " is existent and I have deleted it." << endl;
			table.del(n);

		}
		else {
			cout << n << " is not existent." << endl;
		}
		}*/
		system("PAUSE");
		return 0;
	}