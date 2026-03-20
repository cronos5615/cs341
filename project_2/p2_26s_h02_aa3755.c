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
        if (result == 10)
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
            break;
    }

    free((void*)state);
    *(testcase+i) = '\0';
    return state;



}

void transition755(char c, int* state){
    int from;
    char popped = 0, pushed = 0;

    switch (*state){
        case 0:
            from = 0;
            if(c=='d'){
                safe_push755(pushed = '$');
                *state = 1;
            }
            else
                *state = -1;
            break;
        case 1:
            from = 1;
            if(c=='w')
                *state = 2;
            else    
                *state = -1;
            break;
        case 2:
            from = 2;
            if(c=='w')
                *state = 3;
            else if (c=='q')
                *state = 4;
            else
                *state = -1;
            break;

        case 3:
            from = 3;
            if(c=='(')
                safe_push755(pushed = c);
            else if (c=='.')
                *state = 6;
            else if(c >='0' && c <= '9')
                *state = 5;
            else 
                *state = -1;
            break;
        case 4:
        from = 4;
            if(c=='p'){
                safe_push755(pushed = c);
                *state = 2;
            }
            else
                *state = -1;
            break;
        case 5:
            from = 5;
            if(c >='0' && c <= '9')
                ;
            else if (c=='.')
                *state = 7;
            else
                *state = -1;
            break;

        case 6:
            from = 6;
            if(c >='0' && c <= '9')
                *state = 7;
            else
                *state = -1;
            break;
            

        case 7:
            from = 7;
            if(c >='0' && c <= '9')
                ;
            else if (c == ')'){
                
                if ((popped = safe_pop755()) == '('){
                    *state = 8;
                }
                else
                    *state = -1;
                
            }
            else if (c== 'v')
                *state = 9;
            else if (c=='+' || c == '-' || c == '*' || c == '/')
                *state = 3;
            else
                *state = -1;
        case 8:
            from = 8;
            if (c == ')'){
                
                if ((popped = safe_pop755()) == '('){
                    ;
                }
                else
                    *state = -1;
                
            }
            else if (c== 'v')
                *state = 9;
            else if (c=='+' || c == '-' || c == '*' || c == '/')
                *state = 3;
            else
                *state = -1;

        case 9:
            from = 9;
            if(c == 'd'){
                if((popped = safe_pop755()) == 'p')
                    ;
                else
                    *state = -1;
            }
            else if (c == 'v'){
                if((popped = safe_pop755()) == '$')
                    *state=10;
                else
                    *state = -1;
            }
            else
                *state = -1;
            break;
        case 10:
            from = 10;
            *state = -1;
            /*
                by design, we should never actually go into this case, as reading the last v should set state to 10 and the transition function should not be called after that.
                if we enter here, there is at least 1 extra character in the string.
            */
            


    }
    if(*state = -1){
        printf("The PDA crashed on the following transition:\nPrior state q%d, read %c, popped %c, pushed %c\n",from,c,(popped ? popped : ' '), (pushed ? pushed : ' '));
        return;
    }
    printf("Prior state q%d, read %c, popped %c, pushed %c, new state q%d\n",from,c,(popped ? popped : ' '), (pushed ? pushed : ' '), *state);

}