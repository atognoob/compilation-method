#include "Lexer.h"

SymbolType DefineSymbol(char& symbol) {     //xác định loại ký tự
    if (isdigit(symbol)) return Digit;
    if (isalpha(symbol)) return Letter;
    if (isspace(symbol)) return Space;
    return Operation;
}

Token::Token(string& token, int& position) {
    this->token = token;
    this->position = position;
    this->type = Empty;
}
map <string, TokenType> Token::OperationType{       //ánh xạ các từ khóa và toán tử đến loại token tương ứng
    {"if", If},
    {"then", Then},
    {"else", Else},
    {"while", While},
    {"do", Do},
    {"in", In},
    {"out", Out},
    {"end", End},
    {"begin", Begin},
    {"mass", Mass},
    {"+", Plus},
    {"-", Minus},
    {"/", Div},
    {"*", Mul},
    {"=", Ass},
    {"(", LRb},
    {")", RRb},
    {"[", LSb},
    {"]", RSb},
    {">", Greater},
    {"<", Less},
    {"<=", LessEqual},
    {">=", GreaterEqual},
    {"==", Equal},
    {"!=", NotEqual},
    {";", Semicolon},
    {"{", LCb},
    {"}", RCb}
};


const string& Token::getToken() const {     // Hàm lấy chuỗi token
    return token;
}
TokenType Token::getType() const {
    return type;
}
int Token::getPosition() const {
    return position;
}
void Token::GetInfo() const {
    cout << " token: " << token << " type: " << type << " position: " << position << endl;
}
bool Token::DefineToken(SymbolType& symbol_type) {      //xác định loại token dựa trên loại ký tự
    switch (symbol_type) {
        case Digit: this->type = Const; return true;
        case Letter: this->DefineLetterType(); return true;
        case Operation: if (this->DefineOperationType()) return true; else return false;;
        // In ra thông báo lỗi nếu loại ký tự không đúng
        default: cout << "\n symbol_type is incorrect in Token.Define()"; exit(0);
    }
}
bool Token::DefineOperationType() {
    if (OperationType.find(token) != OperationType.end()) {
        type = OperationType[token];
        return true;
    }
    return false;
}
void Token::DefineLetterType() {
    if (OperationType.find(token) != OperationType.end()) {
        type = OperationType[token];
        return;
    }
    type = Var;
}

Lexer::Lexer(string& code) {
    this->code = code;
    this->position = 0;
}
vector<Token> Lexer::Analysis() {
    string symbols;
    SymbolType symbol_type;

    while (position < code.length())
    {
        symbol_type = DefineSymbol(code[position]);     // Xác định loại ký tự hiện tại
        symbols.push_back(code[position]);              // Thêm ký tự hiện tại vào chuỗi ký tự tạm thời
        if (symbol_type == Space) {                     // Nếu ký tự hiện tại là khoảng trắng
            position++;                                 // Tăng vị trí lên 1
            symbols.clear();                            // Xóa chuỗi ký tự tạm thời

        }
        else {
            // Tiếp tục thêm các ký tự cùng loại vào chuỗi ký tự tạm thời
            while ((symbol_type == DefineSymbol(code[position + 1])) && (position < code.length() - 1)) {
                symbols.push_back(code[position + 1]);
                position++;
            }
            Token token(symbols, position);         // Tạo token mới với chuỗi ký tự tạm thời và vị trí hiện tại
            if (token.DefineToken(symbol_type)) {   // Xác định loại token
                TokenList.push_back(token);  // Thêm token vào danh sách token
                symbols.clear();        // Xóa chuỗi ký tự tạm thời
                position++;
            }
            else {
                bool res = false;
                while (!res) {
                    symbols.pop_back();     // Bỏ ký tự cuối cùng của chuỗi ký tự tạm thời
                    position--;
                    if (symbols.empty()) {
                        cout << "\n token_type is incorrect in position: " << ++position;
                        exit(0);
                    }
                    Token new_token(symbols, position);
                    res = new_token.DefineToken(symbol_type);
                    if (res)TokenList.push_back(new_token);
                }
                symbols.clear();
                position++;
            }
        }
    }
    return TokenList;     // Trả về danh sách các token
}
void Lexer::PrintTokenList() {
    for (const auto& token : TokenList) {
        token.GetInfo();
    }
}