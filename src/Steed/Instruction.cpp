#include "Instruction.h"
#include "VM.h"

// Type
// perm permission N
void Perm::Excute()
{
    if(operand2_flag.N)
        Steed.program_permissions+=operand1_permission.permissions;
}

// test R permissions
void Test::Excute()
{
    int R_i=operand1_register.register_i;

    if(operand2_permission.permissions.Included(Steed.program_permissions))
    {
        general_register.Set(R_i,true);
    }
    else 
    {
        general_register.Set(R_i,false);
    }
    
    Steed.pc.instruction_id++;
}

// cvt type R
void Cvt::Excute()
{
    Register& R=general_register.Get(operand2_register.register_i);
    
    switch(R.data_type)
    {
        case D_INT:
            switch(operand1_type.data_type)
            {
                case D_INT:break;
                case D_DEC:
                    R.data_type=D_DEC;
                    R.DEC_val=(double)R.INT_val;
                    break;
                case D_STR:
                    diagnostor.Error(E_TYPE,"Convert int to str");
                    break;
                case D_BOOL:
                    R.data_type=D_BOOL;
                    R.BOOL_val=(bool)R.INT_val;
                    break;
            }
            break;

        case D_DEC:
            switch(operand1_type.data_type)
            {
                case D_INT:
                    R.data_type=D_INT;
                    R.INT_val=(int)R.DEC_val;
                    break;
                case D_DEC:break;
                case D_STR:
                    diagnostor.Error(E_TYPE,"Convert dec to str");
                    break;
                case D_BOOL:
                    R.data_type=D_BOOL;
                    R.BOOL_val=(bool)R.DEC_val;
                    break;
            }
            break;

        case D_STR:
            switch(operand1_type.data_type)
            {
                case D_INT:
                    diagnostor.Error(E_TYPE,"Convert str to int");
                    break;
                case D_DEC:
                    diagnostor.Error(E_TYPE,"Convert str to dec");
                    break;
                case D_STR:break;
                case D_BOOL:
                    diagnostor.Error(E_TYPE,"Convert str to bool");
                    break;
            }
            break;
        
        case D_BOOL:
            switch(operand1_type.data_type)
            {
                case D_INT:
                    diagnostor.Error(E_TYPE,"Convert bool to int");
                    break;
                case D_DEC:
                    diagnostor.Error(E_TYPE,"Convert bool to dec");
                    break;
                case D_STR:
                    diagnostor.Error(E_TYPE,"Convert bool to str");
                    break;
                case D_BOOL:break;
            }
            break;
    }

    Steed.pc.instruction_id++;
}



// Variable
// var type variable(N)
void Var::Excute()
{   
    VariableTable& variables=Steed.ExcutingFunction().variables;

    string name=operand2_variable.name;
    int scope_i=operand2_variable.scope_i;

    switch(operand1_type.data_type)
    {
        case D_INT: variables.Set(scope_i,name,int(0));     break;
        case D_DEC: variables.Set(scope_i,name,double(0.0));break;
        case D_STR: variables.Set(scope_i,name,string("")); break;
        case D_BOOL:variables.Set(scope_i,name,bool(false));break;
    }

    Steed.pc.instruction_id++;
}

// load R constant
void LoadConstant::Excute()
{
    int R_i=operand1_register.register_i;

    switch(operand2_constant.data_type)
    {
        case D_INT:
            general_register.Set(R_i,operand2_constant.INT_val);
            break;
        case D_DEC:
            general_register.Set(R_i,operand2_constant.DEC_val);
            break;
        case D_STR:
            general_register.Set(R_i,operand2_constant.STR_val);
            break;
        case D_BOOL:
            general_register.Set(R_i,operand2_constant.BOOL_val);
            break;
    }

    Steed.pc.instruction_id++;
}

// load R variable(N)
void LoadVariable::Excute()
{
    int R_i=operand1_register.register_i;

    Variable& variable=Steed.ExcutingFunction().variables.
        Get(operand2_variable.scope_i,operand2_variable.name);

    switch(variable.data_type)
    {
        case D_INT:
            general_register.Set(R_i,variable.INT_val);
            break;
        case D_DEC:
            general_register.Set(R_i,variable.DEC_val);
            break;
        case D_STR:
            general_register.Set(R_i,variable.STR_val);
            break;
        case D_BOOL:
            general_register.Set(R_i,variable.BOOL_val);
            break;
    }

    Steed.pc.instruction_id++;
}

// store variable(N) R
void Store::Excute()
{
    Register& R=general_register.Get(operand2_register.register_i);
    
    VariableTable& variables=Steed.ExcutingFunction().variables;
   
    string name=operand1_variable.name;
    int scope_i=operand1_variable.scope_i;

    switch(R.data_type)
    {
        case D_INT: variables.Set(scope_i,name,R.INT_val); break;
        case D_DEC: variables.Set(scope_i,name,R.DEC_val); break;
        case D_STR: variables.Set(scope_i,name,R.STR_val); break;
        case D_BOOL:variables.Set(scope_i,name,R.BOOL_val);break;
    }

    Steed.pc.instruction_id++;
} 



