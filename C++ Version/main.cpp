#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include "huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
	Huffman h;
	
	h.toTarFile();
	h.toSrcFile();

	return 0;
}
