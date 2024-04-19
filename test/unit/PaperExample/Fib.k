# Fib.k

int Fib(int n)
{
    if(n<=2)ret 1;
 
    ret Fib(n-1)+Fib(n-2);
}

main()
{
    int i:1;
    while(i<=10)
    {
        output "Fib(",i,"):",Fib(i);
        i=i+1;
    }
}