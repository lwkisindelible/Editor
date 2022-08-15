//
// Created by 86157 on 2022-06-16.
//

#ifndef EDITOR_TEST2_LEXICAL_H
#define EDITOR_TEST2_LEXICAL_H

#include <iostream>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include<fstream>
#include "common.h"
using namespace std;

enum{           //tval的枚举定义
    ftp=1,      //float
    btp=2,      //bool
    itp=3,      //int
    ctp=4,      //char
    atp=5,      //数组
    dtp=6,      //结构体
    vtp=7       //空
};

enum{           //cat的枚举定义
    vid=1,      //变量
    fid=2,      //函数
    tid=3,      //类型(struct,typedef)
    did=4,       //域(struct里的具体成
    vfid=5
};

struct typel;

struct ainfl    //数组表
{
    ainfl(int low,int up,typel *tp,int clen):low(low),up(up),tp(tp),len(clen){};
    int low;    //下界
    int up;     //上界
    typel* tp;  //类型指针
    int len;    //长度
};

struct infoR    //结构表的具体内容
{
    infoR(string name,int off,typel *tp):ID(name),off(off),tp(tp){};
    string ID;  //域名
    int off;    //区距
    typel *tp;  //类型指针
};

struct rinfl    //结构表
{
    vector<infoR> info;
};

struct pfinfl   //函数表
{
    vector<int> paramid;
    int paramNum=0;
};

struct addr     //附加信息表
{
    int len;
    int consl;
    int level;
    int off;
    pfinfl *p=nullptr;
};

struct typel    //类型表
{
    explicit typel(int t_tval):tval(t_tval){
        if(t_tval==dtp)
            r=new rinfl;
    };
    int tval;
    ainfl *a=nullptr;
    rinfl *r=nullptr;
};

struct synbl    //符号表
{
    synbl(string t_name,int t_tval,int t_cat):name(t_name),cat(t_cat){
        if(t_tval==itp||t_tval==ftp||t_tval==btp||t_tval==ctp||t_tval==vtp){
            switch (t_tval)
            {
                case itp:type=p_itp;break;
                case ftp:type=p_ftp;break;
                case btp:type=p_btp;break;
                case ctp:type=p_ctp;break;
                case vtp:type= nullptr;break;
            }
        }
        else type=new typel(t_tval);
    }

    string name;
    typel *type=nullptr;
    addr  *ad= nullptr;
    int cat;
    static typel *p_itp,*p_ftp,*p_btp,*p_ctp;           //基本类型的类型表，设置为静态成员节省空间
};



//符号表类
class symbolTable
{
public:

    vector<synbl> I;//主表
    unordered_map<string, int> I_unmap; //用哈希表查询/查重

    bool checkExist(const string& name){return I_unmap.count(name);};

    int addIdentifier(string name,int type,int cat);//为主表添加成员
    void setAinfl(int n,int low,int up,typel *tp,int clen){I[n].type->a=new ainfl(low,up,tp,clen);};//设置数组表,n为主表索引
    void addRinfl(int n,const string& name,int off,typel *tp){I[n].type->r->info.emplace_back(name,off,tp);};//为结构表添加成员，n为主表索引
    int findIdentifier(string s);//用名字寻找标识符，返回主表索引,若没有返回 -1
    void showMainTable();
    string chooseType(int tval);
    string chooseCat(int cat);
};

const vector<string> key_T = {"const","int","void","break","continue","else",
                          "if","return","while"};   //关键字

const vector<string> P_T = {",","=","||","&&","==","!=",">","<",
                          ">=","<=","+","-","*","/","%","!",
                          "&","|","(",")","[","]","{","}",";"};   //界符


/////////////////////////////////////////////////////////////////

class Lexical_analyze
{
public:
    int state_change();
    int record_word(int state);
    void analyze();
    void display();
    int reserve(vector<string> &v, const string& k);
    void showToken(const string& name);
    vector<Token>& RetTokenList(){return TokenList;};
    explicit Lexical_analyze(const string& name){
        infile=new ifstream(name,ios::in);
        if(!infile->is_open()) {
            cerr << "file " << name << " open error" << endl;
            exit(-1);
        }
    }
    vector<string>& RetI(){return this->I;}

    unordered_map<string, int> K{{"int", TK_INT}, {"void", TK_VOID}, {"break", TK_BREAK}, {"float", 4}, {"while", TK_WHILE}, {"do", 6}, {"struct", 7}, {"const", TK_CONST}, {"case", 9}, {"for", 10}, {"return", TK_RETURN}, {"if", TK_IF}, {"default", 13}, {"else", TK_ELSE},{"continue",TK_CONTINUE}};

    unordered_map<string, int> P{{"-", TK_SUB}, {"/", TK_DIV}, {"(", TK_LPAREN}, {")", TK_RPAREN}, {"==", TK_EQUAL}, {"<=", TK_LESS_EQ}, {"<", TK_LESS}, {"+", TK_ADD}, {"*", TK_MUL}, {">", TK_GREAT}, {"=", TK_ASSIGN}, {">=",TK_GREAT_EQ},{",", TK_COMMA}, {";", TK_SEMICOLON}, {"++", 14}, {"{", TK_LBRACE}, {"}", TK_RBRACE},{"[",TK_LBRACKET},{"]",TK_RBRACKET}};

    unordered_map<string, int> I_unmap;
    unordered_map<string, int> C1_unmap;
    unordered_map<string, int> C2_unmap;
    unordered_map<string, int> CT_unmap;
    unordered_map<string, int> ST_unmap;

    vector<string> I;  //标识符
    vector<string> C1; //常整数
    vector<string> C2; //常实数
    vector<string> CT; //字符常量
    vector<string> ST; //字符串常量

    symbolTable sym;

    vector<pair<string, int>> mytoken;
    vector<Token> TokenList;
    int state{};
    int clevel=0;
    int coff=0;
    int infunc= -1;
    int inarray=-1;
    char ch{};
    int alen=0;
    string s;
    ifstream *infile;
};



#endif //EDITOR_TEST2_LEXICAL_H
