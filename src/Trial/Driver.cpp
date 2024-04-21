#include "System.h"
#include "FileManager.h"
#include "Diagnostor.h"
#include "Scanner.h"
#include "Parser.h"
#include "CodeGenerator.h"

enum CompileType
{
    C_LASM,  C_UASM,
    C_TOKEN, C_AST
};

void Usage()
{
    cout<<"Usage: trial [-LUTA] knight_file "<<endl;
    cout<<"-------------------->>> option <<<--------------------"<<endl;
    cout<<"-L: Compile to lower-case KnightAssembly file (default)"<<endl;
    cout<<"-U: Compile to upper-case KnightAssembly file"<<endl;
    cout<<"-T: Scan the code, print tokens"<<endl;
    cout<<"-A: Parse the code, print abstract syntax tree"<<endl;

    exit(0);
}

void Trial(CompileType type)
{
    if(type==C_LASM)is_upper=false;
    else if(type==C_UASM)is_upper=true;

    //Scan
    Scanner scanner(file_manager.source);
    scanner.ScanTokens();
    if(type==C_TOKEN)
    {
        scanner.Tokens_PrintTable();
        
        file_manager.Close();
        file_manager.Remove();
        return;
    }

    //Parse
    Parser parser(scanner.tokens);
    parser.Parse();
    if(type==C_AST)
    {
        abstract_syntax_tree.Print();

        file_manager.Close();
        file_manager.Remove();
        return;
    }

    //CodeGen
    CodeGenerator code_generator;
    code_generator.CodeGen();
}

int main(int argc,char* argv[])
{
    string input_file_name;
    string option;
    CompileType type;

    switch(argc)
    {
        case 2:
            input_file_name=argv[1];
            type=C_LASM;
            break;
        case 3:
            option=argv[1];
            input_file_name=argv[2];
            if(option=="-L")type=C_LASM;
            else if(option=="-U")type=C_UASM;
            else if(option=="-T")type=C_TOKEN;
            else if(option=="-A")type=C_AST;
            else Usage();
            break;
        default:
            Usage();
            break;
    }

    file_manager.Initialize(input_file_name);
    file_manager.Open();
    file_manager.Load();
    Trial(type);
    
    return 0;
}