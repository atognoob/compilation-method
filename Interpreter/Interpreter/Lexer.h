#pragma once
#include <vector>
#include <map>
#include <iostream>
using namespace std;

enum SymbolType {           //Enum to define types of symbols
    Digit,                  //0-9
    Letter,                 //a-z, A-Z
    Operation,
    Space
};

SymbolType DefineSymbol(char& symbol);      //define the type of a symbol

enum TokenType {                //Enum to define types of tokens in the lexer
    Var = 1,   // a
    Const,     // k
    If,
    Then,
    Else,
    While,
    Do,
    In,
    Out,
    End,
    Begin,
    Mass,
    Plus,      //+
    Minus,     // -
    Div,       // /
    Mul,       // *
    Ass,       // =
    LRb,       // (
    RRb,       // )
    LSb,       // [
    RSb,       // ]
    Less,      // <
    Greater,   // >
    LessEqual, //<=
    GreaterEqual, //>=
    Equal,     // ==
    NotEqual,  // !=
    Semicolon, // ;
    LCb,       // {
    RCb,       // }
    Empty
};


class Token {
    string token;
    TokenType type;
    int position;       //position of the token in the input string
public:
    static map <string, TokenType> OperationType;
    Token(string& token, int& position);
    [[nodiscard]] const string& getToken() const;
    [[nodiscard]] TokenType getType() const;
    int getPosition() const;
    void GetInfo() const;
    bool DefineToken(SymbolType& symbol_type);
    bool DefineOperationType();
    void DefineLetterType();
};

class Lexer {
    vector <Token> TokenList;
    int position;
    string code;    // Chuỗi mã nguồn để phân tích
public:
    explicit Lexer(string& code);
    vector<Token> Analysis();
    void PrintTokenList();
};