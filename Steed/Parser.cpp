#include "Parser.h"

Instruction* Parser::Parse()
{   
    int current=0;

    // Opcode
    int end=current;
    while(isalpha(line_code[end]))end++;
    opcode_str=line_code.substr(current,end-current);

    //skip the space
    while(end<line_code.size()&&isspace(line_code[end]))
        end++;

    // Operand1
    current=end;
    while(end<line_code.size()&&line_code[end]!=',')end++;
    if(current<line_code.size())
        operand1_str=line_code.substr(current,end-current);

    // Operand2
    end++;
    current=end;
    while(end<line_code.size())end++;
    if(current<line_code.size())
        operand2_str=line_code.substr(current,end-current);


    return ParseInstruction_map[opcode_str](operand1_str,operand2_str);
}



// Operand
OperandConstant Parse_OperandConstant(string& operand_str)
{
    int current=0;

    // Number
    if(isdigit(operand_str[current]))
    {
        int part_int=0;
        double part_decimal=0;
        bool is_decimal=false;

        while(current<operand_str.size()
            &&isdigit(operand_str[current]))
        {
            part_int=part_int*10+operand_str[current]-'0';
            current++;
        }
        
        if(current<operand_str.size())
        {
            is_decimal=true;
            current++;
            for(int i=1;current<operand_str.size();i++,current++)
            {
                part_decimal+=(double)(operand_str[current]-'0')/pow(10,i);
            }
        }
        // Dec
        if(is_decimal)return OperandConstant((double)part_int+part_decimal);
        // Int
        else return OperandConstant(part_int);
    }

    // Bool
    if(operand_str=="true") return OperandConstant(true);
    else if(operand_str=="false")return OperandConstant(false);

    // Str
    return OperandConstant(operand_str.substr(1,operand_str.size()-2));
}

OperandRegister Parse_OperandRegister(string& operand_str)
{
    // get the register id
    int current=1;
    int register_i=0;
    while(current<operand_str.size()&&isdigit(operand_str[current]))
    {
        register_i=register_i*10+(operand_str[current]-'0');
        current++;
    }

    switch(operand_str[0])
    {
        case 'r': case 'R': return OperandRegister(R_General,register_i);
        case 'x': case 'X': return OperandRegister(X_Argument,register_i);
    }
    
    return OperandRegister(Y_Retvalue);
}

OperandType Parse_OperandType(string& operand_str)
{
    if(operand_str=="INT"||operand_str=="int")       return OperandType(D_INT);
    else if(operand_str=="DEC" ||operand_str=="dec") return OperandType(D_DEC);
    else if(operand_str=="STR" ||operand_str=="str") return OperandType(D_STR);
    else if(operand_str=="BOOL"||operand_str=="bool")return OperandType(D_BOOL);
    
    return OperandType();
}

OperandFunction Parse_OperandFunction(string& operand_str)
{
    string function_name=operand_str;

    return OperandFunction(function_name);
}

OperandVariable Parse_OperandVariable(string& operand_str)
{
    int current=0;
    //@Bug:I think it must have (
    while(operand_str[current]!='(')current++;
    string variable_name=operand_str.substr(0,current);
    //@Bug: Also ...
    current++;
    int scope_i=0;
    while(operand_str[current]!=')')
    {
        scope_i=scope_i*10+(operand_str[current]-'0');
        current++;
    }

    return OperandVariable(variable_name,scope_i);
}

OperandLable Parse_OperandLable(string& operand_str)
{
    int lable_id=stoi(operand_str);

    return OperandLable(lable_id);
}



// Instruction
// Variable
Instruction* Parse_Var(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandVariable operand2_variable=Parse_OperandVariable(operand2_str);

    Var* var=new Var(operand1_type,operand2_variable);
    
    return (Instruction*)var;
}

Instruction* Parse_Load(string& operand1_str,string& operand2_str)
{   
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    // LoadConstant
    if(isdigit(operand2_str[0])||operand2_str[0]=='\"'
         ||operand2_str=="true"||operand2_str=="false")
    {
        OperandConstant operand2_constant=Parse_OperandConstant(operand2_str);
        
        LoadConstant* load=new LoadConstant(operand1_register,operand2_constant);

        return (Instruction*)load;
    }

    // LoadVariable
    OperandVariable operand2_variable=Parse_OperandVariable(operand2_str);

    LoadVariable* load=new LoadVariable(operand1_register,operand2_variable);
    
    return (Instruction*)load;
}

