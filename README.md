# CS204_project

The project converts an assembly code to machine instructions.
The input file with assembly instructions should be named "input_file.asm"
The "output.mc" file contains the machine code
The instructions should conatain instructions in the following format :

.data // if data segment is present
label(optional): .directive(word,half,byte,dword,asciiz) immediate value(in decimal only) // the immediate values can be more than one for an array
for asciiz the string should be enclosed in "" double quotes
for an array different values should be seperated by a delimiter


.text //necessay if data segment is present to differentiate between instructions
R_format instructions:
  Instruction_name register1,register2,register3 //there should not be extra spaces
I_format instructions:
  Instruction_name register1,register2,immediate_value(only in decimal- 12 bits only)
S_format instructions:
  Instruction_name register1,offset(register2) //the offset should be in decimal with 12 bits
SB_format instructions:
  Instruction_name register1,register2,immediate_value(in decimal - containing the 1-12 bits) or a label defined in the code
U_format instructions:
  Instruction_name register1,immediate_value(only in decimal containing the upper 20 bits)
UJ_format instructions:
  Instruction_name register1,immediate_value(in decimal - 20 bits only) or a label

 Instructions should be written in seperate lines without any gap in between them
 Pseudo instructions are not allowed
 For stack pointer use x2 and not sp
 There should not be extra spaces in between the lines or in the beginning of the line

 In the output file , for the data segment the instructions are mentioned as
 address value_given
 for eg:
 "arr: .word 123" will give "0x10000000 0x7B"
 But for .asciiz the values are shown for each byte
 "arr: .asciiz "abcd"" the output will be:
 0x10000000 0x61
 0x10000001 0x62
 0x10000002 0x63
 0x10000003 0x64

 To run the program , make the input file and compile the code by running the command "g++ main.cpp" 
 Make sure that g++ version is 12 or above
 After compiling , run the executable file "a.exe" for windows and "./a.out" for max/linux
 
