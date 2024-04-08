#pragma once

#include "System.h"
#include "Type.h"
#include "Register.h"
#include "CodeGenerator.h"

class DataTypeChecker
{
public:
    // Assignment
    static void Check_Store(DataType data,int r_i,int line);
    
    // Logic
    static void Check_Or(int r1_i,int r2_i,int line);
    static void Check_And(int r1_i,int r2_i,int line);
    static void Check_Not(int r_i,int line);
    static void Check_Equal(int r1_i,int r2_i,int line);
    static void Check_NotEqual(int r1_i,int r2_i,int line);
    static void Check_Less(int r1_i,int r2_i,int line);
    static void Check_LessEqual(int r1_i,int r2_i,int line);
    static void Check_Greater(int r1_i,int r2_i,int line);
    static void Check_GreaterEqual(int r1_i,int r2_i,int line);

    // Arithmetic
    static void Check_Add(int r1_i,int r2_i,int line);
    static void Check_Sub(int r1_i,int r2_i,int line);
    static void Check_Mul(int r1_i,int r2_i,int line);
    static void Check_Div(int r1_i,int r2_i,int line);
    static void Check_Mod(int r1_i,int r2_i,int line);
    static void Check_Neg(int r_i,int line);
};
