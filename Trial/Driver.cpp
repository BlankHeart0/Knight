#include "System.h"
#include "FileManager.h"
#include "Scanner.h"
#include "Parser.h"
#include "CodeGenerator.h"

void Usage()
{
    cout<<"Usage: trial knight_file "<<endl;
}

void Trial()
{
    //Scan
    Scanner scanner(file_manager.source);
    scanner.ScanTokens();
    scanner.Tokens_PrintTable();

    //Parse
    Parser parser(scanner.tokens);
    parser.Parse();
    parser.abstract_syntax_tree.Print();

    //CodeGen
    CodeGenerator code_generator(parser.abstract_syntax_tree);
    code_generator.CodeGen();
}

int main(int argc,char* argv[])
{
    if(argc!=2)Usage();
    else 
    {
        file_manager.Initialize(argv[1]);
        file_manager.Open();
        file_manager.Load();
        Trial();
    }
    return 0;
}