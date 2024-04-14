# A

invoke B:name(int No)

name(int No)
{
    output No;
    output "I am A";
    B.name(2);
}

main()
{
    name(1);
}