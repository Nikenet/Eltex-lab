#include <stdio.h>
#include <dlfcn.h>
#include "header.h"

int main(int argc, char const *argv[])
{	
	int x, y;
	void *extlib;
	int (*func)(int x, int y);
		
	if (argc < 2){
		printf("Need arguments (addition or substraction)\n");
		return 1;
	}

	extlib = dlopen("/home/nikenet/Eltex/C#/Library/dl/libcount.so",RTLD_LAZY);
	if (!extlib){	
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	}

	printf("Input x and y\n");
	scanf("%d %d", &x, &y);
		
	func = dlsym(extlib, argv[1]);	
	
	printf("%d\n", func(x, y));
	
	dlclose(extlib);
	return 0;
}
