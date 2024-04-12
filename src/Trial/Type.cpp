#include "Type.h"

string PermissionSet::Str()
{
    string result="";
    result+="<";

    int i=0;
    for (string permission:permission_uset)
    {
        result+=permission;
        if(i<permission_uset.size()-1)
            result+=",";
        i++;
    }

    result+=">";
    return result;
}

void PermissionSet::InsertPermission(string permission)
{
    permission_uset.insert(permission);
}

bool PermissionSet::IsEmpty()
{
    return permission_uset.empty();
}

bool PermissionSet::HavePermission(string permission)
{
    return permission_uset.find(permission)!=permission_uset.end();
}

bool PermissionSet::Included(PermissionSet& permissions)
{
    bool is_included=true;

    for (string permission:permission_uset)
    {
        if (!permissions.HavePermission(permission))
        {
            is_included=false;
            break;
        }
    }

    return is_included;
}

PermissionSet PermissionSet::Intersection(PermissionSet& permissions)
{
    PermissionSet result_set;

    for (string permission:permission_uset)
    {
        if (permissions.HavePermission(permission))
            result_set.InsertPermission(permission);
    }

    return result_set;
}

PermissionSet PermissionSet::Union(PermissionSet& permissions)
{
    PermissionSet result_set;

    for (string permission:permission_uset)
        result_set.InsertPermission(permission);

    for(string permission:permissions.permission_uset)
        result_set.InsertPermission(permission);

    return result_set;
}

PermissionSet PermissionSet::operator - (PermissionSet& permissions)
{
    PermissionSet result_set;

    for (string permission:permission_uset)
    {
        if (!permissions.HavePermission(permission))
            result_set.InsertPermission(permission);
    }

    return result_set;
}

PermissionSet PermissionSet::operator + (PermissionSet& permissions)
{
    return Union(permissions);
}

void PermissionSet::operator += (PermissionSet& permissions)
{
    for(string permission:permissions.permission_uset)
    {
        this->InsertPermission(permission);
    }
}



string Type::Str()
{
    string result="";

    switch(data)
    {
        case D_INT: result+=(is_upper?"INT":"int");  break;
        case D_DEC: result+=(is_upper?"DEC":"dec");  break;
        case D_STR: result+=(is_upper?"STR":"str");  break;
        case D_BOOL:result+=(is_upper?"BOOL":"bool");break;
    }

    //result+=permissions.Str();

    return result;
}



void TypeAsToken::Print()
{
    cout<<data_token.lexeme;

    cout<<"<";
    for(int i=0;i<permissions_token.size();i++)
    {
        cout<<permissions_token[i].lexeme;
        if(i<permissions_token.size()-1)cout<<",";
    }
    cout<<">";
}

Type TypeAsToken::ToRealType()
{
    DataType data;
    switch(data_token.token_type)
    {
        case INT: data=D_INT; break;
        case DEC: data=D_DEC; break;
        case STR: data=D_STR; break;
        case BOOL:data=D_BOOL;break;
    }

    PermissionType permissions;
    for(Token t:permissions_token)
    {
        permissions.InsertPermission(t.lexeme);
    }

    return Type(data,permissions);
}

