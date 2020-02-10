#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/*read as binary, 8 bits make up a char*/
const int N = 256;
const int M = 2 * N;  // last one is for Select()

struct htNode {
	unsigned long long weight;
	int parent, lchild, rchild;

	htNode() : weight(0), parent(-1), lchild(-1), rchild(-1) {}
};

struct Buffer {
	int cnt;
	char bitsToCh;

	Buffer() : cnt(0), bitsToCh('\0') {}
};

class Huffman
{
public:
	Huffman();
	virtual ~Huffman();

	void toTarFile();
	void toSrcFile();

private:
	int leafNum_;
	unsigned long long srcNum_;

	vector<htNode> node{ vector<htNode>(M) };
	vector<int> leafWeight_{ vector<int>(N,0) };
	vector<int> leafToCodeNum_{ vector<int>(N,0) }; // leaf node's num --> leafCode's index 
	vector<char*> leafCode_{ vector<char*>(N,nullptr) };
	vector<int> idToCh_{ vector<int>(N,0) };
	
	FILE* fin;
	FILE* fout;

	Buffer buf;

	void write(int i);
	void write(int num, int i);
	void writeRemain();
	void read(int& num);
	void read(int& num, int i);

	/*encode functions*/
	void readAndCount();
	void select(int n, int& s1, int& s2);
	void buildAndCode();

	/*decode functions*/
	void readAndResol();
};
