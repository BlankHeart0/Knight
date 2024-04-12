#pragma once

#include "System.h"
#include "Token.h"
#include "Diagnostor.h"

enum DataType
{
    D_INT,D_DEC,D_STR,D_BOOL
};

class PermissionSet
{
private:
    unordered_set<string> permission_uset;

public:
    string Str();
    void InsertPermission(string permission);
    bool IsEmpty();
    bool HavePermission(string permission);
    bool Included(PermissionSet& permissions);
    PermissionSet Intersection(PermissionSet& permissions);
    PermissionSet Union(PermissionSet& permissions);
    PermissionSet operator - (PermissionSet& permissions);
    PermissionSet operator + (PermissionSet& permissions);
    void operator += (PermissionSet& permissions);
};

typedef PermissionSet PermissionType;

class Type
{
public:
    DataType data;
    PermissionType permissions;

    Type(){}
    Type(DataType data,PermissionType permissions):
        data(data),permissions(permissions){}

    string Str();
};

class TypeAsToken
{
public:
    bool is_valid;
    Token data_token;
    vector<Token> permissions_token;

    TypeAsToken():is_valid(false){}
    TypeAsToken(Token data_token,vector<Token> permissions_token):
        is_valid(true),data_token(data_token),permissions_token(permissions_token){}
    
    void Print();
    Type ToRealType();
};

#define TYPE_ERROR(error_message)                             \
        do{                                                   \
            diagnostor.Error(E_TYPE,line,error_message);      \
        }while(0)
