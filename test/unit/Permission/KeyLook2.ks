perm	USE_KEY,0
invoke	HaveKey,GetKey
func	main
load	r0,"PJD"
trans	x0,r0
call	HaveKey.GetKey
trans	r0,y
test	r1,<USE_KEY>
jmpf	0,r1
output	r0
lable	0
output	endline
ret		
