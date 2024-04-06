#pragma once

#include "System.h"
#include "Token.h"

enum DataType
{
    D_INT,D_DEC,D_STR,D_BOOL
};

static vector<string> DataType_Text
{
    "D_INT","D_DEC","D_STR","D_BOOL"
};

class PermissionSet
{
private:
    unordered_set<string> permission_uset;

public:
    void Print();
    void InsertPermission(string permission);
    bool IsEmpty();
    bool HavePermission(string permission);
    bool Included(PermissionSet& permissions);
    PermissionSet Intersection(PermissionSet& permissions);
    PermissionSet Union(PermissionSet& permissions);
    PermissionSet operator - (PermissionSet& permissions);
    PermissionSet operator + (PermissionSet& permissions);
};

class Type
{
public:
    DataType data;
    PermissionSet permissions;

    Type(DataType data,PermissionSet permissions):
        data(data),permissions(permissions){}
};

class TypeAsToken
{
public:
    Token data_token;
    vector<Token> permissions_token;

    TypeAsToken(){}
    TypeAsToken(Token data_token,vector<Token> permissions_token):
        data_token(data_token),permissions_token(permissions_token){}
    
    void Print();
    Type ToRealType();
};
