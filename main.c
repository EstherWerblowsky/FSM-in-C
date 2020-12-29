#include <stdio.h>
#include <assert.h>
#include <string.h>
#define ARRAY_LEN 2620 //include both lowercase and uppercase letter

//for debugging purposes:
//#ifdef DEBUG
//   *debugging statements here*
//#endif
//struct State{
    //int Current;
    //char Input;
  //  struct State *Next;
//};

int getNextState(int lenArr, int state, char input, int StateArr[], char InputArr[], int NextStateArr[]);
int printState(int in_line, int state, char inputChar, int lenArr,  int StateArr[], char InputArr[], int NextStateArr[]);

void testGetNextState(void){
    int fState[25] = {0,2,3,4,5,6,7,8,9,10,22,34,56,78};
    char fInput[25] = {'a','b','c','b','b','d','e','f','f','g','a','b','c','l'};
    int fNext[25]= {3,4,5,7,23,1,23,43,54,65,5443,543,1213,43521};
    int ret =0;
    int result = getNextState(14,4, 'b', fState, fInput, fNext);
    assert(result == 7);
    result = getNextState(14, 3, 'd', fState, fInput, fNext);
    assert(result == -1);
    result = getNextState(14, 34, 'b', fState, fInput, fNext);
    assert(result == 543);
    }

void testPrintState(void){
    int fState[25] = {0,2,3,4,5,6,7,8,9,10,22,34,56,78};
    char fInput[25] = {'a','b','c','b','b','d','e','f','f','g','a','b','c','l'};
    int fNext[25]= {3,4,5,7,23,1,23,43,54,65,5443,543,1213,43521};

    int result = printState(3, 3, 'a', 14,  fState, fInput, fNext);
    assert(result == -1);

    result = printState(3, 0, 'a', 14,  fState, fInput, fNext);
    assert(result == 3);

    result = printState(3, 78, 'l', 14,  fState, fInput, fNext);
    assert(result == 43521);

}

int main(int argc, char *argv[]) {
    //testing code, if fails testing suite, exit program without continuing to I/O
    testGetNextState();
    testPrintState();

    if (argc !=3) {                                            // make sure that exactly two file inputs are called with this program
        printf("Two command line arguments are required \n");          //otherwise print out an error message
        return -1;                                                            //and exit the program
    }

    printf("processing FSM definition file %s \n", argv[1]);
    FILE *mapper;
    mapper = fopen(argv[1], "r");     // open the mapping file
    FILE *input;
    input = fopen(argv[2], "r");    //open the input file

    if (mapper == NULL || input == NULL) {                  //check to make sure that they were opened properly
        printf("Not valid files passed \n");           //if not, then print an error message
        return -1;                                              //and break
    }
                                               //provided that there are two properly opened finals
    int StateArr[ARRAY_LEN], NextStateArr[ARRAY_LEN];
    char InputArr[ARRAY_LEN];
    char garbage, garbageMore;
    int line_no = 0;

    while((fscanf(mapper, "%d%c%c%c%d", &StateArr[line_no],  &garbage, &InputArr[line_no], &garbageMore, &NextStateArr[line_no]))!= EOF && line_no< ARRAY_LEN){
        //FSM( line_no, state ,in, next, StateArr, InputArr, NextStateArr);
        line_no++;
    }

    printf("The FSM has %d transitions \n", line_no+1);
    char inputChar;
    int in_line = 0;
    int state = 0;
    int scanResult;
    while((scanResult = fscanf(input, "%c%c", &inputChar, &garbage))!=EOF && in_line<250){
        if (scanResult > 2){                         //checks to make sure that the correct input was given
            printf("Invalid input to FSM");
            return -1;
        }
        state = printState(in_line, state, inputChar, line_no, StateArr, InputArr, NextStateArr);
        if (state == -1){
            printf("Invalid Input to FSM \n");
            return -1;
        }
        in_line ++;
    }
    printf("after %d steps, state machine finished successfully at state %d\n", in_line, state);
    fclose(mapper);
    fclose(input);
}

    int getNextState(int length, int state, char input, int StateArr[], char InputArr[], int NextStateArr[]){
        for (int i = 0; i<= length; i++){
            if (StateArr[i]== state && InputArr[i]== input){
                return NextStateArr[i];
            }
        }
        printf("there is no path for input %c at state %d\n", input, state);
        return -1;
}

int printState(int step, int state, char input, int length, int StateArr[], char InputArr[], int NextStateArr[]) {
    int nextState;
    if (input > 'Z' && input <'a' || input > 'z' || input <'A') {
        return -1;
    }

    nextState = getNextState(length, state, input, StateArr, InputArr, NextStateArr);
    if (nextState == -1)
        return -1;

    printf("at step %d, input %c transitions the FSM from state %d to state %d \n", step, input, state, nextState);

    return nextState;
    }
