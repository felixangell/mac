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
	I,
	J,
	EX,				// EXCESS
	EXA,			// MORE EXCESS
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
	MOV, // 7 -- mov reg, reg
	SET, // 8 -- mov val, reg
	NOP  // 9 -- nothing
} Instructions;

/** if the program is running */
static bool running = true;

/** testing addition */
int test_a[] = {
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

/** testing multiplication */
int test_b[] = {
	PSH, 5,
	PSH, 2,
	MUL,
	PSH, 10,
	PSH, 20,
	ADD,
	ADD,
	HLT
};

/** testing set and move */
int instructions[] = {
	SET, A, 0
};

/** quick ways to get SP and IP */
#define SP (registers[SP])
#define IP (registers[IP])

/** fetch current instruction */
#define FETCH (instructions[IP])

/** prints the stack from A to B */
void print_stack(int from, int to) {
	printf("\n");
	printf("hex dump from %d to %d\n", from, to);
	for (int i = from; i < to; i++) {
		printf("0x%04x ", stack[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
	printf("\n");

	printf("decimal dump from %d to %d\n", from, to);
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
		SP = SP + 1;
		IP = IP + 1;
		stack[SP] = instructions[IP];
		break;
	}
	case POP: {
		SP = SP - 1;
		break;
	}
	case MOV: {
		registers[EX] = instructions[ip + 1]; // address of from
		registers[EXA] = instructions[ip + 2]; // adress of to
		for (int i = 0; i < REGISTER_SIZE; i++) {
			if (i != registers[EX] && i != registers[EXA]) {
				
			}
		}
		break;
	}
	case SET: {
		printf("curr instr: %d\n", instructions[IP]);
		break;
	}
	case ADD: {
		registers[A] = stack[SP];
		SP = SP - 1;
		
		registers[B] = stack[SP];
		SP = SP - 1;

		registers[C] = registers[B] + registers[A];

		SP = SP + 1;
		stack[SP] = registers[C];
		printf("%d + %d = %d\n", registers[B], registers[A], registers[C]);
		break;
	}
	case SUB: {
		registers[A] = stack[SP];
		SP = SP - 1;
		
		registers[B] = stack[SP];
		SP = SP - 1;

		registers[C] = registers[B] - registers[A];

		SP = SP + 1;
		stack[SP] = registers[C];
		printf("%d - %d = %d\n", registers[B], registers[A], registers[C]);
		break;
	}
	case DIV: {
		registers[A] = stack[SP];
		SP = SP - 1;
		
		registers[B] = stack[SP];
		SP = SP - 1;

		registers[C] = registers[B] / registers[A];

		SP = SP + 1;
		stack[SP] = registers[C];
		printf("%d / %d = %d\n", registers[B], registers[A], registers[C]);
		break;
	}
	case MUL: {
		registers[A] = stack[SP];
		SP = SP - 1;
		
		registers[B] = stack[SP];
		SP = SP - 1;

		registers[C] = registers[B] * registers[A];

		SP = SP + 1;
		stack[SP] = registers[C];
		printf("%d * %d = %d\n", registers[B], registers[A], registers[C]);
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
	SP = -1;
	
	while (running) {
		eval(FETCH);
		IP = IP + 1;
	}
	
	return 0;
}
