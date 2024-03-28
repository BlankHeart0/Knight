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
        Instruction* instruction=parser.Parse();

        //Directive
        if(instruction->is_directive)instruction->Excute();
        //Instruction
        else functions.LoadInstruction(nowInfunction,instruction);
        
        line_str=file_manager.ReadLine();
    }

    file_manager.Close();
}

void VirtualMachine::Run()
{
    cout<<"------Running------"<<endl<<endl;

    pc.function_name="main";
    pc.instruction_id=0;

    while(pc.instruction_id<NowExcuteFunction().instructions.size())
    {
        NowExcuteFunction().instructions[pc.instruction_id]->Excute();
    }

    cout<<"------ Done ------"<<endl<<endl;
}

Function& VirtualMachine::NowExcuteFunction()
{
    return functions.Get(pc.function_name);
}
