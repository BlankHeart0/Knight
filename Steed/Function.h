#pragma once

#include "System.h"
#include "Instruction.h"

class Function
{
public:
    //string name;
    vector<Instruction*> instructions;
    
    void Excute();
};