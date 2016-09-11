/**

	This is almost identical to the articles
	VM

**/

#include <stdio.h>
#include <stdbool.h>

bool _running = true;
int ip = 0; // counter for "source code"
int sp = -1; // counter for data stack

int stack[256]; // equivalent to a data stack; not to be confused with call stack

typedef enum {
   PSH,
   ADD,
   POP,
   HLT
} InstructionSet;

// simple "source code" to be executed
const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};


int fetch() {
    // iterates through source code
    return program[ip];
}

void eval(int instr) {
    switch (instr) {

        case HLT: {
            // halt case - program is terminated by setting _running to false
            _running = false;
            printf("done\n");
            break;
        }

        case PSH: {
            // add whatever follows PSH in the source code to data stack
    	    sp++;
	        stack[sp] = program[++ip];
	        break;
        }

        case POP: {
            // print TOC - top of stack
	        int val_popped = stack[sp--];
	        printf("popped %d\n", val_popped);
	        break;
	    }
        
	    case ADD: {
	        // first we pop the stack and store it as a
	        int a = stack[sp--];
	    
	        // then we pop the top of the stack and store it as b
	        int b = stack[sp--];

	        // we then add the result and push it to the stack
	        int result = b + a;
	        sp++; // increment stack pointer **before**
	        stack[sp] = result; // set the value to the top of the stack

	        // all done!
	        break;
	    }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++; // increment the ip every iteration
    }
}