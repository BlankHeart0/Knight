perm	USE_NUMBER,0
invoke	NumLib,GetSectreNumber
func	main
var		int,number(0)
call	NumLib.GetSectreNumber
trans	r0,y
test	r1,<USE_NUMBER>
jmpf	0,r1
store	number(0),r0
lable	0
load	r0,number(0)
load	r1,0
les		r0,r1
test	r1,<USE_NUMBER>
jmpf	1,r1
cvt		bool,r0
jmpf	2,r0
load	r0,"Negative"
output	r0
output	endline
jmp		3
lable	2
load	r0,"Positive"
output	r0
output	endline
lable	3
lable	1
ret		

