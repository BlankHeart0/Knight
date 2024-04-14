# IO

main()
{
    str name;
    output "Enter your name:";
    input name;

    int age;
    output "Enter your age:";
    input age;

    dec height;
    dec weight;
    output "Enter your height and weight:";
    input height,weight;

    bool sex;
    output "Enter your sex,1 is man,0 is woman:";
    input sex;


    output "Your Information:";
    output "Name:",name;
    output "Age:",age;
    output "Height:",height,"Weight:",weight;
    
    if(sex)output "Sex:MAN";
    else output "Sex:WOMAN";
    
    ret;
}