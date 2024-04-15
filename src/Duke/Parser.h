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

unique_ptr<Command> Parse_Byebye  (string& arg);
unique_ptr<Command> Parse_Command (string& arg);
unique_ptr<Command> Parse_Clear   (string& arg);
unique_ptr<Command> Parse_Draw    (string& arg);
unique_ptr<Command> Parse_List    (string& arg);
unique_ptr<Command> Parse_Run     (string& arg);

static unordered_map<string,unique_ptr<Command>(*)(string&)> CommandParse_map
{
    {"byebye",Parse_Byebye},
    {"command",Parse_Command},
    {"clear",Parse_Clear},
    {"draw",Parse_Draw},
    {"list",Parse_List},
    {"run",Parse_Run}
};
