func	void,main
var		str,name(0)
load	r0,"Enter your name:"
output	r0
output	endline
input	name(0)
var		int,age(0)
load	r0,"Enter your age:"
output	r0
output	endline
input	age(0)
var		dec,height(0)
var		dec,weight(0)
load	r0,"Enter your height and weight:"
output	r0
output	endline
input	height(0)
input	weight(0)
var		bool,sex(0)
load	r0,"Enter your sex,1 is man,0 is woman:"
output	r0
output	endline
input	sex(0)
load	r0,"Your Information:"
output	r0
output	endline
load	r0,"Name:"
output	r0
load	r0,name(0)
output	r0
output	endline
load	r0,"Age:"
output	r0
load	r0,age(0)
output	r0
output	endline
load	r0,"Height:"
output	r0
load	r0,height(0)
output	r0
load	r0,"Weight:"
output	r0
load	r0,weight(0)
output	r0
output	endline
load	r0,sex(0)
cvt		bool,r0
jmpf	0,r0
load	r0,"Sex:MAN"
output	r0
output	endline
jmp		1
lable	0
load	r0,"Sex:WOMAN"
output	r0
output	endline
lable	1
ret		
