## BMI.k
-- This is a test
-- You can calculate bmi by this program
##

permission Look_BMI

str<Look_BMI> GetBMIResult(dec Height,dec Weight)
{
    dec BMI:Weight/Height/Height;

    str<Look_BMI> result;
    if(BMI<18.5)
        result="Thin";
    else if(BMI<=24.5)
        result="Healthy";
    else
        result="Fat";

    ret "\t"+result;
}

main()
{
    str name;
    int age:0;
    bool sex:false;     # false is woman,true is man
    dec height;
    dec weight;
    
    output "Please input your:";
    output "-- Name\n","-- Age\n","-- Sex\n","-- Height\n","-- Weight";
    input name,age,sex,height,weight;

    output "Please wait 3 seconds... ...";
    sleep 3;

    output GetBMIResult(height,weight);
}

