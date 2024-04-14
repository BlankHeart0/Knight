# Exit

f()
{
    output "f1";
    #exit;
    output "f2";
    exit;
    output "f3";
}

main()
{
    output 1;
    #exit;
    f();
    #exit;
    output 2;
    exit;
    output 3;

    ret;
}