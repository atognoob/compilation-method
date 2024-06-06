#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>

int main()
{
    string code;
    ifstream file("tests.txt");
    if (file.is_open())
    {
        while (getline(file, code))
        {
            cout << "\nCode: " << code << endl;
            Lexer program(code);
            vector<Token>List = program.Analysis();
            program.PrintTokenList();
            Parser ops(List);
            ops.Run();
            cout << endl;
            ops.PrintPolishString();
            
            Interpreter play(ops);
        }
    }
    file.close();
    return 0;
}