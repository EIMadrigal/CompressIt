#include "huffman.h"

Huffman::Huffman() : leafNum_(0), srcNum_(0) {
	fin = nullptr;
	fout = nullptr;
}

/* write a char to the file per 8 bits */
void Huffman::write(int i) {
	buf.bitsToCh = (buf.bitsToCh << 1) + i;
	++buf.cnt;

	if (buf.cnt == 8) {
		fputc(buf.bitsToCh, fout);
		buf.cnt = 0;
		buf.bitsToCh = '\0';
	}
}

/* write i bits of num to file */
void Huffman::write(int num, int i) {		
	stack<int> s;
	for (int j = 0; j < i; ++j) {
		s.push(num & 1);
		num >>= 1;
	}

	for (int j = 0; j < i; ++j) {
		write(s.top());
		s.pop();
	}
}

void Huffman::writeRemain() {
	int curBuf = buf.cnt;
	if (curBuf > 0) {
		for (int i = 0; i < 8 - curBuf; ++i)
			write(0);
	}
}

/* read 1 bit from file, store in num */
void Huffman::read(int& num) {
	if (!buf.cnt) {
		buf.bitsToCh = fgetc(fin);
		buf.cnt = 8;
	}
	num = (buf.bitsToCh & 128) >> 7;
	--buf.cnt;
	buf.bitsToCh <<= 1;
}

/* read i bits from file, store in num */
void Huffman::read(int& num, int i) {
	num = 0;
	int oneBit;
	for (int j = 0; j < i; ++j) {
		read(oneBit);
		num = (num << 1) + oneBit;
	}
}

void Huffman::readAndCount() {
	string finName, foutName;
	cout << "Input the file name you want to compress: ";
	cin >> finName;

	errno_t errIn = fopen_s(&fin, finName.c_str(), "rb");
	if (fin == nullptr) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}

	cout << "Input the target file name: ";
	cin >> foutName;

	errno_t errOut = fopen_s(&fout, foutName.c_str(), "wb");
	if (fout == nullptr) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}

	rewind(fin);
	int c = fgetc(fin);  // int required to handle EOF in binary file
	if (c == EOF) {
		cout << "Empty File!" << endl;
		exit(1);
	}

	while (c != EOF) {
		++leafWeight_[c];
		++srcNum_;
		c = fgetc(fin);
	}

	leafNum_ = 0;
	for (int i = 0; i < N; ++i) {
		if (leafWeight_[i]) {
			node[leafNum_].weight = leafWeight_[i];
			leafToCodeNum_[i] = leafNum_;
			idToCh_[leafNum_] = i;
			++leafNum_;
		}
	}

	node[M - 1].weight = ULLONG_MAX;
}

/* select 2 min leaf node */
void Huffman::select(int n, int &s1, int &s2) {
	for (int i = 0; i < n; ++i) {
		if (node[i].parent == -1 && node[i].weight < node[s1].weight) {
			s1 = i;
		}
	}
	for (int j = 0; j < n; ++j) {
		if (node[j].parent == -1 && node[j].weight < node[s2].weight && j != s1) {
			s2 = j;
		}
	}
}

/* build tree and code */
void Huffman::buildAndCode() {
	int n = leafNum_;
	int m = 2 * n - 1;

	/*build huffman tree*/
	for (int j = n; j < m; ++j) {
		int cand1 = M - 1, cand2 = M - 1;
		select(j, cand1, cand2);
		node[cand1].parent = j;
		node[cand2].parent = j;
		node[j].lchild = cand1;
		node[j].rchild = cand2;
		node[j].weight = node[cand1].weight + node[cand2].weight;
	}

	/*code from leaf to root*/
	for (int i = 0; i < n; ++i) {
		vector<char> curCode;
		int iParent = node[i].parent;
		for (int j = i; iParent != -1; j = iParent, iParent = node[iParent].parent) {
			if (node[iParent].lchild == j)
				curCode.push_back('0');
			else
				curCode.push_back('1');
		}
		reverse(curCode.begin(), curCode.end());
		leafCode_[i] = new char[curCode.size() + 1];
		copy(curCode.begin(), curCode.end(), leafCode_[i]);
		leafCode_[i][curCode.size()] = '\0';
	}
}

