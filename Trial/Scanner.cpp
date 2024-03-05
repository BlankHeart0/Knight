#include "Scanner.h"

void Scanner::ScanTokens()
{
    while(!IsAtEnd())
    {
        start=current;
        ScanToken();
    }

    tokens.push_back(Token(CODE_EOF,"",Literal(),line));
}

void Scanner::ScanToken()
{
    char c=Advance();
    switch(c)
    {   
        //Separator
        case ';': AddToken(SEMICOLON);      break;
        case ',': AddToken(COMMA);          break;
        case ':': AddToken(COLON);          break;
        
        case '(': AddToken(LEFT_PAREN);     break;
        case ')': AddToken(RIGHT_PAREN);    break;
        case '{': AddToken(LEFT_BRACE);     break;
        case '}': AddToken(RIGHT_BRACE);    break;
        
        //Operator
        case '+': AddToken(PLUS);           break;
        case '-': AddToken(MINUS);          break;
        case '*': AddToken(STAR);           break;
        case '/': AddToken(SLASH);          break;
        case '%': AddToken(PERCENT);        break;

        case '=': AddToken(ASSIGN);         break;

        case '?': 
            if(Match('=')) AddToken(EQUAL); 
            else SCAN_ERROR("Only '?' is illegal");       
            break;
        case '!': 
            if(Match('=')) AddToken(NOT_EQUAL); 
            else SCAN_ERROR("Only '!' is illegal");       
            break;
        case '<': AddToken(Match('=')?LESS_EQUAL:LESS);         break;
        case '>': AddToken(Match('=')?GREATER_EQUAL:GREATER);   break;

        //Comment
        case '#':
            while(Peek()!='\n'&&!IsAtEnd())Advance();
            break;
        //@Todo: multiple lines

        //Blank
        case ' ': case '\r': case '\t':     break;
        case '\n':      line++;             break;

        //Constant string
        case '"': Scan_Str();               break;

        default:
        //Constant int decimal
        if(IsDigit(c)) Scan_Number();       
				
        //Identifier and Keyword
        else if(IsAlphaUnderline(c)) ScanIdentifierKeyword();
        

        else SCAN_ERROR("Unexpected character.");
        break;
    }
}



void Scanner::Scan_Number()
{
    current--;
    int part_int=0;

    double part_decimal=0;
    bool is_decimal=false;

    while(!IsAtEnd()&&IsDigit(Peek()))
    {
        part_int=part_int*10+Peek()-'0';
        Advance();
    }

    if(Peek()=='.'&&IsDigit(PeekNext()))
    {
        is_decimal=true;
        Advance();

        for(int i=1;!IsAtEnd()&&IsDigit(Peek());i++)
        {
            part_decimal+=(double)(Peek()-'0')/pow(10,i);
            Advance();
        }
    }

    if(is_decimal)AddToken(CONSTANT_DEC,(double)part_int+part_decimal);
    else AddToken(CONSTANT_INT,part_int);
}

void Scanner::Scan_Str()
{
    string value_string;

    while (!IsAtEnd()&&Peek()!='\n'&&Peek()!= '"')
    {
        value_string.push_back(NextChar());
    }

	if (Match('"')) AddToken(CONSTANT_STR,value_string);
	else SCAN_ERROR("Incomplete string.");
}

char Scanner::NextChar()
{
    if(Match('\\'))
    {
        if(Match('a'))return'\a';
        else if(Match('b'))return'\b';
        else if(Match('f'))return'\f';
        else if(Match('n'))return'\n';
        else if(Match('r'))return'\t';
        else if(Match('t'))return'\t';
        else if(Match('v'))return'\v';
        else if(Match('\\'))return'\\';
        else if(Match('\''))return'\'';
        else if(Match('"'))return'"';
        else if(Match('0'))return'\0';

        else SCAN_ERROR("Wrong escape character.");
    }

    //Ordinary character
    return Advance();
}



void Scanner::ScanIdentifierKeyword()
{
    while(!IsAtEnd()&&IsDigitAlphaUnderline(Peek()))Advance();
    string text=source.substr(start,current-start);
    
    auto it=Keyword_map.find(text);
    if(it==Keyword_map.end())AddToken(IDENTIFIER);
    else AddToken(it->second);
}



bool Scanner::IsAtEnd()
{
    return current>=source.size();
}

char Scanner::Advance()
{
    return source[current++];
}

bool Scanner::Match(char expected)
{
    if(IsAtEnd()||source[current]!=expected)return false;

    Advance();
    return true;
}

char Scanner::Peek()
{
    if(IsAtEnd())return '\0';
    return source[current];
}

char Scanner::PeekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current+1];
}


bool Scanner::IsDigit(char c)
{
    return c>='0'&&c<='9';
}

bool Scanner::IsAlphaUnderline(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')||c=='_';
}

bool Scanner::IsDigitAlphaUnderline(char c)
{
	return IsDigit(c) || IsAlphaUnderline(c);
}



void Scanner::AddToken(TokenType token_type,Literal literal)
{
    string lexeme=source.substr(start,current-start);
    tokens.push_back(Token(token_type,lexeme,literal,line));
}

void Scanner::AddToken(TokenType token_type)
{
    AddToken(token_type,Literal());
}

void Scanner::AddToken(TokenType token_type,int literal_int)
{
    AddToken(token_type,Literal(literal_int));
}

void Scanner::AddToken(TokenType token_type,double literal_dec)
{
    AddToken(token_type,Literal(literal_dec));
}

void Scanner::AddToken(TokenType token_type,string literal_str)
{
    AddToken(token_type,Literal(literal_str));
}



void Scanner::Tokens_PrintTable()
{
    cout << "  Line\tType\t\tLexeme\t\tLiteral" << endl<<endl;
	for (Token& token : tokens)
	{
		cout << "  " << token.line << "\t" << TokenType_text[token.token_type] << "\t";
		if (TokenType_text[token.token_type].size() < 8)cout << "\t";
		cout<< token.lexeme;
		if (token.literal.is_valid)
		{
			cout << "\t\t";
			switch (token.token_type)
			{
				case CONSTANT_INT:cout << token.literal.literal_int; break;
                case CONSTANT_DEC:cout << token.literal.literal_dec; break;
				case CONSTANT_STR:cout << token.literal.literal_str; break;
			}
		}
		else cout << "\t\tNULL";
		cout << endl;
	}
    cout<<endl;
}