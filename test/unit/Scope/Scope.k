# Scope
main()
{
    int a:123;
    output "scope0:",a;

    {
        output "scope1:",a;
        int a:-999;
        output "scope1:",a;

        {        
            a=-a;
            output "scope2:",a;

            str a:"Hello";
            output "scope2:",a;
        }
    }

}