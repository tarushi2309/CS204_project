.data
n: .word 3
.text
lui x10,65536
addi x10,x10,512 
addi x6,x0,10
addi x7,x0,11
addi x8,x0,12
jal x1,toh
jal x1,exit
toh:
addi x2,x2,-20
sw x1,0(x2)
sw x6,4(x2)
sw x7,8(x2)
sw x8,12(x2)
sw x11,16(x2)
addi x11,x11,-1
beq x11,x0,base
lw x6,4(x2)
lw x8,8(x2)
lw x7,12(x2)
jal x1,toh
lw x6,4(x2)
lw x7,8(x2)
lw x8,12(x2)
lw x11,16(x2)
add x9,x0,x11
add x9,x9,x6
add x9,x9,x7
sw x9,0(x10)
addi x10,x10,4
addi x11,x11,-1
lw x6,12(x2)
lw x8,4(x2)
lw x7,8(x2) 
jal x1,toh
lw x1,0(x2)
addi x2,x2,20
base:
add x9,x0,x6
add x9,x9,x7
addi x9,x9,256
sw x9,0(x10)
addi x10,x10,4
addi x2,x2,20
exit:
