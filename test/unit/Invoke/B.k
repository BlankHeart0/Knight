# B

invoke C:name(int No)

name(int No)
{
    output No;
    output "I am B";
    C.name(3);
}

main()
{
    name(2);
}