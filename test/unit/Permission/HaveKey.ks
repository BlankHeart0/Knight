perm	USE_KEY,0
func	str,GetKey
var		str,name(0)
trans	r0,x0
store	name(0),r0
var		str,key(0)
load	r0,""
store	key(0),r0
load	r0,name(0)
load	r1,"PJD"
equ		r0,r1
cvt		bool,r0
jmpf	0,r0
load	r0,"123456"
store	key(0),r0
lable	0
load	r0,key(0)
trans	y,r0
ret		
func	void,main
lable	0
load	r0,1
cvt		bool,r0
jmpf	1,r0
load	r0,"HaveKey Running..."
output	r0
output	endline
jmp		0
lable	1
ret		
