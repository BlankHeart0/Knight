#include "Parser.h"

bool CommandParser::GetNameArg()
{
    int size=command_str.size();
    int current=0;

    //Command name
    while(current<size&&isspace(command_str[current]))current++;
    int end=current;
    while(end<size&&!isspace(command_str[end]))end++;
    command_name=command_str.substr(current,end-current);
    current=end;

    //Arg
    while(current<size&&isspace(command_str[current]))current++;
    end=current;
    while(end<size&&!isspace(command_str[end]))end++;
    arg=command_str.substr(current,end-current);
    current=end;

    while(current<size&&isspace(command_str[current]))current++;
    if(current<size)
    {
        cout<<"Command Format: \033[96mcommand [arg]\033[0m"<<endl;
        return false;
    }
    return true;
}

unique_ptr<Command> CommandParser::GetCommand()
{
    if(CommandParse_map.find(command_name)==CommandParse_map.end())
    {
        if(command_name!="")
            cout<<"Unsupport Command: \033[96m"<<command_name<<"\033[0m"<<endl;
        return nullptr;
    }

    return move(CommandParse_map[command_name](arg));
}



unique_ptr<Command> Parse_Byebye(string& arg)
{
    if(arg!="")
    {
        CommandUsage("byebye");
        return nullptr;
    }

    unique_ptr<Byebye> byebye=make_unique<Byebye>();

    return move(byebye);
}

unique_ptr<Command> Parse_Command(string& arg)
{
    if(arg!="")
    {
        CommandUsage("command");
        return nullptr;
    }

    unique_ptr<_Command> command=make_unique<_Command>();

    return move(command);
}

unique_ptr<Command> Parse_History(string& arg)
{
    if(arg!="")
    {
        CommandUsage("history");
        return nullptr;
    }

    unique_ptr<History> history=make_unique<History>();

    return move(history);
}

unique_ptr<Command> Parse_Echo(string& arg)
{
    string something=arg;
    unique_ptr<Echo> echo=make_unique<Echo>(something);

    return move(echo);
}

unique_ptr<Command> Parse_Again(string& arg)
{
    if(arg!="")
    {
        CommandUsage("again");
        return nullptr;
    }

    unique_ptr<Again> again=make_unique<Again>();

    return move(again);
}

unique_ptr<Command> Parse_Clear(string& arg)
{
    if(arg!="")
    {
        CommandUsage("clear");
        return nullptr;
    }

    unique_ptr<Clear> clear=make_unique<Clear>();

    return move(clear);
}

unique_ptr<Command> Parse_Draw(string& arg)
{
    if(arg!="")
    {
        CommandUsage("draw");
        return nullptr;
    }

    unique_ptr<Draw> draw=make_unique<Draw>();

    return move(draw);
}

unique_ptr<Command> Parse_List(string& arg)
{
    if(arg=="")
    {
        unique_ptr<List> list=make_unique<List>();
        return move(list);
    }
    else if(arg=="-pkg")
    {
        unique_ptr<List> list_pkg=make_unique<List>(L_PKG);
        return move(list_pkg);
    }
    else if(arg=="-app")
    {
        unique_ptr<List> list_app=make_unique<List>(L_APP);
        return move(list_app);
    }

    CommandUsage("list");
    return nullptr;
}

unique_ptr<Command> Parse_Install(string& arg)
{
    if(arg=="")
    {
        CommandUsage("install");
        return nullptr;
    }

    string package=arg;
    unique_ptr<Install> install=make_unique<Install>(package);
    
    return move(install);
}

unique_ptr<Command> Parse_Uninstall(string& arg)
{
    if(arg=="")
    {
        CommandUsage("uninstall");
        return nullptr;
    }

    string application=arg;
    unique_ptr<Uninstall> uninstall=make_unique<Uninstall>(application);

    return move(uninstall);
}

unique_ptr<Command> Parse_Chperm(string& arg)
{
    if(arg=="")
    {
        CommandUsage("chperm");
        return nullptr;
    }

    string application=arg;
    unique_ptr<Chperm> chperm=make_unique<Chperm>(application);

    return move(chperm);
}

unique_ptr<Command> Parse_Run(string& arg)
{
    if(arg=="")
    {
        CommandUsage("run");
        return nullptr;
    }

    string application=arg;
    unique_ptr<Run> run=make_unique<Run>(application);

    return move(run);
}



InstructionParser::InstructionParser(string line_code)
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