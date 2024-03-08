# CS204_project

The project converts an assembly code to machine instructions.
The input file with assembly instructions should be named "input_file.asm"
The "output.mc" file contains the machine code
The instructions should conatain instructions in the following format :

.data // if data segment is present
label(optional): .directive(word,half,byte,dword,asciiz) immediate value(in decimal only) // the immediate values can be more than one for an array
for asciiz the string should be enclosed in "" double quotes

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
