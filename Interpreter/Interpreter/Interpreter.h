#pragma once
#include "Parser.h"
//The Interpreter class is responsible for interpreting the program code that has been parsed by the Parser class. 
// It performs mathematical operations, manages variables and arrays, and controls the flow of the program.
class Interpreter {
    Parser* ptr;            //Con tr? ??n ??i t??ng Parser ?? l?y d? li?u ?ã phân tích cú pháp.
    vector <Parser::PS_Element> not_stack;  //Stack ?? l?u tr? các ph?n t? trong quá trình di?n gi?i.
    int VarOrConst();
    void ChangeToConst(int& result);
    string key;         //Chu?i ?? l?u tr? tên bi?n ho?c m?ng hi?n t?i.
    int id;
public:

    int index;
    Interpreter(Parser& Data);
    void Interpretation(); //
    void ChooseOperation(Parser::PS_Element& operation);
    int TakeMassValue(string& s, int& c);
    void ChangeMassValue(int& value);
    void ResetMass();

    void in();
    void out();
    void solve(Parser::PS_Operation type);
    void ass();         //Thuc hien phép gán giá tri cho bien.
    void indexing();
    void compare(Parser::PS_Operation type);
    void t_transition();
    void f_transition();
};

void Shit(int number);