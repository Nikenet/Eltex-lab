// Sort by alphabet

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN	35
#define MAX_LINE_COUNT	15

static char *read_line(void)
{
	char *buf = (char *) malloc(sizeof(char) * MAX_LINE_LEN);
	return fgets(buf, MAX_LINE_COUNT - 1, stdin);
}

static int cmp(const void *p1, const void *p2){
	char **str1 = (char **) p1;
	char **str2 = (char **) p2;
	return strcmp(*str1, *str2);
}

int main(int argc, char **argv) {
	char *buf[MAX_LINE_COUNT];
	int i, count = 0;

	for (i = 0; i < MAX_LINE_COUNT; i++) {
		buf[i] = read_line();
		if (buf[i] == NULL)
			break;

		count++;
	}

	printf("After sorting: \n");

	for (i = 1; i < count; i++) {

		printf("\t#%d %s", i, buf[i]);
	}

	qsort(&buf[0], count, sizeof(char *), cmp);

	printf("\nBefore sorting: \n");

	for (i = 1; i < count; i++) {
		printf("\t#%02d %s", i, buf[i]);
		free(buf[i]);
	}

	return 0;
}
