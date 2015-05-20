# MAC
MAC is a really simple virtual machine. It's written in C and is [as of writing this]
only one small C file.

This is the more advanced version, it has more instructions and 
you can pass it files, for instance this file is `test.mac`:

	1 5 2 1
	5 2 1 5
	2 0

Which is passed as an argument to the program `./mac test.mac` and it will
execute the program. Note that there could be more error checks on memory,
etc. But these are not accounted for for simplicity and brevity.

## Registers

	register	purpose
	-------------------------------
	A			general purpose
	B			general purpose
	C			general purpose
	D			general purpose
	E			general purpose
	F			general purpose
	EX 			extra
	EXA 		extra
	IP			instruction pointer
	SP			stack pointer

## Instructions

	op   val    usage    			function
	---------------------------------------------------------------------
	HLT  0      hlt 	 			halts program
	PSH  1      psh val  			pushes <val> to stack
	POP  2      pop 	 			pops value from stack
	ADD  3      add 	 			adds top two vals on stack
	MUL  4      mul 	 			multiplies top two vals on stack
	DIV  5      div 	 			divides top two vals on stack
	SUB  6      sub 	 			subtracts top two vals on stack
	MOV  7      mov reg_a, reg_b 	movs the value in reg_a to reg_b 
	SET  8      set reg, val 		sets the reg to value
	LOG  9      log a 				prints out a
	IF   10     if reg val ip 		if the register == val branch to the ip
	IFN  11     ifn reg val ip 		if the register != val branch to the ip
	GLD  10     gld reg 			loads a register to the stack
	GPT  11     gpt reg 			pushes top of stack to the given register
	NOP  12     nop 				nothing