Instruction* Parse_Store(string& operand1_str,string& operand2_str)
{
    OperandVariable operand1_variable=Parse_OperandVariable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Store* store=new Store(operand1_variable,operand2_register);
    
    return (Instruction*)store;
}

Instruction* Parse_Cvt(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Cvt* cvt=new Cvt(operand1_type,operand2_register);

    return (Instruction*)cvt;
}



// Function    
Instruction* Parse_Func(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandFunction operand2_function=Parse_OperandFunction(operand2_str);

    Func* func=new Func(operand1_type,operand2_function);

    return (Instruction*)func;
}

Instruction* Parse_Trans(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Trans* trans=new Trans(operand1_register,operand2_register);

    return (Instruction*)trans;
}

Instruction* Parse_Call(string& operand1_str,string& operand2_str)
{
    OperandFunction operand1_function=Parse_OperandFunction(operand1_str);

    Call* call=new Call(operand1_function);
    
    return (Instruction*)call;
}

Instruction* Parse_Ret(string& operand1_str,string& operand2_str)
{
    Ret* ret=new Ret();

    return (Instruction*)ret;
}

Instruction* Parse_Push(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    Push* push=new Push(operand1_register);

    return (Instruction*)push;
}

Instruction* Parse_Pop(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    Pop* pop=new Pop(operand1_register);

    return (Instruction*)pop;
}

Instruction* Parse_Print(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    Print* print=new Print(operand1_register);

    return (Instruction*)print;
}



// Control Flow
Instruction* Parse_Lable(string& operand1_str,string& operand2_str)
{
    OperandLable operand1_lable=Parse_OperandLable(operand1_str);

    Lable* lable=new Lable(operand1_lable);

    return (Instruction*)lable;
}

Instruction* Parse_Jmp(string& operand1_str,string& operand2_str)
{
    OperandLable operand1_lable=Parse_OperandLable(operand1_str);

    Jmp* jmp=new Jmp(operand1_lable);

    return (Instruction*)jmp;
}

Instruction* Parse_Jmpt(string& operand1_str,string& operand2_str)
{
    OperandLable    operand1_lable=Parse_OperandLable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Jmpt* jmpt=new Jmpt(operand1_lable,operand2_register);

    return (Instruction*)jmpt;
}

Instruction* Parse_Jmpf(string& operand1_str,string& operand2_str){
    OperandLable    operand1_lable=Parse_OperandLable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Jmpf* jmpf=new Jmpf(operand1_lable,operand2_register);

    return (Instruction*)jmpf;
}



// Binary
Instruction* Parse_Or(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Or* or_=new Or(operand1_register,operand2_register);

    return (Instruction*)or_;
}

Instruction* Parse_And(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    And* and_=new And(operand1_register,operand2_register);

    return (Instruction*)and_;
}

Instruction* Parse_Equ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Equ* equ=new Equ(operand1_register,operand2_register);

    return (Instruction*)equ;
}

Instruction* Parse_Nequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Nequ* nequ=new Nequ(operand1_register,operand2_register);

    return (Instruction*)nequ;
}

Instruction* Parse_Les(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Les* les=new Les(operand1_register,operand2_register);

    return (Instruction*)les;
}

Instruction* Parse_Lequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Lequ* lequ=new Lequ(operand1_register,operand2_register);

    return (Instruction*)lequ;
}

Instruction* Parse_Gre(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Gre* gre=new Gre(operand1_register,operand2_register);

    return (Instruction*)gre;
}

Instruction* Parse_Gequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Gequ* gequ=new Gequ(operand1_register,operand2_register);

    return (Instruction*)gequ;
}

Instruction* Parse_Add(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Add* add=new Add(operand1_register,operand2_register);

    return (Instruction*)add;
}

Instruction* Parse_Sub(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Sub* sub=new Sub(operand1_register,operand2_register);

    return (Instruction*)sub;
}

Instruction* Parse_Mul(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Mul* mul=new Mul(operand1_register,operand2_register);

    return (Instruction*)mul;
}

Instruction* Parse_Div(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Div* div=new Div(operand1_register,operand2_register);

    return (Instruction*)div;
}

Instruction* Parse_Mod(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    Mod* mod=new Mod(operand1_register,operand2_register);

    return (Instruction*)mod;
}



// Unary
Instruction* Parse_Neg(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    Neg* neg=new Neg(operand1_register);

    return (Instruction*)neg;
}

Instruction* Parse_Not  (string& operand1_str,string& operand2_str)
{    
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    Not* not_=new Not(operand1_register);

    return (Instruction*)not_;
}
