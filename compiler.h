#pragma once

#include <iostream>
#include <vector>

#define DEF_IS_Left_Semi(x) ('(' == x)
#define DEF_IS_Right_Semi(x) (')' == x)
#define DEF_IS_Left_Quote(x) ('{' == x)
#define DEF_IS_Right_Quote(x) ('}' == x)
#define DEF_IS_Empty(x) (' ' == x)
#define DEF_IS_String(x) ('"' == x)
#define DEF_IS_MARK(x) (';' == x)
#define DEF_IS_DIGIT(x) (isdigit(x))
#define DEF_IS_NEXT_LINE(x) ('\n' == x || '\r\n' == x)
// Symbol content
#define DEF_IS_LETTERS(x) ( \
    isalnum(x) || \
    '+' == x || '-' == x || '*' == x || '/' == x || '=' || \
    '\\' == x || '_' == x || '&' == x \
)
typedef enum {
    Token_Type_Semi,
    Token_Type_Quote,
    Token_Type_Number,
    Token_Type_String,
    Token_Type_Comment,
    Token_Type_Letter
} Token_Type;

typedef enum {
    Ast_Type_Error,
    Ast_Type_Program,
    Ast_Type_Comment,
    Ast_Type_Symbol,
    Ast_Type_Number,
    Ast_Type_String,
    Ast_Type_SExpr,
    Ast_Type_Semi,
    Ast_Type_QExpr,
    Ast_type_Quote
} Ast_Type;

class Token;
class AStruct;
typedef std::vector<Token*> TokenptrVector;
typedef std::vector<AStruct*> ASTptrVector;

class Token {
public:
    Token_Type type;
    std::string value;
    Token(Token_Type a, std::string b): type(a), value(b) {}
};

class AStruct {
public:
    Ast_Type type;
    std::string error;
    std::string content;
    ASTptrVector* children;
    AStruct(Ast_Type a): type(a) {}
    AStruct(Ast_Type a, std::string b, ASTptrVector* c = NULL): type(a), content(b), children(c) {}
    // print node
    void print(uint32_t indent = 0);
    // delete node
    void deleteNode(void);
private:
    void expr_print(uint32_t indent = 0);
    void exprDeleteNode();
};

class AKCompiler {
public:
    // compiler Entrance
    static AStruct& compiler(std::string& input);

    static int tokenizer(std::string& input, TokenptrVector& tokens);
    static AStruct& aster(TokenptrVector& tokens);
private:
    static AStruct* walk(TokenptrVector& tokens, uint32_t& current);
};
