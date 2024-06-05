#pragma once
#include "Lexer.h"
#include <unordered_map>
#include <string>
#include "stack"
using namespace std;

class Parser {
public:
    enum class PS_Type          // Enum định nghĩa các loại của PS_Element
    {
        Var,
        Const,
        Operation,
        Empty
    };

    enum class PS_Operation {
        In,
        Out,
        Mass,
        Plus, //+
        Minus, // -
        Div, // /
        Mul, // *
        Ass, // =
        Less, // <
        Greater, // >
        LessEqual, // <=
        GreaterEqual, // >=
        Equal, // ==
        NotEqual, // !=
        T, // unconditional transition
        F, // conditional transition
        I, // indexing
        Empty
    };


    struct PS_Element {         //lưu trữ thông tin về một phần tử PS
        string PS_Element_Name;
        PS_Type PS_Element_Type = PS_Type::Empty;
        PS_Operation PS_Element_Operation = PS_Operation::Empty;
        int position = -1; // for errors
        int num = 0;

        PS_Element(string name, const Token& T)
        {
            PS_Element_Type = PS_Type::Var;
            PS_Element_Name = name;
            position = T.getPosition();
        }
        PS_Element(int con, const Token& T)
        {
            PS_Element_Type = PS_Type::Const;
            num = con;
            position = T.getPosition();
        }
        PS_Element(PS_Operation operation, const Token& T)
        {
            PS_Element_Type = PS_Type::Operation;
            PS_Element_Operation = operation;
            position = T.getPosition();
        }
        PS_Element(const PS_Element& other) {
            this->position = other.position;
            this->PS_Element_Type = other.PS_Element_Type;
            this->num = other.num;
            this->PS_Element_Operation = other.PS_Element_Operation;
            this->PS_Element_Name = other.PS_Element_Name;
        }
    };

    void PrintPolishString();       // Hàm in chuỗi Ba Lan
    struct Data {
        vector <PS_Element> Polish_String;  // Chuỗi Ba Lan
        unordered_map<string, int> Var_Map;  // Bản đồ biến
        unordered_map<string, vector<int>> Mass_Map;  // Bản đồ mảng
    };

    Data Get_data();    // Hàm lấy dữ liệu
    void Run();         // Hàm chạy parser
    Parser(vector <Token> List);    // Hàm tạo

    enum class Maps
    {
        Mass,
        Var
    };

private:    
    void Next_State();              // Hàm chuyển trạng thái
    void Run_Generator_program(); // Hàm chạy chương trình generator
    // Enum định nghĩa các trạng thái của parser
    enum class State
    {
        A, // → beginMS end
        M, // → mass a[k];M | λ
        S, // → aH = Q;B | λ
        Q, // → (Q)F’T’ | aHF’T’ | kF’T’ | in(aH)F’T’
        T_tilda, // → +TT’ | -TT’ | λ
        T, // → (Q)F’ | aHF’ | kF’ | in(aH)F’
        F_tilda, // → *FF’ | \FF’ | λ
        F, // → (Q) | aH | k | in(aH)
        H, // → [Q] | λ
        B, // → mass a[k];B | aH = Q;B | if (C) then {SB}EB | while (C) do {SB}B | out(aH);B | λ
        E, // → else {S} | λ
        C, // → aHG
        G, // → < Q | > Q | == Q |  != Q
        Z, // →  λ
        Empty
    }; 
 
    // Enum định nghĩa các chương trình generator
    enum class Generator_program
    {
        Empty,
        Var,
        Const,
        In,
        Out,
        Mass,
        Plus, //+
        Minus, // -
        Div, // /
        Mul, // *
        Ass, // =
        Less, // <
        Greater, // >
        LessEqual,
        GreaterEqual,
        Equal, // ==
        NotEqual, // !=
        I, // indexing
        Program1,
        Program2,
        Program3,
        Program4,
        Program5,
        Program6,
        Program7,
        Program8,
        Program9,
        Program10
    };
    //lưu trữ một mục của stack
    struct Stack_item {
        bool Is_terminal;      // Để xác định phần tử này có phải là terminal hay không
        TokenType token;       // Loại token nếu là terminal
        State state;           // Trạng thái nếu là non-terminal

        // Hàm tạo cho terminal
        Stack_item(TokenType token) : Is_terminal(true), token(token), state(State::Empty) {};

        // Hàm tạo cho non-terminal
        Stack_item(State state) : Is_terminal(false), token(TokenType::Empty), state(state) {};
    };

    Generator_program current_program;
    Token current_token;
    State current_state;
    Maps current_map;
    string current_var_name;
    stack<Stack_item> Automate_Stack;               //Quản lý các trạng thái và token hiện tại của bộ phân tích cú pháp.
    stack<Generator_program> Automate_Generator;    //Xác định các hành động cụ thể cần thực hiện tại mỗi trạng thái hoặc khi gặp các token nhất định.
    stack<int> Labels;                              //Giữ các vị trí trong chuỗi Ba Lan để xử lý các cấu trúc điều khiển.
    //if - else và while.
    
    vector<Token> input_data;
public:
    Data data;

};






//push(x) : Thêm phần tử x vào đỉnh của stack.
//pop() : Loại bỏ phần tử trên cùng của stack.
//top() : Trả về giá trị của phần tử trên cùng mà không loại bỏ nó.
//empty() : Kiểm tra stack có rỗng hay không.
//size() : Trả về số lượng phần tử trong stack.

//stack là một cấu trúc dữ liệu trong lập trình, 
//hoạt động theo nguyên tắc LIFO (Last In, First Out), tức là phần tử được đưa vào sau cùng sẽ được lấy ra trước. 