#include "list.h"

int main()
{
	char read_file[] = "poemmm.txt";
	char write_file[] = "write.txt";
	char* buf = NULL;
	int last = 0, nlines = 0;
	if ((last = Read_Data(&buf, read_file)) == ERROR) return ERROR;
	nlines = Count_And_Adapt(buf, last);
	char** text = calloc(nlines, sizeof(char*));
	if (text == NULL) {printf("Can't create array.\n"); return ERROR;}
	Fill_Text(text, buf, last, nlines);
	Write_Data(text, write_file, nlines);
	Selsort(text, nlines, sizeof(char*), Compare_Strings);
	Write_Data(text, write_file, nlines);
	Reverse(text, nlines);
	Selsort(text, nlines, sizeof(char*), Compare_Strings);
	Reverse(text, nlines);
	Write_Data(text, write_file, nlines);
	printf ("Mission completed!\n%d lines and %d symbols were sorted!\n", nlines, last);
	My_Free(&buf, &text);
	return 0;
}
		
