func	void,main
var		int,i(0)
load	r0,10
store	i(0),r0
lable	0
load	r0,i(0)
cvt		bool,r0
jmpf	1,r0
var		str,number_type(1)
load	r0,i(0)
load	r1,2
mod		r0,r1
load	r1,0
equ		r0,r1
cvt		bool,r0
jmpf	2,r0
load	r0,"EVEN"
store	number_type(1),r0
jmp		3
lable	2
load	r0,"ODD"
store	number_type(1),r0
lable	3
load	r0,i(0)
output	r0
load	r0,":"
load	r1,number_type(1)
add		r0,r1
output	r0
output	endline
load	r0,i(0)
load	r1,1
sub		r0,r1
store	i(0),r0
jmp		0
lable	1
