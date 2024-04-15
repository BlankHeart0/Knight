#pragma once

#include "System.h"
#include "Sword.h"

static unordered_map<string,string> CommandUsage_map
{
    {"byebye","byebye"},
    {"command","command"},
    {"clear","clear"},
    {"draw","draw"},
    {"list","list [-pkg|-app]"},
    {"run","run application"}
};
void CommandUsage(string command);



class Command
{
public:
    virtual ~Command(){}
    virtual void Excute()=0;
};



// byebye
class Byebye: public Command
{
public:
    void Excute();
};

// command
class _Command: public Command
{
public:
    void Excute();
};

// clear
class Clear: public Command
{
public:
    void Excute();
};

// draw
class Draw: public Command
{
public:
    void Excute();
};

// list [-pkg|-app]
enum ListType
{
    L_ALL,L_PKG,L_APP
};

class List: public Command
{
public:
    ListType type;

    List():type(L_ALL){}
    List(ListType type):type(type){}

    void Excute();
};

//run
class Run: public Command
{
public:
    string application;

    Run(string application):application(application){}
    void Excute();
};