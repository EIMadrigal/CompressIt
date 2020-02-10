#include "header.h"

int main()
{
	SSTable ST;
	int i = 0;
	char maliu[5000] = { '\0' };

	ST.elem = (ElemType*)malloc(70 * sizeof(ElemType));
	ST.length = 70;

	Huffmancoding(command(read()));

	fun(ST);
	Encoding(ST, maliu);
	for (i = 0; i < 5000; i++)
	{
		printf("%c", maliu[i]);
	}

	char jiema[5000] = { '\0' };
	char* point;
	point = jiema;

	codedecode(maliu, point);
	printf("\n");
	printf("%s", jiema);

	Decoding(ST, jiema);

	check();

	return 0;
}
