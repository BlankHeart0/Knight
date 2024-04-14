#pragma once

#include "System.h"
#include "Sword.h"

class Command
{
public:
    virtual ~Command(){}
    virtual void Excute()=0;
};



// draw
class Draw: public Command
{
public:
    void Excute();
};



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