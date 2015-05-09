# MAC
MAC is a really simple virtual machine. It's written in C and is [as of writing this]
only one small C file.

[Blog Post!](http://blog.felixangell.com/virtual-machine-in-c/)

Check out the [improved version](mac-improved/) to see an implementation of more instructions,
registers, etc...

## Instructions

	op   val    usage    			function
	---------------------------------------------------------------------
	HLT  0      hlt 	 			halts program
	PSH  1      psh val  			pushes <val> to stack
	POP  2      pop 	 			pops value from stack
	ADD  3      add 	 			adds top two vals on stack
