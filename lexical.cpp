//
// Created by 86157 on 2022-06-16.
//

#include "lexical.h"
//初始化静态成员
typel* synbl::p_itp=new typel(itp);
typel* synbl::p_ftp=new typel(ftp);
typel* synbl::p_btp=new typel(btp);
typel* synbl::p_ctp=new typel(ctp);

string symbolTable::chooseType(int tval) {
    string t;
    switch (tval)
    {
        case itp:t+="itp";break;
        case vtp:t+="null";break;
        case atp:t+="atp";break;
    }
    return t;
}

string symbolTable::chooseCat(int cat){
    string t;
    switch (cat)
    {
        case vid:t+="v";break;
        case vfid:t+="vf";break;
        case fid:t+="func";break;
    }
    return t;
}

void symbolTable::showMainTable(){
    printf("-------------MainTable-------------\n");
    printf("name\t\ttype\t\tcat\n");



    for(int i=0;i<I.size();i++){
        printf("%s\t\t%s\t\t%s",I[i].name.c_str(), chooseType(I[i].type->tval).c_str(), chooseCat(I[i].cat).c_str());
        if(I[i].cat==vid||I[i].cat==vfid){
            printf("\taddr -> level:%d\toff:%d",I[i].ad->level,I[i].ad->off);
        }
        else if(I[i].cat==fid){
            printf("\taddr -> paramNum:%d\tparamId: ",I[i].ad->p->paramNum);
            for(int j=0;j<I[i].ad->p->paramNum;j++){
                printf("%d ",I[i].ad->p->paramid[j]);
            }
        }

        if(I[i].type->tval==atp){
            printf("\tAinfl -> low:%d\tup:%d\ttypel:itp\tlen:%d",I[i].type->a->low,I[i].type->a->up,I[i].type->a->len);
        }
        printf("\n");
    }
}

int symbolTable::addIdentifier(string name,int type,int cat){
    I.push_back(synbl(name,type,cat));
    I_unmap[name] = I.size()-1;
    return I.size()-1;
}

int symbolTable::findIdentifier(string s){
    if(!I_unmap.count(s)){
        return -1;
    }
    return I_unmap[s];
}
/////////////////////////////////////////////////////////
int Lexical_analyze::state_change()
{
    switch (state)
    {
        case 1:
            if (isalpha(ch) || ch == '_')
            {
                state = 2;
            }
            else if (ch == '0')
            {
                state = 24;
            }
            else if (isdigit(ch) && ch != '0')
            {
                state = 3;
            }
            else if (ch == '\'')
            {
                state = 9;
            }
            else if (ch == '\"')
            {
                state = 11;
            }
            else if (ch == '>')
            {
                state = 4;
            }
            else if (ch == '<')
            {
                state = 5;
            }
            else if (ch == '=')
            {
                state = 6;
            }
            else if (ch == '+')
            {
                state = 19;
            }
            else if (isspace(ch))
            {
                state = 1;
            }
            else if(ch=='/'){
                state=26;
            }
            else
            {
                string t;
                t += ch;
                if (P.count(t))
                {
                    state = 18;
                }
                else
                    state = -1;
            }

            break;

        case 2:
            if (isalnum(ch) || ch == '_')
            {
                state = 2;
            }
            else
                state = 0;
            break;

        case 3:
            if (isdigit(ch))
            {
                state = 3;
            }
            else if (ch == '.')
            {
                state = 8;
            }
            else if (ch == 'e')
            {
                state = 21;
            }
            else
                state = 0;
            break;

        case 4:
            // if (ch == '=')
            // {
            //     state = 13;
            // }
            // else
            state = 0;
            break;

        case 5:
            if (ch == '=')
            {
                state = 14;
            }
            else
                state = 0;
            break;

        case 6:
            if (ch == '=')
            {
                state = 15;
            }
            else
                state = 0;
            break;

        case 7:
            if (isdigit(ch))
            {
                state = 7;
            }
            else if (ch == 'e')
            {
                state = 21;
            }
            else
                state = 0;
            break;

        case 8:
            if (isdigit(ch))
            {
                state = 7;
            }
            break;

        case 9:
            if (isalpha(ch))
            {
                state = 10;
            }
            break;

        case 10:
            if (ch == '\'')
            {
                state = 16;
            }
            else
                state = -10;
            break;

        case 11:
            if (isalpha(ch))
            {
                state = 12;
            }
            break;

        case 12:
            if (isalpha(ch))
            {
                state = 12;
            }
            else if (ch == '\"')
            {
                state = 17;
            }
            break;

        case 13:
            state = 0;
            break;

        case 14:
            state = 0;
            break;

        case 15:
            state = 0;
            break;

        case 16:
            state = 0;
            break;

        case 17:
            state = 0;
            break;

        case 18:
            state = 0;
            break;

        case 19:
            if (ch == '+')
            {
                state = 20;
            }
            else
                state = 0;
            break;

        case 20:
            state = 0;
            break;

        case 21:
            if (ch == '+' || ch == '-')
            {
                state = 22;
            }
            else if (isdigit(ch))
            {
                state = 23;
            }
            break;

        case 22:
            if (isdigit(ch))
            {
                state = 23;
            }
            else
                state = -22;
            break;

        case 23:
            if (isdigit(ch))
            {
                state = 23;
            }
            else
                state = 0;
            break;

        case 24:
            if (ch == '.')
            {
                state = 8;
            }
            else if (ch == 'x' || ch == 'X')
            {
                state = 25;
            }
            else state=0;
            break;

        case 25:
            if (isalnum(ch))
            {
                state = 25;
            }
            else
                state = 0;
            break;

        case 26:
            if(ch=='/')
                state=27;
            else if(ch=='*')
                state=28;
            else state=0;
            break;

        case 27:
            if(ch=='\n')
                state=31;
            else state=27;
            break;

        case 28:
            if(ch=='*')
                state=29;
            else state=28;
            break;

        case 29:
            if(ch=='/')
                state=30;
            break;

        case 30:
            state=0;
            break;

        case 31:
            state=0;
            break;

    }

    return state;
}

