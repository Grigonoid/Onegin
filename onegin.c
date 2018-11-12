#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const int ERROR = -1;
const int alph_size = 65;
int Read_Data (char** buf_ptr, char read_file[]);
int Calculate_Size (FILE* read);
int Count_And_Adapt (char* buf, int last);
void Fill_Text (char** text, char* buf, int last, int nlines);
int Custom_Encoding (char c);
int Compare_Strings (const void* ptr1, const void* ptr2);
int Write_Data (char** text, char write_file[], int nlines);
void My_Free (char** buf, char*** text);
void Reverse (char** text, int nlines);
void Swap (char *v1, char *v2);

//-------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	char read_file[] = "poemmm.txt";
	char write_file[] = "write.txt";
	char* buf = NULL;
	int last = 0, nlines = 0;
	if ((last = Read_Data(&buf, read_file)) == ERROR) return ERROR;
	nlines = Count_And_Adapt(buf, last);
	printf("%d\n", last);
	printf("%d\n", nlines);
	char** text = calloc(nlines, sizeof(char*));
	if (text == NULL) {printf("Can't create array.\n"); return ERROR;}
	Fill_Text(text, buf, last, nlines);
	Write_Data(text, write_file, nlines);
	qsort(text, nlines, sizeof(char*), Compare_Strings);
	Write_Data(text, write_file, nlines);
	Reverse(text, nlines);
	qsort(text, nlines, sizeof(char*), Compare_Strings);
	Reverse(text, nlines);
	Write_Data(text, write_file, nlines);
	printf ("Mission completed!\n%d lines were sorted!\n", nlines);
	My_Free(&buf, &text);
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int Calculate_Size (FILE* read)
{
	fseek (read, 0, SEEK_END);
	int size = ftell(read);
	fseek (read, 0, SEEK_SET);
	return size;
}
	
//-------------------------------------------------------------------------------------------------------------------------------------

int Read_Data (char** buf_ptr, char read_file[])
{
	FILE* read = fopen(read_file, "r");
	if (!read) {printf("Cannot open %s.\n", read_file); return ERROR;}
	int size = Calculate_Size(read);
	*buf_ptr = calloc(size+1, sizeof(char));
	if (*buf_ptr == NULL) {printf("Can't create array.\n"); return ERROR;}
	int last = fread (*buf_ptr, sizeof(char), size, read);
	*buf_ptr = realloc(*buf_ptr, (last+1)*sizeof(char));
	if (*buf_ptr == NULL) {printf("Can't create array.\n"); return ERROR;}
	(*buf_ptr)[last] = '\n';
	fclose(read);
	return last;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int Count_And_Adapt (char* buf, int last)
{
	int nlines = 0;
	for (int i = 0; i <= last; ++i) {
		if (buf[i] == '\n') {
			++nlines;
			buf[i] = '\0';
			while (buf[i+1] <= last && buf[i+1] == '\n')
				++i;
		}
	}
	return nlines;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void Fill_Text (char** text, char* buf, int last, int nlines)
{
	text[0] = &buf[0];
	int count = 1;
	for (int i = 0; i < last; ++i) { 
		if (buf[i] == '\0') {
			while (buf[i+1] <= last && buf[i+1] == '\n')
				++i;
			text[count] = &buf[i+1];
			++count;
			if (count == nlines) break;
		}
	}
}
	
//-------------------------------------------------------------------------------------------------------------------------------------

int Custom_Encoding (char c)
{
	char alph[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	for (int i = 0; i <= alph_size; ++i)
		if (c == alph[i])
			return i+1;
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int Compare_Strings (const void* ptr1, const void* ptr2)
{
	char* str1 = *((char**) ptr1);
	char* str2 = *((char**) ptr2);
	while ((*str1) != '\0' && (*str2) != '\0') 
	{
		while (Custom_Encoding(*str1) == 0) *str1++;
		while (Custom_Encoding(*str2) == 0) *str2++;
		if (Custom_Encoding(*str1) != Custom_Encoding(*str2))
			return Custom_Encoding(*str1) - Custom_Encoding(*str2);
		*str1++;
		*str2++;
	}
	return ((*str1) == '\0') ? -1 : 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int Write_Data (char** text, char write_file[], int nlines) 
{
	FILE* write = fopen(write_file, "a+");
	if (!write) {printf("Cannot open %s.\n", write_file); return ERROR;}
	for (int i = 0; i < nlines; ++i)
		fprintf (write, "%s\n", text[i]);
	fprintf (write, "\n\n**********************************************\n**********************************************\n\n");
	fseek(write, 0, SEEK_SET);
	fclose(write);
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void My_Free (char** buf, char*** text)
{
	free(*buf);
	*buf = NULL;
	free(*text);
	*text = NULL;
}

//-------------------------------------------------------------------------------------------------------------------------------------
		
void Reverse (char** text, int nlines)
{
	for (int j = 0; j < nlines; ++j) {
		char* str = text[j];
		int len = strlen(str);
		for (int i = 0; i < len/2; ++i)
			Swap(str + i, str + len - 1 - i);
		}
}

//-------------------------------------------------------------------------------------------------------------------------------------

void Swap (char *v1, char *v2)
{
  char tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}
	
	
	
	
	
	
	
