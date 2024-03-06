#include "VM.h"

VirtualMachine Steed;

void VirtualMachine::Initialize(string knightASM_file_name)
{
    file_manager.Initialize(knightASM_file_name);
    file_manager.Open();
}

void VirtualMachine::Load()
{
    cout<<"Loadding... ..."<<endl<<endl;

    string line_str=file_manager.ReadLine();
    while(line_str!="")
    {   
        Parser parser(line_str);
        main.instructions.push_back(parser.Parse());
        
        line_str=file_manager.ReadLine();
    }

    file_manager.Close();
}

void VirtualMachine::Run()
{
    cout<<"------Running------"<<endl;
    main.Excute();
}
