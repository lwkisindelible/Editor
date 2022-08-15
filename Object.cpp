//
// Created by 86157 on 2022-06-16.
//

#include "Object.h"
Object::Object(vector<string> &I) {
    for(auto & i : I) {
        this->is_act_I.insert(pair<string,bool>(i,false));
    }
    RDL = "";
}

void Object::generate_obj(vector<Quaternary>& QT) {
    int len = (int)QT.size();
    int k = 0;
    for(int i = 0; i < len; i++){
        string w = QT[i].Operator;
        string B = QT[i].Value1.name;bool b = QT[i].Value1.activity;
        string C = QT[i].Value2.name;bool c = QT[i].Value2.activity;
        string A = QT[i].Result.name;bool a = QT[i].Result.activity;
        if(w == "Func"){
            this->obj_code.push_back(B + " PROC");
            fun_sem.push(B);
        }
        else if(w == "FuncEnd"){
            this->obj_code.push_back(fun_sem.top()+" ENDP");
            fun_sem.pop();
        }
        else if(w == "Ret"){
            //this->obj_code.push_back("MOV "+QT[i-1].Result.name+",AX");
            this->obj_code.emplace_back("RET");
        }
        else if(w == "+" || w == "-" || w == "*" || w == "/"){
            string s = (w == "+")?"ADD":(w == "-")?"SUB":(w == "*")?"MUL":"DIV";
            if(RDL.empty()){
                this->obj_code.push_back("MOV AX,"+B);
                this->obj_code.push_back(s.append(" AX,")+C);
                RDL = A;
            }
            else if(RDL == B){
                if(b){
                    this->obj_code.push_back("MOV "+B+",AX");
                    this->obj_code.push_back(s.append(" AX,")+C);
                }
                else{
                    this->obj_code.push_back(s.append(" AX,")+C);
                }
                RDL = A;
            }
            else if(RDL == C){
                if(c){
                    this->obj_code.push_back("MOV "+C+",AX");
                    this->obj_code.push_back(s.append(" AX,")+B);
                }
                else{
                    this->obj_code.push_back(s.append(" AX,")+B);
                }
            }
            else{
                this->obj_code.push_back("MOV "+RDL+",AX");
                this->obj_code.push_back("MOV AX,"+B);
                this->obj_code.push_back(s.append(" AX,")+C);
                RDL = A;
            }
        }
        else if(w == "="){
            if(RDL.empty()){
                this->obj_code.push_back("MOV AX,"+B);
            }
            else if(RDL == B){
                if(b) this->obj_code.push_back("MOV "+B+",AX");
            }
            else{
                this->obj_code.push_back("MOV "+RDL+",AX");
                this->obj_code.push_back("MOV AX,"+B);
            }
        }
        else if(w == ">" || w == "<" || w == ">=" || w == "<=" || w == "==" || w == "!=" ){
            //this->obj_code.push_back("MOV "+A+",AX");
            //this->obj_code.push_back("MOV AX,"+B);
            RDL = A;
            string s = (w == ">")?"JA":(w == "<")?"JB":(w == ">=")?"JAE":(w == "<=")?"JBE":(w == "==")?"JE":"JNE";
            string wh = (w == ">")?"JBE":(w == "<")?"JAE":(w == ">=")?"JB":(w == "<=")?"JA":(w == "==")?"JNE":"JE";
            if(QT[i+1].Operator == "if"){
                if(RDL.empty()){
                    this->obj_code.push_back("MOV AX,"+B);
                    this->obj_code.push_back("CMP AX,"+C);
                    this->obj_code.emplace_back(s.append(" ")+jmp[k]);
                    SEM.push(jmp[k++]);
                }
                else if(RDL == QT[i+1].Value1.name){
                    if(QT[i+1].Value1.activity){
                        this->obj_code.push_back("MOV AX,"+B);
                        this->obj_code.push_back("CMP AX,"+C);
                        this->obj_code.emplace_back(s.append(" ")+ jmp[k]);
                    }
                    else
                    {
                        this->obj_code.push_back("CMP AX,"+C);
                        this->obj_code.emplace_back(s.append(" ")+jmp[k]);
                    }
                    SEM.push(jmp[k++]);
                    RDL = "";
                }
            }
            else if(QT[i+1].Operator == "do"){
                if(RDL.empty()){
                    this->obj_code.push_back("MOV AX,"+B);
                    this->obj_code.push_back("CMP AX,"+C);
                    this->obj_code.emplace_back(wh.append(" ")+jmp[k]);
                    SEM.push(jmp[k++]);
                }
                else if(RDL == QT[i+1].Value1.name){
                    if(QT[i+1].Value1.activity){
                        this->obj_code.push_back("MOV AX,"+B);
                        this->obj_code.push_back("CMP AX,"+C);
                        this->obj_code.emplace_back(wh.append(" ")+ jmp[k]);
                    }
                    else
                    {
                        this->obj_code.push_back("CMP AX,"+C);
                        this->obj_code.emplace_back(wh.append(" ")+jmp[k]);
                    }
                    SEM.push(jmp[k++]);
                    RDL = "";
                }
            }
        }
        else if(w == "else"){
            this->obj_code.push_back("JMP "+ jmp[k]);
            this->obj_code.push_back(SEM.top()+":");
            SEM.pop();
            SEM.push(jmp[k++]);
        }
        else if(w == "ie"){
            this->obj_code.push_back(SEM.top()+":");
            SEM.pop();
        }
        else if(w == "we"){
            string n2 = SEM.top();SEM.pop();
            string n1 = SEM.top();SEM.pop();
            this->obj_code.push_back("JMP "+n1);
            this->obj_code.push_back(n2+":");
        }
        else if(w == "while"){
            this->obj_code.push_back(jmp[k]+":");
            SEM.push(jmp[k++]);
        }
    }
     //this->obj_code.push_back("LD "+ QT[len-3].Result.name + ",R");
}


void Object::show_obj() {
    cout << "----------object code----------" << endl;
    cout << "CSEG SEGMENT" << endl;
    for(auto& i: this->obj_code){
        cout << i << endl;
    }
    cout << "CSEG ENDS" << endl;
}