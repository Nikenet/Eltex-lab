#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

//Write file
void write_string(char *str, FILE *file)
{
 	while(*str){ 
		if(!ferror(file)){
			fputc(*str++, file);
		}   
	} 
}

//Delete length
void delete_length(int length, FILE *file)
{
	FILE *out;
	out = fopen("test.txt.out", "w");

	int i = 0, count=0;
	char ch;
	char buf[length+1];
	
	while(ch != EOF) {
		ch = getc(file);

		if ((ch < 65 || ch > 90) && (ch < 97 || ch > 122)) {
			if (count > 0 && count <= length) {
				buf[i++] = '\0';
				fprintf(out, "%s\n", buf);
			}

			count = 0;
			i = 0;

			continue;
		}

		if (count++ > length)
			continue;
		
		buf[i++] = ch;
	}

	fclose(out);
}

//Delete char
void delete_char(char symbol, FILE *file)
{
	char ch;

	FILE *out;
	out = fopen("test.txt.out", "w");

	while(ch != EOF) {
		ch = getc(file);
		if (ch != symbol)
			fprintf(out, "%c", ch);
	}

	fclose(out);
}

int main(int argc, char *argv[])
{

	FILE *file;
	int opt, length;
	char symbol;

	struct 
	{
		const char *file_name;
		int task_id;
	} app_data;

	//Clean structure (fill 0x00 everywhere)
	memset(&app_data, 0x00, sizeof(app_data));


	if (argc < 2)
	{
		printf("Not enought parametrs, look --help \n");
	}

	while((opt = getopt(argc, argv, "f:n:")) != -1)
	{
		switch (opt) 
		{		
			case 'f':
				app_data.file_name = optarg;
				break;

			case 'n':
				app_data.task_id = atoi(optarg);
				break;

			default: 
				fprintf(stderr, "Usage: [-f file] [-n number of task]\n");
				exit(EXIT_FAILURE);
		}
	}

	if (app_data.file_name == NULL)
	{
		printf("\n");
		exit(1);
	}

	file = fopen(app_data.file_name, "r");
	if (file == NULL) {
		printf("Couldn't open file %s\n", app_data.file_name);
		exit(1);
	}

	if (app_data.task_id == 1) {	
		printf("Choose max length: \n");
		scanf("%d", &length);
		delete_length(length, file);                 
		
	} else if (app_data.task_id == 2) {
		printf("Choose symbol\n");
		scanf("%c", &symbol);
		delete_char(symbol, file);
	} else {
		printf("Unknown task id O_o\n");
	}

	if(fclose(file)){ 
		printf("Close error.\n");
		exit(1);
	}
	return 0;

}
