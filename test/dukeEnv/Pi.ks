perm	SECRET,0
func	main
var		dec,normal_pi(0)
load	r0,3.14
store	normal_pi(0),r0
var		dec,secret_pi(0)
load	r0,3.1415926
test	r1,<SECRET>
jmpf	0,r1
store	secret_pi(0),r0
lable	0
load	r0,"Normal Pi:"
output	r0
load	r0,normal_pi(0)
output	r0
output	endline
load	r0,"Secret Pi:"
output	r0
load	r0,secret_pi(0)
test	r1,<SECRET>
jmpf	1,r1
output	r0
lable	1
output	endline
