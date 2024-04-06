#include "Type.h"

void PermissionSet::Print()
{
    cout<<permission_uset.size()<<" permissions: ";

    for (string permission:permission_uset)
        cout<<permission<<" ";

    cout<<endl;
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



void TypeAsToken::Print()
{
    cout<<data_token.lexeme;

    if(permissions_token.size()>0)
    {
        cout<<"<";
        for(int i=0;i<permissions_token.size();i++)
        {
            cout<<permissions_token[i].lexeme;
            if(i<permissions_token.size()-1)cout<<",";
        }
        cout<<">";
    }
    
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

    PermissionSet permissions;
    for(Token t:permissions_token)
    {
        permissions.InsertPermission(t.lexeme);
    }

    return Type(data,permissions);
}

