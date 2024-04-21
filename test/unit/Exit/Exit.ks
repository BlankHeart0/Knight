func	f
load	r0,"f1"
output	r0
output	endline
load	r0,"f2"
output	r0
output	endline
exit	
load	r0,"f3"
output	r0
output	endline
func	main
load	r0,1
output	r0
output	endline
call	f
load	r0,2
output	r0
output	endline
exit	
load	r0,3
output	r0
output	endline
ret		
