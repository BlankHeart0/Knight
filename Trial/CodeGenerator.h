#pragma once

#include "System.h"
#include "AbstractSyntaxTree.h"
#include "FileManager.h"

class CodeGenerator
{
public:
    AST abstract_syntax_tree;

    CodeGenerator(AST abstract_syntax_tree):
                      abstract_syntax_tree(abstract_syntax_tree){}

    void CodeGen();
};