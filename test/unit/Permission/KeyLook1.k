# KeyLook1
permission USE_KEY

str<USE_KEY> GetKey(str name)
{
    str<USE_KEY> key:"";
    
    if(name?="PJD")key="123456";

    ret key;
}

main()
{
    output GetKey("PJD");
    
    ret;
}

