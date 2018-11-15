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
			while (i + 1 <= last && buf[i+1] == '\n')
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
			while (i + 1 <= last && buf[i+1] == '\n')
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
		while (!Custom_Encoding(*str1)) *str1++;
		while (!Custom_Encoding(*str2)) *str2++;
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

//-------------------------------------------------------------------------------------------------------------------------------------

unsigned Linear_Search (const void *parr, unsigned len, unsigned size, cmp_t cmp)
{
	assert(parr);
	assert(len > 0);
	const void *min = parr;
	unsigned i, minpos = 0; 
	for (i = 1, parr = (const char*)parr + size; i < len; i++, parr = (const char*)parr + size)
    	if (cmp(parr, min) < 0) {
    		min = parr;
    		minpos = i;
		}
	return minpos;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void Swap_Voids (void *x, void *y, unsigned size)
{
	for (char *t = (char*) x, *p = (char*) y; t < (char*) x + size; t++, p++)
		Swap (t, p);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void Selsort (void *arr, unsigned len, unsigned size, cmp_t cmp) 
{
	for (unsigned i = 0; i < len; i++) {
		unsigned minpos = Linear_Search(arr + i*size, len - i, size, cmp);
		Swap_Voids(arr + i*size, arr + (i + minpos)*size, size);
	}
}

