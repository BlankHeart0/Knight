perm	USE_A,0
perm	USE_B,0
func	SecurityAdd
var		int,a(0)
var		int,b(0)
trans	r0,x0
test	r1,<USE_A>
jmpf	0,r1
store	a(0),r0
lable	0
trans	r0,x1
test	r1,<USE_B>
jmpf	1,r1
store	b(0),r0
lable	1
load	r0,a(0)
load	r1,b(0)
add		r0,r1
test	r1,<USE_B,USE_A>
jmpf	2,r1
trans	y,r0
lable	2
ret		
func	main
load	r0,1
load	r1,1
test	r2,<USE_A>
jmpf	0,r2
trans	x0,r0
lable	0
test	r0,<USE_B>
jmpf	1,r0
trans	x1,r1
lable	1
call	SecurityAdd
trans	r0,y
test	r1,<USE_B,USE_A>
jmpf	2,r1
output	r0
lable	2
output	endline
