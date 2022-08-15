//
// Created by 86157 on 2022-06-15.
//

#ifndef EDITOR_TEST2_COMMON_H
#define EDITOR_TEST2_COMMON_H


#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <fstream>
using namespace std;

typedef vector<string> vectorStr;
typedef vector<int> vectorInt;
typedef unordered_map<string, int> Map;

const int unInit = -65536;

class Element {
public:
    string name;
    bool isVar;
    bool isSignal;
    bool isTmp;
public:
    Element();
    Element(string, bool, bool, bool);
    ~Element() = default;
};

class Operand {
public:
    string name;
    bool activity;
    bool isTmp;
    bool isNum;
public:
    Operand();
    Operand(string, bool, bool, bool);
    ~Operand() = default;
};

const Operand epsilon = Operand("_", false, false, false);

class Quaternary {
public:
    string Operator;
    Operand Value1;
    Operand Value2;
    Operand Result;
public:
    Quaternary();
    Quaternary(string, Operand, Operand, Operand);
    ~Quaternary() = default;
};

class BasicBlock {
public:
    vector<Quaternary> Blocks;
public:
};

enum token {
//keywords
    TK_CONST = 1,// const
    TK_INT,// int
    TK_VOID,// void
    TK_BREAK,// break
    TK_CONTINUE,// continue
    TK_ELSE,// else
    TK_IF,// if
    TK_RETURN,// return
    TK_WHILE,// while   9
    TK_FLOAT,
//identifier
    TK_ID = 20,// ID    20
    TK_NUM,// NUM       21
//operators
    TK_COMMA = 30,// ,
    TK_ASSIGN,// =
    TK_OR,// ||
    TK_AND,// &&
    TK_EQUAL,// ==
    TK_UNEQUAL,// !=
    TK_GREAT,// >
    TK_LESS,// <
    TK_GREAT_EQ,// >=
    TK_LESS_EQ,// <=
    TK_ADD,// +
    TK_SUB,// -
    TK_MUL,// *
    TK_DIV,// /
    TK_MOD,// %
    TK_NOT,// !
    TK_AND_BYTE,// &
    TK_OR_BYTE,// |
    TK_LPAREN,// (
    TK_RPAREN,// )
    TK_LBRACKET,// [
    TK_RBRACKET,// ]    51
//Punctuates
    TK_LBRACE ,// {
    TK_RBRACE,// }
    TK_SEMICOLON,// ;   54
    TK_NEWLINE = 60,// \n
//EOF
    TK_EOF// EOF
};


typedef pair<token, string> Token;

//读取进入数字
#define addDigit(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
//判断是否是十进制数
#define IsDigit(c) (c >= '0' && c <= '9')
//判断是否是八进制数
#define IsOcDigit(c) ((c >= '0' && c <= '7'))
//判断是否是十六进制数
#define Is0XDigit(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
//判断是否是合法的标识符或关键字命名首字符
#define IsLetter(c) ((c >= 'a' && c <= 'z') || (c == '_') || (c >= 'A' && c <= 'Z'))
//判断是否是合法命名中非第一个字符
#define IsNotFirstLetter(c) (IsLetter(c) || IsDigit(c) || c == '_')


#endif //EDITOR_TEST2_COMMON_H
