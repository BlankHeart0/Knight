# HaveKey
permission USE_KEY

str<USE_KEY> GetKey(str name)
{
    str<USE_KEY> key:"";
    
    if(name?="PJD")key="123456";

    ret key;
}

main()
{
    while(1)
    {
        output "HaveKey Running...";
        sleep 1;
    }
    
    ret;
}