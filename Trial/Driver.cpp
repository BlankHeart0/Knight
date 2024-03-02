#include "System.h"
#include "Scanner.h"
#include "Parser.h"

void Usage()
{
    cout<<"Usage: trial knight_file "<<endl;
}

string Load(char* input_file_path)
{
    ifstream file;
    file.open(input_file_path,ios::in);
    if(!file.is_open())
    {
        cout<<"Open the code file error!"<<endl;
        exit(-1);
    }

    string source="";
    string buffer;
    while(getline(file,buffer))
    {
        source+=buffer;
        source+='\n';
    }
    
    file.close();

    return source;
}

void Compile(char* input_file_path)
{
    string code=Load(input_file_path);

    //Scan
    Scanner scanner(code);
    scanner.ScanTokens();
    scanner.Tokens_PrintTable();

    //Parse
    Parser parser(scanner.tokens);
    parser.Parse();
    parser.abstract_syntax_tree.Print();
}

int main(int argc,char* argv[])
{
    if(argc!=2)Usage();
    else Compile(argv[1]);

    return 0;
}