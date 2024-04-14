# Add

int add1(int a,int b)
{
    ret a+b;
}

int add2(int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9,int x10)
{
    ret x1+x2+x3+x4+x5+x6+x7+x8+x9+x10;
}

dec add3(dec a,dec b)
{
    ret a+b;
}

main()
{
    output add1(1,add1(2,add1(1,2)));
    output add2(1,2,3,4,5,6,7,8,9,10);
    output add3(3.1415926,3.1415927);
}