#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int (*cmp_t) (const void *, const void *); 
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
unsigned Linear_Search (const void *parr, unsigned len, unsigned size, cmp_t cmp);
void Swap_Voids (void *x, void *y, unsigned size);
void Selsort (void *arr, unsigned len, unsigned size, cmp_t cmp);

#include "func.c"


