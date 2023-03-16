
using namespace std;

#include <ctype.h>

#include "compiler.h"

int tokenizer(string& input, TokenptrVector& tokens) {
    int current = 0;
    while (current < input.size()) {
        char c = input.at(current);
        if (DEF_IS_Left_Semi(c)) {
            Token* t = new Token(Token_Type_Semi, "(");
            tokens.push_back(t);
            current++;
            continue;
        }
        if (DEF_IS_Right_Semi(c)) {
            Token* t = new Token(Token_Type_Semi, ")");
            tokens.push_back(t);
            current++;
            continue;
        }
        if (DEF_IS_Left_Quote(c)) {
            Token* t = new Token(Token_Type_Quote, "{");
            tokens.push_back(t);
            current++;
            continue;
        }
        if (DEF_IS_Right_Quote(c)) {
            Token* t = new Token(Token_Type_Quote, "}");
            tokens.push_back(t);
            current++;
            continue;
        }
        if (DEF_IS_Empty(c)) {
            current++;
            continue;
        }
        if (DEF_IS_DIGIT(c)) {
            string value;
            while (DEF_IS_DIGIT(c) && current < input.size()) {
                value += c;
                current++;
                if (current >= input.size()) break;
                c = input.at(current);
            }
            Token* t = new Token(Token_Type_Number, value);
            tokens.push_back(t);
            continue;
        }
        if (DEF_IS_String(c)) {
            string value;
            c = input.at(++current);
            while (!DEF_IS_String(c) && current <= input.size()) {
                value += c;
                current++;
                if (current >= input.size()) break;
                c = input[current];
            }
            c = input[++current];
            Token* t = new Token(Token_Type_String, value);
            tokens.push_back(t);
            continue;
        }
        if (DEF_IS_MARK(c)) {
            string value;
            c = input.at(++current);
            while (DEF_IS_Empty(c)) {
                current++;
                if (current >= input.size()) break;
                c = input.at(current);
            }
            while (!DEF_IS_NEXT_LINE(c) && current <= input.size()) {
                value += c;
                current++;
                if (current >= input.size()) break;
                c = input.at(current);
            }
            c = input.at(++current);
            Token* t = new Token(Token_Type_Comment, value);
            tokens.push_back(t);
        }
        if (DEF_IS_LETTERS(c)) {
            string value;
            while (DEF_IS_LETTERS(c) && current <= input.size()) {
                value += c;
                current++;
                if (current >= input.size()) break;
                c = input.at(current);
            }
            Token* t = new Token(Token_Type_Letter, value);
            tokens.push_back(t);
            continue;
        }
        cout << __func__ << " 未识别的类型: " << c << endl;
        exit(1);
    }
    return tokens.size();
}

AStruct* walk(TokenptrVector& tokens, uint32_t& current) {
    Token* token = tokens[current];
    if (Token_Type_Comment == token->type) {
        current++;
        return new AStruct(Ast_Type_Comment, token->value);
    }
    if (Token_Type_Letter == token->type) {
        current++;
        return new AStruct(Ast_Type_Symbol, token->value);
    }
    if (Token_Type_Number == token->type) {
        current++;
        return new AStruct(Ast_Type_Number, token->value);
    }
    if (Token_Type_String == token->type) {
        current++;
        return new AStruct(Ast_Type_String, token->value);
    }
    if (Token_Type_Semi == token->type && "(" == token->value) {
        ASTptrVector* children = new ASTptrVector;
        children->push_back(new AStruct(Ast_Type_Semi, "("));
        AStruct* node = new AStruct(Ast_Type_SExpr, "", children);
        token = tokens.at(++current);
        while (
            current < tokens.size() &&
            (
                Token_Type_Semi != token->type ||
                (Token_Type_Semi == token->type && ")" != token->value)
            )
        ) {
            AStruct* child_node = walk(tokens, current);
            node->children->push_back(child_node);
            if (current >= tokens.size()) break;
            token = tokens.at(current);
        }
        current++;
        node->children->push_back(new AStruct(Ast_Type_Semi, ")"));
        return node;
    }
    if (Token_Type_Quote == token->type && "{" == token->value) {
        ASTptrVector* children = new ASTptrVector;
        children->push_back(new AStruct(Ast_type_Quote, "{"));
        AStruct* node = new AStruct(Ast_Type_QExpr, "", children);
        token = tokens.at(++current);
        while (
            current < tokens.size() &&
            (
                Token_Type_Quote != token->type ||
                (Token_Type_Quote == token->type && "}" != token->value)
            )
        ) {
            AStruct* child_node = walk(tokens, current);
            node->children->push_back(child_node);
            if (current >= tokens.size()) break;
            token = tokens.at(current);
        }
        current++;
        node->children->push_back(new AStruct(Ast_type_Quote, "}"));
        return node;
    }
    cout << __func__ << " 未识别类型: " << token->type << endl;
    exit(1);
}

AStruct* aster(TokenptrVector& tokens) {
    uint32_t current = 0;
    ASTptrVector* children = new ASTptrVector;
    AStruct* ast = new AStruct(Ast_Type_Program, ">", children);
    while (current < tokens.size()) {
        AStruct* child = walk(tokens, current);
        ast->children->push_back(child);
    }
    return ast;
}

AStruct* compiler(string& input) {
    TokenptrVector tokens;
    int count = tokenizer(input, tokens);
    return aster(tokens);
}

#pragma mark ---

void print_indent(uint32_t indent = 0) {
    for (int i = 0; i < indent; i++) {
        cout << " ";
    }
}

string type2name(Ast_Type type) {
    switch (type) {
        case Ast_Type_Program: return ">";
        case Ast_Type_Comment: return "Comment";
        case Ast_Type_Number: return "Number";
        case Ast_Type_String: return "String";
        case Ast_Type_Symbol: return "Symbol";
        case Ast_Type_SExpr: return "Sexpr";
        case Ast_Type_Semi: return "SemiColon";
        case Ast_Type_QExpr: return "Qexpr";
        case Ast_type_Quote: return "Quote";
        default:
            return "Unknown Type!" + type;
    }
}

#pragma mark ---

void AStruct::expr_print(uint32_t indent) {
    print_indent(indent);
    cout << type2name(type) << " : " << endl;

    for (ASTptrVector::iterator it = children->begin(); it < children->end(); it++) {
        AStruct* child = *it;
        child->print(indent + 1);
    }
}

void AStruct::print(uint32_t indent) {
    switch (type) {
        case Ast_Type_Program:
        case Ast_Type_SExpr:
        case Ast_Type_QExpr:
            expr_print(indent);
            break;
        default:
            print_indent(indent);
            cout << type2name(type) << " : " << content << endl;
    }
}

void AStruct::exprDeleteNode() {
    for (ASTptrVector::iterator it = children->begin(); it != children->end(); it++) {
        (*it)->deleteNode();
    }
    delete children;
}

void AStruct::deleteNode() {
    switch (type) {
        case Ast_Type_Program:
        case Ast_Type_SExpr:
        case Ast_Type_QExpr:
            exprDeleteNode();
            break;
    }
    delete this;
}