// Function
// invoke application function (directive)
void Invoke::Excute()
{
    FileManager app_file;
    app_file.Initialize(operand1_application.name);
    app_file.Open();

    bool isInTargetFunction=false;

    string line_str=app_file.ReadLine();
    while(line_str!="")
    {
        Parser parser(line_str);
        if(parser.opcode_str=="INVOKE"||parser.opcode_str=="invoke")
            parser.Parse()->Excute();

        if(parser.opcode_str=="FUNC"||parser.opcode_str=="func")
        {
            if(parser.operand1_str==operand2_function.name)
            {
                parser.operand1_str=operand1_application.name+"."+operand2_function.name;
                isInTargetFunction=true;
            }
            else isInTargetFunction=false;
        }

        if(isInTargetFunction)
        {
            unique_ptr<Instruction> instruction=parser.Parse();
            if(instruction->is_directive)instruction->Excute();
            else Steed.ParsingFunction().instructions.push_back(move(instruction));
        }

        line_str=app_file.ReadLine();
    }

    app_file.Close();
}

// func type function (directive)
void Func::Excute()
{
    Steed.functions.New(operand1_function.name);
    Steed.parsing_function=operand1_function.name;
}

/*
trans   X           R
trans   R           X
trans   Y           R
trans   R           Y 
*/
void Trans::Excute()
{
    int register1_i=operand1_register.register_i;
    RegisterType type1=operand1_register.register_type;

    int register2_i=operand2_register.register_i;
    RegisterType type2=operand2_register.register_type;

    if(type1==X_Argument&&type2==R_General)
    {
        argument_register.Set(register1_i,
            general_register.Get(register2_i));
    }
    else if(type1==R_General&&type2==X_Argument)
    {
        general_register.Set(register1_i,
            argument_register.Get(register2_i));
    }
    else if(type1==Y_Retvalue&&type2==R_General)
    {
        retvalue_register.Set(
            general_register.Get(register2_i));
    }
    else if(type1==R_General&&type2==Y_Retvalue)
    {
        general_register.Set(register1_i,
            retvalue_register);
    }

    Steed.pc.instruction_id++;
}

// call function
void Call::Excute()
{
    function_stack.Push();

    Steed.pc.excuting_function=operand1_function.name;
    Steed.pc.instruction_id=0;
}

// ret
void Ret::Excute()
{
    if(Steed.pc.excuting_function=="main")
    {
        Steed.is_stop=true;
        return;
    }

    function_stack.Pop();
}

// exit
void Exit::Excute()
{
    Steed.is_stop=true;
}

void Sleep::Excute()
{
    sleep(operand1_natural.N);

    Steed.pc.instruction_id++;
}

// push R
void Push::Excute()
{
    Register R=general_register.Copy(operand1_register.register_i);

    register_stack.Push(R);

    Steed.pc.instruction_id++;
}

// pop R
void Pop::Excute()
{
    Register& R=general_register.Get(operand1_register.register_i);

    register_stack.Pop(R);

    Steed.pc.instruction_id++;
}

// input variable(N)
void Input::Excute()
{
    VariableTable& variables=Steed.ExcutingFunction().variables;

    string name=operand1_variable.name;
    int scope_i=operand1_variable.scope_i;

    Variable& variable=variables.Get(scope_i,name);

    //@Bug:Have undefined behavior
    switch(variable.data_type)
    {
        case D_INT: cin>>variable.INT_val; break;
        case D_DEC: cin>>variable.DEC_val; break;
        case D_STR: cin>>variable.STR_val; break;
        case D_BOOL:cin>>variable.BOOL_val;break;
    }

    Steed.pc.instruction_id++;
}

// output R
void OutputRegister::Excute()
{
    Register& R=general_register.Get(operand1_register.register_i);
    switch(R.data_type)
    {
        case D_INT: cout<<R.INT_val;                  break;
        case D_DEC: cout<<R.DEC_val;                  break;
        case D_STR: cout<<R.STR_val;                  break;
        case D_BOOL:cout<<(R.BOOL_val?"true":"false");break;
    }

    Steed.pc.instruction_id++;
}

// output endline
void OutputEndline::Excute()
{
    cout<<endl;

    Steed.pc.instruction_id++;
}



// Control Flow
// lable N (directive)
void Lable::Excute()
{
    Steed.ParsingFunction().lables[operand1_lable.N]=
        Steed.ParsingFunction().instructions.size();
}

