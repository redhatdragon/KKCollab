#pragma once

//#define DELETE(_objName, _obj) \
//_objName##Destruct(_obj);

#define PRIM_FOR(_num) \
{ \
	unsigned int i = 0; \
	while(i < _num){

#define FOR(_init, _condition, _doAtEnd) \
{ \
	_init; \
	while(_condition){ \
	_doAtEnd;

#define FOR_END }}



char* concat(const char *s1, const char *s2)
{
	char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
													   //in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}



/***********************************************************
Functions/Macros for reading/wrighting to files of any os.
***********************************************************/



#ifdef _WIN32
__forceinline int BPGetFileSize(char *filename) {
	FILE *file;
	file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);  //may not be necessary.
	fclose(file);
	return size;
}
__forceinline char* BPReadFile(char *filename) {
	//signed char c;
	int bufferLength = BPGetFileSize(filename);
	char *buffer = (char*)malloc(bufferLength + 1);
	FILE *file;
	file = fopen(filename, "r");
	if (file) {
		int count = 0;
		//while ((c = getc(file)) != EOF) {
		while(count < bufferLength) {
			//putchar(c);
			//buffer[count] = c;
			buffer[count] = getc(file);
			count++;
		}
		buffer[bufferLength] = 0;
		fclose(file);
		return buffer;
	}
	return NULL;
}
__forceinline void BPWriteToFile(char *filename, char *str) {
	FILE *file;
	file = fopen(filename, "w");
	if (file == NULL) {
		printf("File not created, errno = %d\n", errno);
	}
	fprintf(file, str);
	fclose(file);
}
__forceinline void BPRemoveDir(char *dirname) {
	int cheack;
	//clrscr();
	//system("dir/p");
	//char *str = dirname;
	char *str = concat("rmdir /s /q ", dirname);
	system(str);
	/*cheack = rmdir(str);
	if (!cheack){
		printf("Directory deleted\n");
	}else{
		printf("Unable to remove directory\n");
		//getch();
		return;
	}*/
	//getch();
}
__forceinline char* BPGetFilesInDir() {
	DIR *dir;
	struct dirent *ent;
	char *directory = NULL;
	if ((dir = opendir(".")) != NULL) {
		unsigned int size = 256;
		unsigned int length = 0;
		directory = (char*)malloc(size);
		while ((ent = readdir(dir)) != NULL) {
			unsigned int count = 0;
			while (1) {
				if (length < size-1) {
					directory[length] = ent->d_name[count];
					count++;
					length++;
					if (ent->d_name[count-1] == 0) {
						directory[length - 1] = '\n'; break;
					}
				}else{
					size = size * 2;
					realloc(directory, size);
					directory[length] = ent->d_name[count];
					count++;
					length++;
					if (ent->d_name[count - 1] == 0) {
						directory[length - 1] = '\n'; break;
					}
				}
			}
			directory[length] = 0;
		}
		closedir(dir);
		return directory;
	}else{
		printf("couldn't open directory.");
		return directory;
	}
}
#elif defined(LINUX)
__forceinline bool BPGetFilesInDir() {

}
__forceinline bool BPWriteToFile(char *filename, char *str) {
	FILE *fp;
	fp = fopen(&filename, "w");
	if (fp == NULL) {
		printf("File not created, errno = %d\n", errno);
		return 1;
	}
	fprintf (fp, &str); // if you want something in the file.
	fclose(fp);
	printf("File created okay\n");
}
#elif defined(APPLE)

#endif
