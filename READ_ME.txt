AbstractVM
A simple virtual machine that can interpret programs written in a basic assembly language

AbstractVm is able to run programs from a file passed as parameter and from the standard input. When reading from the standard input, the end of the program is indicated by the special symbol ;; otherwise absent.

Instructions
Comment start with a ; abd finish with a newline. Acomment can ve either at th start of a line, or after an instruction
push + v : Pushes the value v at the top of the stack
pop: Unstacks the value from the top of the stack
dump: Displays eaach values of the stack
assert + v : Asserts that the value at the top of the stack is equal to the one passed
add: Unstacks the first two values on the stack, adds them together and stacks the result
sub: Unstacks the first two values on the stack, substracts them and stacks the result
mul: Unstacks the first two values on the stack, multiplies them and stacks the result
div: Unstacks the first two values on the stack, divides them and stacks the result
mod: Unstacks the first two values on the stack, calculates the modulus and stacks the result
print: Assert that the value at the top of the stack is an 8-bit integer, then interprets it as an ASCII value and displays the corresponding character on the standard output
exit: Terminate the execution of the current rogram.

Grammar
The assembly language of AbstractVM is generated from the following grammar (# corresponds to the end of the input):

S := INSTR [SEP INSTR]* #

INSTR :=
	  push VALUE
	| pop
	| dump
	| assert VALUE
	| add
	| sub
	| mul
	| div
	| mod
	| print
	| exit

VALUE :=
     int8(N)
	| int16(N)
	| int32(N)
	| float(Z)
	| double(Z)
	
N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP :=  \n +