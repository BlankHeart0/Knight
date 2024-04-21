#include "VM.h"

VirtualMachine Steed;

void VirtualMachine::Initialize(string knightASM_file_name)
{
    file_manager.Initialize(knightASM_file_name);
    file_manager.Open();
}

void VirtualMachine::Load()
{
    string line_str=file_manager.ReadLine();
    while(line_str!="")
    {   
        Parser parser(line_str);
        unique_ptr<Instruction> instruction=parser.Parse();

        //Directive
        if(instruction->is_directive)instruction->Excute();
        //Instruction
        else ParsingFunction().instructions.push_back(move(instruction));
        
        line_str=file_manager.ReadLine();
    }

    file_manager.Close();
}

void VirtualMachine::Run()
{
    pc.excuting_function="main";
    pc.instruction_id=0;
    is_stop=false;

    while(!is_stop)
    {
        if(pc.instruction_id<ExcutingFunction().instructions.size())
            ExcutingFunction().instructions[pc.instruction_id]->Excute();
        else if(pc.excuting_function!="main")
            function_stack.Pop();
        else is_stop=true;
    }
}

Function& VirtualMachine::ParsingFunction()
{
    return functions.Get(parsing_function);
}

Function& VirtualMachine::ExcutingFunction()
{
    return functions.Get(pc.excuting_function);
}
