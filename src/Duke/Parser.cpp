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
        cout<<"Command Format: command [arg]"<<endl;
        return false;
    }
    return true;
}

unique_ptr<Command> Parser::GetCommand()
{
    if(CommandParse_map.find(command_name)==CommandParse_map.end())
    {
        if(command_name!="")
            cout<<"Unsupport Command: "<<command_name<<endl;
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

unique_ptr<Command> Parse_Uninstall (string& arg)
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