int Lexical_analyze::record_word(int state)
{
    int flag = 1;
    switch (state)
    {
        case 2: // I or K
            if (K.count(s))
            {
                mytoken.emplace_back("K", K[s]);
                TokenList.emplace_back(static_cast<const token>(K[s]), s);
            }
            else if (I_unmap.count(s))
            {
                mytoken.emplace_back("I", I_unmap[s]);
                TokenList.emplace_back(TK_ID,s);
            }
            else
            {

                if(ch=='('){//处理函数名
                    coff=0;
                    int n=sym.addIdentifier(s,itp,fid);
                    sym.I[n].ad=new addr;
                    sym.I[n].ad->level=clevel;
                    sym.I[n].ad->p=new pfinfl;
                    infunc= n;
                }
                else if(ch=='['){//处理一维数组
                    int n=sym.addIdentifier(s,atp,vid);
                    sym.I[n].ad=new addr;
                    sym.I[n].ad->level=clevel;
                    sym.I[n].ad->off=coff;
                    inarray=n;
                }
                else{//处理基本类型变量
                    if(infunc== -1)//非函数参数
                    {
                        int n=sym.addIdentifier(s,itp,vid);
                        sym.I[n].ad=new addr;
                        sym.I[n].ad->level=clevel;
                        sym.I[n].ad->off=coff;
                        coff+=4;
                    }
                    else{//函数参数
                        int n=sym.addIdentifier(s,itp,vfid);
                        sym.I[n].ad=new addr;
                        sym.I[n].ad->level=clevel+1;
                        sym.I[n].ad->off=coff;
                        coff+=4;

                        sym.I[infunc].ad->p->paramNum++;
                        sym.I[infunc].ad->p->paramid.emplace_back(n);
                    }

                }

                I.push_back(s);
                I_unmap[s] = I.size();
                mytoken.emplace_back("I", I_unmap[s]);
                TokenList.emplace_back(TK_ID,s);
            }
            break;

        case 3: // int
            if (C1_unmap.count(s))
            {
                mytoken.emplace_back("C1", C1_unmap[s]);
                TokenList.emplace_back(TK_NUM,s);
            }
            else
            {
                C1.push_back(s);
                C1_unmap[s] = C1.size();
                mytoken.emplace_back("C1", C1_unmap[s]);
                TokenList.emplace_back(TK_NUM,s);
            }
            if(inarray!=-1)
                alen= stoi(s);
            break;

        case 4: //'>'
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 5: //'<'
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 6: //'='
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 13: //'>='
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 14: //'<='
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 15: //'=='
            mytoken.push_back(make_pair("P", P[s]));
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 7: // float
            if (C2_unmap.count(s))
            {
                mytoken.emplace_back("C2", C2_unmap[s]);
            }
            else
            {
                C2.push_back(s);
                C2_unmap[s] = (int)C2.size();
                mytoken.emplace_back("C2", C2_unmap[s]);
            }
            break;

        case 16: // CT
            s.erase(s.begin());
            s.erase(--s.end());
            if (CT_unmap.count(s))
            {
                mytoken.emplace_back("CT", CT_unmap[s]);
            }
            else
            {
                CT.push_back(s);
                CT_unmap[s] = (int)CT.size();
                mytoken.emplace_back("CT", CT_unmap[s]);
            }
            break;

        case 17: // ST
            s.erase(s.begin());
            s.erase(--s.end());
            if (ST_unmap.count(s))
            {
                mytoken.emplace_back("ST", ST_unmap[s]);
            }
            else
            {
                ST.push_back(s);
                ST_unmap[s] = (int)ST.size();
                mytoken.emplace_back("ST", ST_unmap[s]);
            }
            break;

        case 18:
            if(s=="{") clevel++;
            else if(s=="}") clevel--;
            if(s==")") infunc=-1;
            if(s=="]"){
                if(inarray!=-1){
                    sym.setAinfl(inarray,0,alen-1,synbl::p_itp,alen);
                    coff+=4*alen;
                }
                inarray=-1;
            }
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 19:
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 20:
            mytoken.emplace_back("P", P[s]);
            TokenList.emplace_back(static_cast<const token>(P[s]), s);
            break;

        case 23: //科学计数
            if (C2_unmap.count(s))
            {
                mytoken.emplace_back("C2", C2_unmap[s]);
            }
            else
            {
                C2.push_back(s);
                C2_unmap[s] = (int)C2.size();
                mytoken.emplace_back("C2", C2_unmap[s]);
            }
            break;

        case 24:
            if (C1_unmap.count(s))
            {
                mytoken.emplace_back("C1", C1_unmap[s]);
                TokenList.emplace_back(TK_NUM, s);
            }
            else
            {
                C1.push_back(s);
                C1_unmap[s] = (int)C1.size();
                mytoken.emplace_back("C1", C1_unmap[s]);
                TokenList.emplace_back(TK_NUM, s);
            }
            break;

        case 25: //十六进制
            //转化为十进制
            int a;
            sscanf(s.c_str(), "%x", &a);
            char str[20];
            sprintf(str, "%d", a);
            s = str;

            if (C1_unmap.count(s))
            {
                mytoken.emplace_back("C1", C1_unmap[s]);
            }
            else
            {
                C1.push_back(s);
                C1_unmap[s] = (int)C1.size();
                mytoken.emplace_back("C1", C1_unmap[s]);
            }
            break;

        default:
            flag = 0;
    }

    return flag;
}

