// Arda Ayna, aa3755
// Section: H02
// Semester: Spring 26



#include <stdio.h>
#include <stdlib.h>

int dfa755(char* testcase);
void transition755(char c,int* state);
int main(){

    printf("Project 1 for CS 341\nSection number: H02\nSemester: Spring 2026\nWritten by: Arda Ayna, aa3755\nInstructor: Marvin Nakayama, marvin@njit.edu\n");
    printf("\nEnter the number of test cases: \n");
    //100 characters, in my opinion, is a reasonable maximum length for an email.
    size_t buffsize = 100; 
    char buffer[buffsize];
    char* b = buffer;
    getline(&b,&buffsize,stdin);
    char* endptr;
    long itercount = strtol(b,&endptr,10);
    //checking for \r here is necessary because the test file is CRLF, so
    //the lines end with \r\n, not \n. However, I kept the \n so that it is also compatible
    //with LF.
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
    int i,result;
    //loop to go over the test cases
    for( i = 1; i <= itercount; i++){
        printf("Enter string %d of %ld: \n",i,itercount);
        getline(&b,&buffsize,stdin);
        printf("The string to process is: %s", b);
        result = dfa755(b);
        if(result == 7)
            printf("The string %s is accepted.\n",b);
        else
            printf("The string %s is rejected.\n",b);
    }

    return 0;
}
//the main logic of the dfa that iters over the test case and returns the final state of the DFA
int dfa755(char* testcase){
    int i,state = 0;
    char c;
    for(i = 0; (c = *(testcase+i)) != '\n' && c != '\r'; i++){
        transition755(c,&state);
    }
    //changing \r or \n (depending on file type) to \0 so that \r\n is not printed when printing the string
    //otherwise causes weird formatting
    *(testcase+i) = '\0';
    return state;
}

//the transition function of the dfa
void transition755(char c,int* state){
    int from; //this is only necessary to print out the prior state
      
    //switch statement to implement the actual transition conditions
    //all states are the same as the DFA drawing
    switch(*state){
        case 0:
            from = 0;
            if(c >= 'a' && c <= 'z')
                *state = 1;
            else
                *state = 9;
            break;
        case 1:
            from = 1;
            if(c >= 'a' && c <= 'z')
                //we can skip this because the state is already one and it should stay as one.
                ;
            else if(c=='.')
                *state = 8;
            else if(c=='@')
                *state = 2;
            else
                //this else is unnecessary as the project guarantees an input over the language
                //however, I still added it because in case I test it with other test cases.
                *state = 9;
            break;
        case 2:
            from = 2;
            if(c >= 'a' && c <= 'z')
                *state = 3;
            else
                *state = 9;
            break;
        case 3:
            from = 3;
            if(c >= 'a' && c <= 'z')
                //same as state 1
                ;
            else if(c == '.')
                *state = 4;
            else
                *state = 9;
            break;
        case 4:
            from = 4;
            if(c=='i')
                *state = 5;
            else if(c>='a' && c<='z')
                *state = 3;
            else
                *state = 9;
            break;
        case 5:
            from = 5;
            if(c=='n')
                *state = 6;
            else if(c>='a' && c<='z')
                *state = 3;
            else if(c=='.')
                *state = 4;
            else
                *state = 9;
            break;
        case 6:
            from = 6;
            if(c=='t' || c=='c')
                *state = 7;
            else if(c>='a' && c<='z')
                *state = 3;
            else if(c=='.')
                *state = 4;
            else
                *state = 9;
            break;
        case 7:
            from = 7;
            if(c>='a' && c<='z')
                *state = 3;
            else if(c=='.')
                *state = 4;
            else
                *state = 9;
            break;
        case 8:
            from = 8;
            if(c>='a' && c<='z')
                *state = 1;
            else
                *state = 9;
            break;
        //no need to change *state since it will be stuck in q9 until the end of the string.
        case 9: //trap state
            from = 9;
            break;
        }
    printf("State before - q%d, read \'%c\', new state - q%d\n",from,c,*state);

}