func	main
var		int,a(0)
load	r0,123
store	a(0),r0
load	r0,"scope0:"
output	r0
load	r0,a(0)
output	r0
output	endline
load	r0,"scope1:"
output	r0
load	r0,a(0)
output	r0
output	endline
var		int,a(1)
load	r0,999
neg		r0
store	a(1),r0
load	r0,"scope1:"
output	r0
load	r0,a(1)
output	r0
output	endline
load	r0,a(1)
neg		r0
store	a(1),r0
load	r0,"scope2:"
output	r0
load	r0,a(1)
output	r0
output	endline
var		str,a(2)
load	r0,"Hello"
store	a(2),r0
load	r0,"scope2:"
output	r0
load	r0,a(2)
output	r0
output	endline
