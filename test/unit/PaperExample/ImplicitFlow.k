# ImplicitFlow.k

permission USE_NUMBER 
invoke NumLib:int<USE_NUMBER> GetSectreNumber()

main()
{
    int<USE_NUMBER> number; 
    number=NumLib.GetSectreNumber();
    
    if (number < 0)
        output "Negative";
    else
        output "Positive";
    
    ret;
}

