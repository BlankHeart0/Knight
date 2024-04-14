invoke	B,name
func	void,name
var		int,No(0)
trans	r0,x0
store	No(0),r0
load	r0,No(0)
output	r0
output	endline
load	r0,"I am A"
output	r0
output	endline
load	r0,2
trans	x0,r0
call	B.name
func	void,main
load	r0,1
trans	x0,r0
call	name
