#include "Parser.h"

bool Parser::GetNameArg()
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
        cout<<"Command Format: command [arg]";
        return false;
    }
    return true;
}

unique_ptr<Command> Parser::GetCommand()
{
    if(ParseCommand_map.find(command_name)==ParseCommand_map.end())
    {
        cout<<"Unsupport Command: "<<command_name<<endl;
        return nullptr;
    }
        
    return move(ParseCommand_map[command_name](arg));
}



unique_ptr<Command> Parse_Draw(string& arg)
{
    if(arg!="")
    {
        cout<<"Draw Usage: draw"<<endl;
        return nullptr;
    }

    unique_ptr<Draw> draw=make_unique<Draw>();

    return move(draw);
}

unique_ptr<Command> Parse_List(string& arg)
{
    return nullptr;
}