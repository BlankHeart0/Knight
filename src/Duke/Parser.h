#pragma once

#include "System.h"
#include "Command.h"

class Parser
{
private:
    string command_str;

    string command_name;
    string arg;

public: 

    Parser(string command_str):command_str(command_str){}

    bool GetNameArg();
    unique_ptr<Command> GetCommand();
};

unique_ptr<Command> Parse_Byebye    (string& arg);
unique_ptr<Command> Parse_Command   (string& arg);
unique_ptr<Command> Parse_History   (string& arg);
unique_ptr<Command> Parse_Echo      (string& arg);
unique_ptr<Command> Parse_Again     (string& arg);
unique_ptr<Command> Parse_Clear     (string& arg);
unique_ptr<Command> Parse_Draw      (string& arg);
unique_ptr<Command> Parse_List      (string& arg);
unique_ptr<Command> Parse_Uninstall (string& arg);
unique_ptr<Command> Parse_Run       (string& arg);

static unordered_map<string,unique_ptr<Command>(*)(string&)> CommandParse_map
{
    {"byebye",Parse_Byebye},
    {"command",Parse_Command},
    {"history",Parse_History},
    {"echo",Parse_Echo},
    {"again",Parse_Again},
    {"clear",Parse_Clear},
    {"draw",Parse_Draw},
    {"list",Parse_List},
    {"uninstall",Parse_Uninstall},
    {"run",Parse_Run}
};
