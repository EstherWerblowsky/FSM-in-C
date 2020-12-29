#include <stdio.h>
#include <assert.h>
#include <string.h>
#define ARRAY_LEN 1310

//for debugging purposes:
//#ifdef DEBUG
//   *debugging statements here*
//#endif
//struct State{
    //int Current;
    //char Input;
  //  struct State *Next;
//};

//int getLength(int* State, char* Input, int* NextState);
//void FSM(int index, int fsmState, char fsmIn, int fsmNext, int* State, char* Input, int* NextState);//FILE* mapper, int* State, char* Input, int* NextState);
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

 //void testFSMFunc(void){
   // int State[35] = {0,23,546,7,43,32,543,6342,1,2342,543,63,6,475,86,87,1,2,3,4,5,6,7,8,9,0,2,1,3,43};
    //char Input[35] = {'a','b','c','d','e','f','g','h','i','j','k','a','a','b','c','d','e','f','f','g','h','a','c','d','g','h','a','e','f','y'};
    //int Next[35]= {1,0,7,546,543,6342, 1,2342, 23, 63,6,475, 86,87, 1,2,3,4,5,6,7,8,9,0,2,1,3,43,32,23};
    //int empState[32];
    //char empIn[32];
    //int empNextState[32];
    //for(int i = 0; i<30; i++){
      //  FSM(i, State[i], Input[i], Next[i], empState, empIn, empNextState);
        //assert(State[i]== empState[i]);
        //assert(Input[i]== empIn[i]);
        //assert(Next[i]== empNextState[i]);
    //}
//}

//void testGetState(void){
  //  char str[25] = "98:a<5213";
    //char state = extractState(str);
    //char input = extractInput(str);
    //char next = extractNext(str);
    //assert(state == 98);
    //assert(input == 'a');
    //assert(next == 5213);
//}




int main(int argc, char *argv[]) {
    //testing code, if fails testing suite, exit program without continuing to I/O
    testGetNextState();
    //testFSMFunc();
  //  testGetState();

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
    while((fscanf(input, "%c%c", &inputChar, &garbage))!=EOF && in_line<250){
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
    //void FSM(int line_no, int num, char in, int next, int* State, char* Input, int* NextState) { //FILE* mapper
      //  State[line_no] = num;
        //Input[line_no] = in;
        //NextState[line_no] = next;
        //printf("here we are:[%d]:[%c]:[%d]", State[line_no], Input[line_no], NextState[line_no]);
        //printf("[%d]:[%c]:[%d]\n", num, in, next);
            //lenArr = line_no +1;
            //printf("the length of the array is %d", length);
        //printf("State[%d] is %d, Input[%d] is %c, NextState[%d] is %d", line_no, State[line_no], line_no, Input[line_no], line_no, NextState[line_no]);
    //}

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
    if (input > 'z' || input < 'a') {
        printf("oops the input is %c", input);
        return -1;
    }
    nextState = getNextState(length, state, input, StateArr, InputArr, NextStateArr);
    if (nextState == -1)
        return -1;
    printf("at step %d, input %c transitions the FSM from state %d to state %d \n", step, input, state, nextState);
    state = nextState;
    return state;
    }