// jmp N
void Jmp::Excute()
{
    Steed.pc.instruction_id=
        Steed.ExcutingFunction().lables[operand1_lable.N];
}

// jmpt N R
void Jmpt::Excute()
{
    Register& R=general_register.Get(operand2_register.register_i);
    if(R.BOOL_val)
    {
        Steed.pc.instruction_id=
            Steed.ExcutingFunction().lables[operand1_lable.N];
    }
    else Steed.pc.instruction_id++;
}

// jmpf N R
void Jmpf::Excute()
{
    Register& R=general_register.Get(operand2_register.register_i);
    if(!R.BOOL_val)
    {
        Steed.pc.instruction_id=
            Steed.ExcutingFunction().lables[operand1_lable.N];
    }
    else Steed.pc.instruction_id++;
}



// Binary
// or R R
void Or::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);

    R1.BOOL_val=R1.BOOL_val||R2.BOOL_val;

    Steed.pc.instruction_id++;
}

// and R R
void And::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    R1.BOOL_val=R1.BOOL_val&&R2.BOOL_val; 

    Steed.pc.instruction_id++;
}

// equ R R
void Equ::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val ==R2.INT_val; break;
        case D_DEC: R1.BOOL_val=R1.DEC_val ==R2.DEC_val; break;
        case D_STR: R1.BOOL_val=R1.STR_val ==R2.STR_val; break;
        case D_BOOL:R1.BOOL_val=R1.BOOL_val==R2.BOOL_val;break;
    }
    R1.data_type=D_BOOL;

    Steed.pc.instruction_id++;
}

// nequ R R
void Nequ::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val !=R2.INT_val; break;
        case D_DEC: R1.BOOL_val=R1.DEC_val !=R2.DEC_val; break;
        case D_STR: R1.BOOL_val=R1.STR_val !=R2.STR_val; break;
        case D_BOOL:R1.BOOL_val=R1.BOOL_val!=R2.BOOL_val;break;
    }
    R1.data_type=D_BOOL;

    Steed.pc.instruction_id++;
}

// les R R
void Les::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val<R2.INT_val;break;
        case D_DEC: R1.BOOL_val=R1.DEC_val<R2.DEC_val;break;
    }
    R1.data_type=D_BOOL; 

    Steed.pc.instruction_id++;
}

// lequ R R
void Lequ::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val<=R2.INT_val;break;
        case D_DEC: R1.BOOL_val=R1.DEC_val<=R2.DEC_val;break;
    }
    R1.data_type=D_BOOL;

    Steed.pc.instruction_id++;
}

// gre R R
void Gre::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val>R2.INT_val;break;
        case D_DEC: R1.BOOL_val=R1.DEC_val>R2.DEC_val;break;
    }
    R1.data_type=D_BOOL; 

    Steed.pc.instruction_id++;
}

// gequ R R
void Gequ::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT: R1.BOOL_val=R1.INT_val>=R2.INT_val;break;
        case D_DEC: R1.BOOL_val=R1.DEC_val>=R2.DEC_val;break;
    }
    R1.data_type=D_BOOL;  

    Steed.pc.instruction_id++;
}

// add R R
void Add::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT:R1.INT_val+=R2.INT_val;break;
        case D_DEC:R1.DEC_val+=R2.DEC_val;break;
        case D_STR:R1.STR_val+=R2.STR_val;break;
    }

    Steed.pc.instruction_id++;
}

// sub R R
void Sub::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT:R1.INT_val-=R2.INT_val;break;
        case D_DEC:R1.DEC_val-=R2.DEC_val;break;
    }

    Steed.pc.instruction_id++;
}

// mul R R
void Mul::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT:R1.INT_val*=R2.INT_val;break;
        case D_DEC:R1.DEC_val*=R2.DEC_val;break;
    }

    Steed.pc.instruction_id++;
}

// div R R
void Div::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    switch(R1.data_type)
    {
        case D_INT:R1.INT_val/=R2.INT_val;break;
        case D_DEC:R1.DEC_val/=R2.DEC_val;break;
    }

    Steed.pc.instruction_id++;
}

// mod R R
void Mod::Excute()
{
    Register& R1=general_register.Get(operand1_register.register_i);
    Register& R2=general_register.Get(operand2_register.register_i);
    
    R1.INT_val%=R2.INT_val;

    Steed.pc.instruction_id++;
}



// Unary
// neg R
void Neg::Excute()
{
    Register& R=general_register.Get(operand1_register.register_i);

    switch(R.data_type)
    {
        case D_INT:R.INT_val=-R.INT_val;break;
        case D_DEC:R.DEC_val=-R.DEC_val;break;
    }

    Steed.pc.instruction_id++;
}

// not R
void Not::Excute()
{
    Register& R=general_register.Get(operand1_register.register_i);

    R.BOOL_val=!R.BOOL_val;

    Steed.pc.instruction_id++;
}