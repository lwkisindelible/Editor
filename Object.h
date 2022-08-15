//
// Created by 86157 on 2022-06-16.
//

#ifndef EDITOR_TEST2_OBJECT_H
#define EDITOR_TEST2_OBJECT_H
#include <vector>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include "Parser.h"
using namespace std;
class Object {
public:
    Object(vector<string> &);
    void generate_obj(vector<Quaternary>&);
    void show_obj();
private:
    vector<string> obj_code;
    unordered_map<string,bool> is_act_I;
    string RDL;
    stack<string> SEM;
    string jmp[10] = {"N1","N2","N3","N4","N5","N6","N7","N8","N9"};
    stack<string> fun_sem;
};
enum REGIS{ AX = 0,BX,CX,DX };
typedef pair<REGIS, string> Reg;
#endif //EDITOR_TEST2_OBJECT_H
