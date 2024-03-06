#include "System.h"
#include "VM.h"

void Usage()
{
    cout<<"Usage: steed knightASM_file "<<endl;
}

int main(int argc,char* argv[])
{
    if(argc!=2)Usage();
    else 
    {
        Steed.Initialize(argv[1]);
        Steed.Load();
        Steed.Run();
    }

    return 0;
}