void Lexical_analyze::analyze()
{
    int before_state;
    state = 1;
    while (true)
    {
        //if (scanf("%c", &ch) == EOF)
        if(infile->peek()==EOF)
        {
            if (!record_word(state)&&state!=1)
            { //报错
                cout<<state<<endl;
                state = -1;
            };
            mytoken.emplace_back("EOF",0);
            TokenList.emplace_back(TK_EOF,"EOF");
            //cout<<state<<endl;
            s.clear();
            break;
        }
        else
        {
            infile->get(ch);
            before_state = state;
            state = state_change();
            if (state < 0)
            { //报错
                break;
            }
            else if (state && state != 1)
            {
                s += ch;
            }
            else
            {
                record_word(before_state);
                s.clear();
                state = 1;
                state = state_change();
                if (state < 0)
                { //报错
                    break;
                }
                if (state != 1)
                    s += ch;
            }
        }
    }
}

void Lexical_analyze::showToken(const string& name) {
    ofstream out;
    out.open(name);
    int len = (int)TokenList.size();
    for(int i = 0; i < len; ++i) {
        out << TokenList[i].first << ' ' << TokenList[i].second << endl;
    }
    sym.showMainTable();
}

void  Lexical_analyze::display() {
    int len = (int)TokenList.size();
    int i_c = 0, c1_c = 0;
    cout << "Token:" << endl;
    for(int i = 0; i < len; i++){
        if(TokenList[i].first >= 1 && TokenList[i].first <= 9){
            //K.push_back(TokenList[i].second);
            cout << "(K ," << TokenList[i].first << ")";
        }
        else if(TokenList[i].first == 20){
            int t = reserve(I,TokenList[i].second);
            bool wh = (t == -1);
            if(wh) {
                I.push_back(TokenList[i].second);
                i_c++;
            }
            cout << "(I ," << (wh?i_c:t) << ")";
        }
        else if(TokenList[i].first == 21){
            int t = reserve(C1,TokenList[i].second);
            bool wh = (t == -1);
            if(wh) {
                C1.push_back(TokenList[i].second);
                c1_c++;
            }
            cout << "(C1 ," << (wh?c1_c:t) << ")";
        }
        else if(TokenList[i].first >= 30 && TokenList[i].first <= 54){
            //P.push_back(TokenList[i].second);
            cout << "(P ," << TokenList[i].first - 29 << ")";
        }
        else if(TokenList[i].first >= 60){
            continue;
        }
        else{
            cout << "wrong!" << endl;
            exit(0);
        }
    }
    cout << endl;
    cout << "K:";
    for(const auto& i: key_T){
        cout << " " << i;
    }
    cout << endl;
    cout << "P:";
    for(const auto& i : P_T){
        cout << " " << i;
    }
    cout << endl;
    cout << "I:" ;
    for(const auto& i: I){
        cout << " " << i;
    }
    cout << endl;
    cout << "C1:";
    for(const auto& i: C1){
        cout << " " << i;
    }
}

//是否重复
int Lexical_analyze::reserve(vector<string> &v, const string& k){
    int len = (int)v.size();
    for(int i = 0; i < len; i++){
        if(v[i] == k) return i + 1;
    }
    return -1;
}