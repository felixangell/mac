#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 256
static int stack[STACK_SIZE];

/** Registers */
typedef enum {
	A,				// GENERAL PURPOSE
	B,
	C,
	D,
	E,
	F,
	IP,				// INSTRUCTION POINTER
	SP,				// STACK POINTER
	REGISTER_SIZE
} Registers;
static int registers[REGISTER_SIZE];

/** Instructions */
typedef enum {
	HLT, // 0 -- halts the program
	PSH, // 1 -- pushes the next instruction
	POP, // 2 -- pops the stack
	ADD, // 3 -- pops stack twice, adds result pushes to stack
	MUL, // 4 -- pops stack twice, multiplies the result pushes to stack
	DIV, // 5 -- pops stack twice, divides result pushes to stack
	SUB, // 6 -- pops stack twice, substracts result pushes to stack
	NOP  // 7 -- nothing
} Instructions;

/** Program to run */
static int instructions[] = {
	PSH, 5,
	PSH, 2,
	ADD,
	PSH, 10,
	PSH, 12,
	ADD,
	ADD,
	POP,
	HLT
};

/** if the program is running */
static bool running = true;

/** quick ways to get SP and IP */
#define SP (registers[SP])
#define IP (registers[IP])

/** fetch current instruction */
#define FETCH (instructions[IP])

/** prints the stack from A to B */
void print_stack(int from, int to) {
	for (int i = from; i < to; i++) {
		printf("0x%04x ", stack[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
	printf("\n");

	for (int i = from; i < to; i++) {
		printf("0x%04d ", stack[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
	printf("\n");
}

/** evaluate the given instruction */
void eval(int instr) {
	switch (instr) {
	case HLT: {
		running = false;
		printf("finished execution\n");
		print_stack(0, 16);
		break;
	}
	case PSH: {
		int y = stack[SP] = instructions[IP + 1];
		IP = IP + 1;
		SP = SP + 1;
		printf("pushed %d\n", y);
		break;
	}
	case POP: {
		int x = stack[SP];
		SP = SP - 1;
		printf("popped %d\n", x);
		break;
	}
	case ADD: {
		registers[A] = stack[SP - 1] + stack[SP - 2];
		SP = SP - 2;
		stack[SP] = registers[A];
		SP = SP + 1;
		printf("added %d\n", registers[A]);
		registers[A] = 0;
		break;
	}
	case NOP: {
		printf("do nothing\n");
		break;
	}
	default: {
		printf("unknown instruction %d\n", instr);
		break;
	}
	}
}

int main() {
	while (running) {
		eval(FETCH);
		IP = IP + 1;
	}
	
	return 0;
}
