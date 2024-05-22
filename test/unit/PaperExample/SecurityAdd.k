#SecurityAdd.k
permission USE_A,USE_B

int<USE_A,USE_B> SecurityAdd(int<USE_A> a,int<USE_B> b)
{
    ret a+b;
}

main()
{
    output SecurityAdd(1,1);
}

