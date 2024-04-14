# Recursive

int Factorial(int n)
{
    if(n?=0)ret 1;

    ret Factorial(n-1)*n;
}

int Fibonacci(int n)
{
    if(n<=2)ret 1;
 
    ret Fibonacci(n-1)+Fibonacci(n-2);
}

main()
{
    int i:1;
    while(i<=10)
    {
        output " -----xxx----- i",i," -----xxx-----";
        output "Factorial(",i,"):",Factorial(i)," Fibonacci(",i,"):",Fibonacci(i);

        i=i+1;
    }
}

