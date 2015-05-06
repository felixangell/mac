# MAC
MAC is a really simple virtual machine. It's written in C and is [as of writing this]
only one small C file.

## Registers

	register	purpose
	A			general purpose
	B			general purpose
	C			general purpose
	D			general purpose
	E			general purpose
	F			general purpose
	IP			instruction pointer
	SP			stack pointer

## Instructions

	op   val    function
	---------------------------------------------------------------------
	HLT  0		halts the program
	PSH  1		pushes the next instruction
	POP  2		pops the stack
	ADD  3		pops stack twice, adds result pushes to stack
	MUL  4		pops stack twice, multiplies the result pushes to stack
	DIV  5		pops stack twice, divides result pushes to stack
	SUB  6		pops stack twice, substracts result pushes to stack
	NOP  7		nothing