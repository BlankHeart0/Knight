perm	Look_BMI,1
func	str,GetBMIResult
var		dec,Height(0)
var		dec,Weight(0)
trans	r0,x0
store	Height(0),r0
trans	r0,x1
store	Weight(0),r0
var		dec,BMI(0)
load	r0,Weight(0)
load	r1,Height(0)
div		r0,r1
load	r1,Height(0)
div		r0,r1
store	BMI(0),r0
var		str,result(0)
load	r0,BMI(0)
load	r1,18.5
les		r0,r1
cvt		bool,r0
jmpf	0,r0
load	r0,"Thin"
store	result(0),r0
jmp		1
lable	0
load	r0,BMI(0)
load	r1,24.5
lequ	r0,r1
cvt		bool,r0
jmpf	2,r0
load	r0,"Healthy"
store	result(0),r0
jmp		3
lable	2
load	r0,"Fat"
store	result(0),r0
lable	3
lable	1
load	r0,"\t"
load	r1,result(0)
add		r0,r1
trans	y,r0
ret		
func	void,main
var		str,name(0)
var		int,age(0)
load	r0,0
store	age(0),r0
var		bool,sex(0)
load	r0,false
store	sex(0),r0
var		dec,height(0)
var		dec,weight(0)
load	r0,"Please input your:"
output	r0
output	endline
load	r0,"-- Name\n"
output	r0
load	r0,"-- Age\n"
output	r0
load	r0,"-- Sex\n"
output	r0
load	r0,"-- Height\n"
output	r0
load	r0,"-- Weight"
output	r0
output	endline
input	name(0)
input	age(0)
input	sex(0)
input	height(0)
input	weight(0)
load	r0,"Please wait 3 seconds... ..."
output	r0
output	endline
sleep	3
load	r0,height(0)
load	r1,weight(0)
trans	x0,r0
trans	x1,r1
call	GetBMIResult
trans	r0,y
test	r1,<Look_BMI>
jmpf	0,r1
output	r0
lable	0
output	endline
