#include "Parser.h"

Parser::Parser(string line_code)
{
    this->line_code=line_code;

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
}   

unique_ptr<Instruction> Parser::Parse()
{   
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

OperandPermission Parse_OperandPermission(string& operand_str)
{
    PermissionSet permissions;

    int begin=operand_str[0]=='<'?1:0;

    while(begin<operand_str.size())
    {
        int end=begin;
        while(end<operand_str.size()&&operand_str[end]!=','&&operand_str[end]!='>')
            end++;
        
        permissions.InsertPermission(operand_str.substr(begin,end-begin));
        begin=end+1;
    }

    return OperandPermission(permissions);
}

OperandApplication Parse_OperandApplication(string& operand_str)
{
    string app_name=operand_str;

    return OperandApplication(app_name);
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
// Type
unique_ptr<Instruction> Parse_Perm (string& operand1_str,string& operand2_str)
{
    OperandPermission operand1_permission=Parse_OperandPermission(operand1_str);
    OperandLable      operand2_lable=Parse_OperandLable(operand2_str);

    unique_ptr<Perm> perm=make_unique<Perm>(operand1_permission,operand2_lable);

    return move(perm);
}

unique_ptr<Instruction> Parse_Test (string& operand1_str,string& operand2_str)
{
    OperandRegister   operand1_register=Parse_OperandRegister(operand1_str);
    OperandPermission operand2_permission=Parse_OperandPermission(operand2_str);

    unique_ptr<Test> test=make_unique<Test>(operand1_register,operand2_permission);

    return move(test);
}

unique_ptr<Instruction> Parse_Cvt(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Cvt> cvt=make_unique<Cvt>(operand1_type,operand2_register);

    return move(cvt);
}



// Variable
unique_ptr<Instruction> Parse_Var(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandVariable operand2_variable=Parse_OperandVariable(operand2_str);

    unique_ptr<Var> var=make_unique<Var>(operand1_type,operand2_variable);
    
    return move(var);
}

unique_ptr<Instruction> Parse_Load(string& operand1_str,string& operand2_str)
{   
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    // LoadConstant
    if(isdigit(operand2_str[0])||operand2_str[0]=='\"'
         ||operand2_str=="true"||operand2_str=="false")
    {
        OperandConstant operand2_constant=Parse_OperandConstant(operand2_str);
        
        unique_ptr<LoadConstant> load=make_unique<LoadConstant>(operand1_register,operand2_constant);

        return move(load);
    }

    // LoadVariable
    OperandVariable operand2_variable=Parse_OperandVariable(operand2_str);

    unique_ptr<LoadVariable> load=make_unique<LoadVariable>(operand1_register,operand2_variable);
    
    return move(load);
}

unique_ptr<Instruction> Parse_Store(string& operand1_str,string& operand2_str)
{
    OperandVariable operand1_variable=Parse_OperandVariable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Store> store=make_unique<Store>(operand1_variable,operand2_register);
    
    return move(store);
}



// Function
unique_ptr<Instruction> Parse_Invoke(string& operand1_str,string& operand2_str)
{
    OperandApplication operand1_application=Parse_OperandApplication(operand1_str);
    OperandFunction    operand2_function=Parse_OperandFunction(operand2_str);

    unique_ptr<Invoke> invoke=make_unique<Invoke>(operand1_application,operand2_function);

    return move(invoke);
}

unique_ptr<Instruction> Parse_Func(string& operand1_str,string& operand2_str)
{
    OperandType     operand1_type=Parse_OperandType(operand1_str);
    OperandFunction operand2_function=Parse_OperandFunction(operand2_str);

    unique_ptr<Func> func=make_unique<Func>(operand1_type,operand2_function);

    return move(func);
}

unique_ptr<Instruction> Parse_Trans(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Trans> trans=make_unique<Trans>(operand1_register,operand2_register);

    return move(trans);
}

unique_ptr<Instruction> Parse_Call(string& operand1_str,string& operand2_str)
{
    OperandFunction operand1_function=Parse_OperandFunction(operand1_str);

    unique_ptr<Call> call=make_unique<Call>(operand1_function);
    
    return move(call);
}

unique_ptr<Instruction> Parse_Ret(string& operand1_str,string& operand2_str)
{
    unique_ptr<Ret> ret=make_unique<Ret>();

    return move(ret);
}

unique_ptr<Instruction> Parse_Exit(string& operand1_str,string& operand2_str)
{
    unique_ptr<Exit> exit=make_unique<Exit>();

    return move(exit);
}

unique_ptr<Instruction> Parse_Push(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    unique_ptr<Push> push=make_unique<Push>(operand1_register);

    return move(push);
}

unique_ptr<Instruction> Parse_Pop(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    unique_ptr<Pop> pop=make_unique<Pop>(operand1_register);

    return move(pop);
}

unique_ptr<Instruction> Parse_Input(string& operand1_str,string& operand2_str)
{
    OperandVariable operand1_variable=Parse_OperandVariable(operand1_str);

    unique_ptr<Input> input=make_unique<Input>(operand1_variable);

    return move(input);
}

unique_ptr<Instruction> Parse_Output(string& operand1_str,string& operand2_str)
{
    // OutputEndline
    if(operand1_str=="endline"||operand1_str=="ENDLINE")
    {
        unique_ptr<OutputEndline> print=make_unique<OutputEndline>();

        return move(print);
    }    

    // OutputRegister
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    unique_ptr<OutputRegister> print=make_unique<OutputRegister>(operand1_register);

    return move(print);
}



// Control Flow
unique_ptr<Instruction> Parse_Lable(string& operand1_str,string& operand2_str)
{
    OperandLable operand1_lable=Parse_OperandLable(operand1_str);

    unique_ptr<Lable> lable=make_unique<Lable>(operand1_lable);

    return move(lable);
}

unique_ptr<Instruction> Parse_Jmp(string& operand1_str,string& operand2_str)
{
    OperandLable operand1_lable=Parse_OperandLable(operand1_str);

    unique_ptr<Jmp> jmp=make_unique<Jmp>(operand1_lable);

    return move(jmp);
}

unique_ptr<Instruction> Parse_Jmpt(string& operand1_str,string& operand2_str)
{
    OperandLable    operand1_lable=Parse_OperandLable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Jmpt> jmpt=make_unique<Jmpt>(operand1_lable,operand2_register);

    return move(jmpt);
}

unique_ptr<Instruction> Parse_Jmpf(string& operand1_str,string& operand2_str){
    OperandLable    operand1_lable=Parse_OperandLable(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Jmpf> jmpf=make_unique<Jmpf>(operand1_lable,operand2_register);

    return move(jmpf);
}



// Binary
unique_ptr<Instruction> Parse_Or(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Or> or_=make_unique<Or>(operand1_register,operand2_register);

    return move(or_);
}

unique_ptr<Instruction> Parse_And(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<And> and_=make_unique<And>(operand1_register,operand2_register);

    return move(and_);
}

unique_ptr<Instruction> Parse_Equ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Equ> equ=make_unique<Equ>(operand1_register,operand2_register);

    return move(equ);
}

unique_ptr<Instruction> Parse_Nequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Nequ> nequ=make_unique<Nequ>(operand1_register,operand2_register);

    return move(nequ);
}

unique_ptr<Instruction> Parse_Les(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Les> les=make_unique<Les>(operand1_register,operand2_register);

    return move(les);
}

unique_ptr<Instruction> Parse_Lequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Lequ> lequ=make_unique<Lequ>(operand1_register,operand2_register);

    return move(lequ);
}

