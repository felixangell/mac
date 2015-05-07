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
	HLT, // 0 -- hlt :: halts program
	PSH, // 1 -- psh val :: pushes <val> to stack
	POP, // 2 -- pop :: pops value from stack
	ADD, // 3 -- add :: adds top two vals on stack
	MUL, // 4 -- mul :: multiplies top two vals on stack
	DIV, // 5 -- div :: divides top two vals on stack
	SUB, // 6 -- sub :: subtracts top two vals on stack
	MOV, // 7 -- mov reg_a, reg_b :: movs the value in reg_a to reg_b 
	SET, // 8 -- set reg, val :: sets the reg to value
	LOG, // 9 -- log a :: prints out a
	NOP  // 9 -- nop :: nothing
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
	SET, A, 2,
	MOV, A, C,
	MOV, C, D,
	LOG, A,
	LOG, E,
	HLT
};

/** quick ways to get SP and IP */
#define SP (registers[SP])
#define IP (registers[IP])

/** fetch current instruction */
#define FETCH (instructions[IP])

/** prints the stack from A to B */
void print_stack(int from, int to) {
	printf("decimal dump from %d to %d\n", from, to);
	for (int i = from; i < to; i++) {
		printf("0x%04d ", stack[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
	printf("\n");
}

void print_registers() {
	printf("register dump\n");
	for (int i = 0; i < REGISTER_SIZE; i++) {
		printf("%04d ", registers[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
}

int find_empty_register() {
	for (int i = 0; i < REGISTER_SIZE; i++) {
		if (i != registers[EX] && i != registers[EXA]) {
			return i;
		}
	}
	return EX; // throw it in EX, whatever
}

/** evaluate the given instruction */
void eval(int instr) {
	switch (instr) {
	case HLT: {
		running = false;
		printf("finished execution\n");
		// print_stack(0, 16);
		// print_registers();
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
		registers[instructions[IP + 2]] = registers[instructions[IP + 1]];
		IP = IP + 2;
		break;
	}
	case SET: {
		registers[instructions[IP + 1]] = instructions[IP + 2];
		IP = IP + 2;
		break;
	}
	case LOG: {
		printf("%d\n", registers[instructions[IP + 1]]);
		IP = IP + 1;
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
