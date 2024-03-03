#include "CodeGenerator.h"

void CodeGenerator::CodeGen()
{
    abstract_syntax_tree.CodeGen();
}

void AST::CodeGen()
{
    cout<<"--- --- CodeGen Begin --- ---"<<endl;
    file_manager.Write("hello knight!\n");
    //translation_unit->CodeGen();
}

