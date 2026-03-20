/*
Arda Ayna, aa3755
Section: H02
Semester: Spring 26
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int stack_size = 20, stackptr = -1;
char* stack;

int pda755(char* str);
/*
    I reused the main function from project 1 
    as its function is significantly similar to the 
    requirements of this project.
    The main difference is that this one is compliant with the ANSI C standard.

*/
int main(){ 
    char buffer[MAX_SIZE];
    long itercount;
    char *endptr,*b;
    int i,result;
    size_t buffsize = MAX_SIZE;
    printf("Project 2 for CS 341\nSection number: H02\nSemester: Spring 2026\nWritten by: Arda Ayna, aa3755\nInstructor: Marvin Nakayama, marvin@njit.edu\n");
    printf("\nEnter the number of test cases: \n");
    getline(&b,&buffsize,stdin);

    
    itercount = strtol(b,&endptr,10);

    if (b==endptr || (*endptr != '\n' && *endptr != '\r')){
        printf("Invalid input\n");
        return 1;
    }
    if(itercount == 0){
        printf("No test cases to process.\n");
        return 0;
    }
    else if(itercount < 0){
        printf("Test cases cannot be negative.\n");
        return 1;
    }

    printf("Amount of test cases to process: %ld\n",itercount);
    
    /*loop to go over the test cases*/
    for( i = 1; i <= itercount; i++){
        printf("Enter string %d of %ld: \n",i,itercount);
        getline(&b,&buffsize,stdin);
        printf("The string to process is: %s", b);
        result = pda755(b);
        if(result == 7)
            printf("The string %s is accepted.\n",b);
        else    
            printf("The string %s is rejected.\n",b);

        /*resetting stack size and pointer for the next testcase*/
        stack_size = 20;
        stackptr = -1;
    }

    return 0;
}


char safe_pop755(){ 
    char c;
    if (stackptr==-1)
        return -1;
    c = stack[stackptr--];
    /*
    shrink stack if <=25% full
    */
    if (stackptr <= (stack_size/4)){
        stack_size /= 2;
        stack = (char*)realloc((void *)stack,stack_size);
    }
    return c;

}
void safe_push755(char c){
    /*
    stack is full, grow
    */
    if (stackptr==stack_size-1){
        stack_size *= 2;
        stack = (char*)realloc((void*) stack, stack_size);
    }
    stack[++stackptr] = c;
}


/*
    The PDA function is also practically the same as the DFA function from project 1, with minor tweaks used
    to manipulate the stack 
*/
int pda755(char* testcase){
    /*
        using malloc to create the stack so that memory can be reallocated as stack grows/shrinks
    */
    stack =(char *)malloc(stack_size);
    int i,state = 0;
    char c;
    for(i = 0; (c = *(testcase+i)) != '\n' && c != '\r'; i++){
        transition755(c,&state);
        if(state==-1)
            return state;
    }


    //changing \r or \n (depending on file type) to \0 so that \r\n is not printed when printing the string
    //otherwise causes weird formatting of output
    *(testcase+i) = '\0';
    return state;



}

void transition755(char c, int* state){
    int from;
    char popped = 0, pushed = 0;

    switch (*state){
        case 0:
            if(c=='d'){
                safe_push755(pushed = '$');
                *state = 1;
                from = 0;
                break;
            }
        case 1:

        case 2:

        case 3:

        case 4:

        case 5:

        case 6:

        case 7:

        case 8:

        case 9:

        case 10:


    }
    printf("Prior state q%d, read %c, popped %s, pushed %c, new state q%d",from,c,(popped ? popped : "nothing"), (pushed ? pushed : "nothing"), *state);

}