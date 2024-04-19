# Key.k

permission USE_KEY

invoke HaveKey:str<USE_KEY> GetKey(str name)

main()
{
    output HaveKey.GetKey("PJD");
    
    ret;
}


