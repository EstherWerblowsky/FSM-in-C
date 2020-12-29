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

//this function tests my getNextState function
void testGetNextState(void){
    //initialization of testing arrays
    int fState[25] = {0,2,3,4,5,6,7,8,9,10,22,34,56,78};
    char fInput[25] = {'a','b','c','b','b','d','e','f','f','g','a','b','c','l'};
    int fNext[25]= {3,4,5,7,23,1,23,43,54,65,5443,543,1213,43521};

    //check that it works for a valid input
    int result = getNextState(14,4, 'b', fState, fInput, fNext);
    assert(result == 7);

    //check that it returns the right thing with an invalid input
    result = getNextState(14, 3, 'd', fState, fInput, fNext);
    assert(result == -1);

    //check another valid input
    result = getNextState(14, 34, 'b', fState, fInput, fNext);
    assert(result == 543);
    }

//This function tests my printState() function
void testPrintState(void){
    //initialization of arrays used for testing
    int fState[25] = {0,2,3,4,5,6,7,8,9,10,22,34,56,78};
    char fInput[25] = {'a','b','c','b','b','d','e','f','f','g','a','b','c','l'};
    int fNext[25]= {3,4,5,7,23,1,23,43,54,65,5443,543,1213,43521};

    //check that it returns a -1 in the case where the input does nothing for the FSM
    int result = printState(3, 3, 'a', 14,  fState, fInput, fNext);
    assert(result == -1);

    //check that it works when it is supposed to work
    result = printState(3, 0, 'a', 14,  fState, fInput, fNext);
    assert(result == 3);
    result = printState(3, 78, 'l', 14,  fState, fInput, fNext);
    assert(result == 43521);

    //check that it registers when a non valid input is put in
    result = printState(3, 78, '^', 14,  fState, fInput, fNext);
    assert(result == -1);

}


int main(int argc, char *argv[]) {
    //testing code, if fails testing suite, exit program without continuing to I/O
    testGetNextState();
    testPrintState();

    // make sure that exactly two file inputs are called with this program
    //otherwise print an error message and exit gracefully
    if (argc !=3) {
        printf("Two command line arguments are required \n");
        return -1;
    }

    printf("processing FSM definition file %s \n", argv[1]);

    FILE *mapper;
    mapper = fopen(argv[1], "r");     // open the mapping file
    FILE *input;
    input = fopen(argv[2], "r");    //open the input file

    //check to make sure that they were opened properly
    //if not, then print an error message and exit gracefully
    if (mapper == NULL || input == NULL) {
        printf("Not valid files passed \n");
        return -1;
    }
    //initialize the arrays that are used as the DS for the FSM
    int StateArr[ARRAY_LEN], NextStateArr[ARRAY_LEN];
    char InputArr[ARRAY_LEN];

    //garbage values to be used in the FSM
    char garbage, garbageMore;

    //counter to keep track of how many transitions there are
    //and how long the storage arrays will be
    int line_no = 0;

    //variable to check how many values get scanned in
    int scanResult;

    //read in the values from the fsm file and store them in their respective arrays
    while((scanResult = fscanf(mapper, "%d%c%c%c%d", &StateArr[line_no],  &garbage, &InputArr[line_no], &garbageMore, &NextStateArr[line_no]))!= EOF && line_no< ARRAY_LEN){

        //make sure that the file format is correct at each line
        //otherwise print an error message and return
        if(scanResult<5){
            printf("incorrect format for input to FSM file");
            return -1;
        }
        line_no++;
    }

    printf("The FSM has %d transitions \n", line_no+1);

    //a variable which keeps track of the input for each line of input in the file
    char inputChar;

    //counter which counts how many steps there are in the FSM
    int in_line = 0;

    //variable used to store the current and next states
    int state = 0;
    int nextState = 0;
    while((scanResult = fscanf(input, "%c%c", &inputChar, &garbage))!=EOF && in_line<250){

        //if the input is blank-print error statement and return
        if (scanResult <1){
            printf("Invalid input to FSM");
            return -1;
        }

        //get the next state, and print the current step
        nextState = printState(in_line, state, inputChar, line_no, StateArr, InputArr, NextStateArr);

        //if the return is -1- there was an invalid input somewhere so return from program
        if (nextState == -1){
            printf("Not valid input to the FSM\n");
            return -1;
        }
        printf("at step %d, input %c transitions the FSM from state %d to state %d \n", in_line, inputChar, state, nextState);
        state = nextState;
        in_line ++;
    }


    printf("after %d steps, state machine finished successfully at state %d\n", in_line, state);
    fclose(mapper);
    fclose(input);
}

    //function called by the printState() method to search for the next state with given input and current state
    int getNextState(int length, int state, char input, int StateArr[], char InputArr[], int NextStateArr[]){

        //loop through the length of the filled DS of the FSM
        for (int i = 0; i<= length; i++){

            //search for the corresponding input and state
            if (StateArr[i]== state && InputArr[i]== input){

                //if found, return the appropriate next State
                return NextStateArr[i];
            }
        }

        //otherwise, there is no valid state in the FSM for that input and state combo
        //return -1
        return -1;
}

//printState function- accepts current state, step in FSM, the current input, length of filled FSM arrays, and the FSM arrays
int printState(int step, int state, char input, int length, int StateArr[], char InputArr[], int NextStateArr[]) {
    int nextState;

    //check to make sure that the input is only a lowercase or uppercase letter
    if (input > 'Z' && input <'a' || input > 'z' || input <'A') {
        return -1;
    }

    //get the next state
    nextState = getNextState(length, state, input, StateArr, InputArr, NextStateArr);
    if (nextState == -1)
        return -1;

    return nextState;
    }