void Huffman::toTarFile() {
	readAndCount();
	buildAndCode();

	rewind(fin);
	rewind(fout);

	buf.cnt = 0;
	buf.bitsToCh = '\0';

	fwrite(&srcNum_, sizeof(unsigned long long), 1, fout);
	write(leafNum_, 8);

	for (int i = 0; i < leafNum_; ++i)
		fwrite(&idToCh_[i], sizeof(char), 1, fout);

	int bitsNeed = 1;
	int totalNode = 2 * leafNum_ - 1;
	while (totalNode) {
		++bitsNeed;
		totalNode >>= 1;
	}

	for (int i = leafNum_; i < 2 * leafNum_ - 1; ++i) {
		write(node[i].lchild, bitsNeed);
		write(node[i].rchild, bitsNeed);
	}

	int c;
	while ((c = fgetc(fin)) != EOF) {
		int i = 0;
		while (leafCode_[leafToCodeNum_[c]][i] != '\0') {
			if (leafCode_[leafToCodeNum_[c]][i] == '1')
				write(1);
			else
				write(0);
			++i;
		}
	}

	writeRemain(); // an operation like flush

	fclose(fin);
	fclose(fout);
}

void Huffman::readAndResol() {
	string finName, foutName;
	cout << "Input the file name you want to decompress: ";
	cin >> finName;

	errno_t errIn = fopen_s(&fin, finName.c_str(), "rb");
	if (fin == nullptr) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}
	if (fgetc(fin) == EOF) {
		cout << "Empty file!" << endl;
		exit(1);
	}

	cout << "Input the target file name: ";
	cin >> foutName;

	errno_t errOut = fopen_s(&fout, foutName.c_str(), "wb");
	if (fout == nullptr) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}

	for (int i = 0; i < M; ++i)
		node[i].parent = node[i].lchild = node[i].rchild = -1;

	/* clean the buffer */
	buf.cnt = 0;
	buf.bitsToCh = '\0';

	if (fin) {
		rewind(fin);
		fread(&srcNum_, sizeof(unsigned long long), 1, fin);
	}

	read(leafNum_, 8);
	if (!leafNum_)
		leafNum_ = N;

	for (int i = 0; i < leafNum_; ++i)
		fread(&idToCh_[i], sizeof(char), 1, fin);

	int bitsNeed = 1;
	int totalNode = 2 * leafNum_ - 1;
	while (totalNode) {
		++bitsNeed;
		totalNode >>= 1;
	}

	/* restore huffman tree */
	for (int i = leafNum_; i < 2 * leafNum_ - 1; ++i) {
		read(node[i].lchild, bitsNeed);
		read(node[i].rchild, bitsNeed);
		node[node[i].lchild].parent = node[node[i].rchild].parent = i;
	}
}

void Huffman::toSrcFile() {
	readAndResol();
	rewind(fout);

	int getOne;
	read(getOne);
	for (int i = 0; i < srcNum_; ++i) {
		int j = 2 * leafNum_ - 2;

		/* get leaf code from root to leaf */
		while (getOne != EOF && (node[j].lchild != -1 || node[j].rchild != -1)) {
			if (getOne)
				j = node[j].rchild;
			else
				j = node[j].lchild;
			read(getOne);
		}
		fputc(idToCh_[j], fout);
	}

	fclose(fin);
	fclose(fout);
}

Huffman::~Huffman() {
	for (vector<char*>::iterator it = leafCode_.begin(); it != leafCode_.end(); ++it) {
		if (nullptr != *it) {
			delete* it;
			*it = nullptr;
		}
	}
}
