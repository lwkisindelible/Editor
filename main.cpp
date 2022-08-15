#include"main.h"

int main(int argc, char* argv[]) {
    cout << "--- lexical analysis ---" << endl;
    Lexical_analyze Lex("main.c");//Scanner
    Lex.analyze();
    Lex.showToken("token.txt");
    Lex.display();
    //Lex.printToken();


    cout << endl;
    cout << "--- grammatical analysis ---" << endl;
    Parser p(Lex.RetTokenList());
    p.analyse();
    p.showQuaternary("qt.txt");

    Object ob(Lex.RetI());
    ob.generate_obj(p.RetQtSet());
    ob.show_obj();
//    symbolTable s;
//    s.showMainTable();
//

    return 0;
}
