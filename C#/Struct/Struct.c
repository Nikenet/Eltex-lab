// first variant

#include <stdio.h>
#include <stdlib.h>

//struct for storage data
struct person
{
	char surname[20];
	int burth;
	int numberofdepartment;
	int salary;
};
typedef struct person persons;

//function to prosses of inputing data
void input(persons *st)
{
	printf("\nInput surname:\n");
	scanf("%s", st->surname);

	printf("\nInput burth:\n");
	scanf("%d", &st->burth);

	printf("\nInput number of department:\n");
	scanf("%d", &st->numberofdepartment);

	printf("\nInput salary:\n");
	scanf("%d", &st->salary);
}

static int cmp(const void *p1, const void *p2)
{
	persons * st1 = *(persons**)p1;
	persons * st2 = *(persons**)p2;
	return st1 -> burth - st2 -> burth;
}

int main(int argc, char **argv)
{
	int count = 3;

    printf("\nInput count of persons: ");
    scanf("%d", &count);

    persons** st = (persons**)malloc(sizeof(persons**)*count);

    for (int i = 0; i < count ; i++){
        st[i] = (persons*) malloc (sizeof(persons));
        input(st[i]);
    }

    qsort(st, count, sizeof(persons*), cmp); 

    printf("\nOldest person is %s who burth in %d\n", st[0]->surname, st[0]->burth);
    printf("\nOther persons is:\n");

    for (int i = 1; i < count; ++i){
    	printf("\t%s, who has %d burth, works in %d department and his salary is %d \n",
    		st[i]->surname, st[i]->burth, st[1]->numberofdepartment, st[1]->salary);
	}

    for (int i = 0; i < count; i++)
        free(st[i]);
	
    free(st);
    return 0;
}