unique_ptr<Instruction> Parse_Gre(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Gre> gre=make_unique<Gre>(operand1_register,operand2_register);

    return move(gre);
}

unique_ptr<Instruction> Parse_Gequ(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Gequ> gequ=make_unique<Gequ>(operand1_register,operand2_register);

    return move(gequ);
}

unique_ptr<Instruction> Parse_Add(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Add> add=make_unique<Add>(operand1_register,operand2_register);

    return move(add);
}

unique_ptr<Instruction> Parse_Sub(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Sub> sub=make_unique<Sub>(operand1_register,operand2_register);

    return move(sub);
}

unique_ptr<Instruction> Parse_Mul(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Mul> mul=make_unique<Mul>(operand1_register,operand2_register);

    return move(mul);
}

unique_ptr<Instruction> Parse_Div(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Div> div=make_unique<Div>(operand1_register,operand2_register);

    return move(div);
}

unique_ptr<Instruction> Parse_Mod(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);
    OperandRegister operand2_register=Parse_OperandRegister(operand2_str);

    unique_ptr<Mod> mod=make_unique<Mod>(operand1_register,operand2_register);

    return move(mod);
}



// Unary
unique_ptr<Instruction> Parse_Neg(string& operand1_str,string& operand2_str)
{
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    unique_ptr<Neg> neg=make_unique<Neg>(operand1_register);

    return move(neg);
}

unique_ptr<Instruction> Parse_Not(string& operand1_str,string& operand2_str)
{    
    OperandRegister operand1_register=Parse_OperandRegister(operand1_str);

    unique_ptr<Not> not_=make_unique<Not>(operand1_register);

    return move(not_);
}
