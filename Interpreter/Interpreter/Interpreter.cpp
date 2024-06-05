#include "Interpreter.h"
#define OPS ptr->data.Polish_String

Interpreter::Interpreter(Parser& Data) {
    this->ptr = &Data;
    index = 0;
    this->ResetMass();
    this->Interpretation();
}
void Interpreter::Interpretation() {
    for (; index < OPS.size(); ++index) {
        switch (OPS[index].PS_Element_Type) {
        case Parser::PS_Type::Var:
            not_stack.push_back(OPS[index]);
            break;
        case Parser::PS_Type::Const:
            not_stack.push_back(OPS[index]);
            break;
        case Parser::PS_Type::Operation:
            this->ChooseOperation(OPS[index]);
            break;
        default: Shit(0);
        }
    }
}
void Interpreter::ChooseOperation(Parser::PS_Element& operation) {
    switch (operation.PS_Element_Operation) {
    case Parser::PS_Operation::In: this->in(); break;
    case Parser::PS_Operation::Out: this->out(); break;
    case Parser::PS_Operation::Plus: this->solve(Parser::PS_Operation::Plus); break;
    case Parser::PS_Operation::Minus: this->solve(Parser::PS_Operation::Minus); break;
    case Parser::PS_Operation::Div: this->solve(Parser::PS_Operation::Div); break;
    case Parser::PS_Operation::Mul: this->solve(Parser::PS_Operation::Mul); break;
    case Parser::PS_Operation::Ass: this->ass(); break;
    case Parser::PS_Operation::Less: this->compare(Parser::PS_Operation::Less); break;
    case Parser::PS_Operation::Greater: this->compare(Parser::PS_Operation::Greater); break;
    case Parser::PS_Operation::LessEqual: this->compare(Parser::PS_Operation::LessEqual); break;
    case Parser::PS_Operation::GreaterEqual: this->compare(Parser::PS_Operation::GreaterEqual); break;
    case Parser::PS_Operation::Equal: this->compare(Parser::PS_Operation::Equal); break;
    case Parser::PS_Operation::NotEqual: this->compare(Parser::PS_Operation::NotEqual); break;
    case Parser::PS_Operation::I: this->indexing(); break;
    case Parser::PS_Operation::T: this->t_transition(); break;
    case Parser::PS_Operation::F: this->f_transition(); break;
    case Parser::PS_Operation::Mass: not_stack.pop_back(); break;
    default: Shit(0);
    }
}

int Interpreter::VarOrConst() {
    if (not_stack.back().PS_Element_Type == Parser::PS_Type::Var) return ptr->data.Var_Map[not_stack.back().PS_Element_Name];
    else return not_stack.back().num;
}

void Interpreter::ChangeToConst(int& result) {
    not_stack.back().PS_Element_Type = Parser::PS_Type::Const;
    not_stack.back().num = result;
}

void Interpreter::in() {
    if (not_stack.back().PS_Element_Type != Parser::PS_Type::Var) Shit(2);
    cout << endl << "Value: ";
    int result;
    cin >> result;
    this->ChangeToConst(result);
}

void Interpreter::out() {
    cout << endl << "Out: " << this->VarOrConst();
    not_stack.pop_back();
    this->ResetMass();
}

void Interpreter::solve(Parser::PS_Operation type) {
    int result = 0;
    for (int i = 0; i < 2; ++i) {
        switch (type) {
        case Parser::PS_Operation::Plus:
            result += this->VarOrConst();
            break;
        case Parser::PS_Operation::Minus:
            result = this->VarOrConst() - result;
            break;
        case Parser::PS_Operation::Div:
            if (i > 0) result = this->VarOrConst() / result;
            else result = this->VarOrConst();
            break;
        case Parser::PS_Operation::Mul:
            if (i > 0) result *= this->VarOrConst();
            else result = this->VarOrConst();
            break;
        }
        if (i < 1) not_stack.pop_back();
    }
    this->ChangeToConst(result);
}

void Interpreter::ass() {
    int result = this->VarOrConst();
    not_stack.pop_back();
    string name = not_stack.back().PS_Element_Name;
    switch (not_stack.back().PS_Element_Type) {
    case Parser::PS_Type::Var:
        ptr->data.Var_Map[name] = result;
        break;
    case Parser::PS_Type::Const:
        if (name == key) this->ChangeMassValue(result);
        else Shit(4);
        break;
    }
    not_stack.pop_back();
    this->ResetMass();
}

void Interpreter::ChangeMassValue(int& value) {
    ptr->data.Mass_Map[key][id] = value;
}

int Interpreter::TakeMassValue(string& s, int& c) {
    return ptr->data.Mass_Map[s][c];
}

void Interpreter::ResetMass() {
    this->key = "empty";
    this->id = 0;
}

void Interpreter::indexing() {
    bool flag = this->key == "empty";
    if (!flag) {
        int t = this->VarOrConst();
        not_stack.pop_back();
        string t2 = not_stack.back().PS_Element_Name;
        int result = 0;
        if (t < ptr->data.Mass_Map[t2].size()) {
            result = this->TakeMassValue(t2, t);
            this->ChangeToConst(result);
        }
        else Shit(1);
    }
    else {
        this->id = this->VarOrConst();
        not_stack.pop_back();
        this->key = not_stack.back().PS_Element_Name;
        int result = 0;
        int size = ptr->data.Mass_Map[key].size();
        if (id < size) {
            result = this->TakeMassValue(key, id);
            this->ChangeToConst(result);
        }
        else Shit(1);
    }
}

void Interpreter::compare(Parser::PS_Operation type) {
    int right = this->VarOrConst();
    not_stack.pop_back();
    int left = this->VarOrConst();
    int result = 0;
    switch (type) {
    case Parser::PS_Operation::Less: if (left < right) result = 1; break;
    case Parser::PS_Operation::Greater: if (left > right) result = 1; break;
    case Parser::PS_Operation::LessEqual: if (left <= right) result = 1; break;
    case Parser::PS_Operation::GreaterEqual: if (left >= right) result = 1; break;
    case Parser::PS_Operation::Equal: if (left == right) result = 1; break;
    case Parser::PS_Operation::NotEqual: if (left != right) result = 1; break;
    }
    this->ChangeToConst(result);
}

void Interpreter::t_transition() {
    this->index = not_stack.back().num - 1;
    not_stack.pop_back();
}

void Interpreter::f_transition() {
    int num = not_stack.back().num;
    not_stack.pop_back();
    int flag = not_stack.back().num;
    not_stack.pop_back();

    switch (flag) {
    case 0: this->index = num - 1; break;
    case 1: break;
    default: Shit(3);
    }
}

string ShitList[] = { "PS_Type = ???", "indexing: array is out of bounds", "in: PS_Type != Const", "transition: flag > 1", "ass: Const = Const" };
void Shit(int number) {
    cout << "\nERROR -- Interpreter: " << ShitList[number];
    exit(0);
}