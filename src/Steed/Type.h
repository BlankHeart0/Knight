#pragma once

#include "System.h"

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