#pragma once
#include <string>

// Every possible token type AlgoDoctor needs to recognize
enum class TokenType {
    // Keywords
    FOR,
    WHILE,
    DO,
    IF,
    ELSE,
    RETURN,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL,
    VOID,
    VECTOR,
    COUT,
    CIN,

    // Identifiers & Literals
    IDENTIFIER,     // variable names, function names
    NUMBER,         // 0, 1, 42, etc.

    // Operators
    ASSIGN,         // =
    PLUS,           // +
    MINUS,          // -
    MULTIPLY,       // *
    DIVIDE,         // /
    MODULO,         // %
    INCREMENT,      // ++
    DECREMENT,      // --
    PLUS_ASSIGN,    // +=
    MINUS_ASSIGN,   // -=
    MULTIPLY_ASSIGN,// *=
    DIVIDE_ASSIGN,  // /=

    // Comparison
    LESS,           // <
    GREATER,        // >
    LESS_EQ,        // <=
    GREATER_EQ,     // >=
    EQUAL,          // ==
    NOT_EQUAL,      // !=

    // Logical
    AND,            // &&
    OR,             // ||
    NOT,            // !

    // Punctuation
    LPAREN,         // (
    RPAREN,         // )
    LBRACE,         // {
    RBRACE,         // }
    LBRACKET,       // [
    RBRACKET,       // ]
    SEMICOLON,      // ;
    COMMA,          // ,
    DOT,            // .
    COLON,          // :

    // Special
    UNKNOWN,        // anything we don't recognize
    END_OF_FILE     // marks the end of input
};

// Converts a TokenType to a readable string (useful for debugging)
inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::FOR:             return "FOR";
        case TokenType::WHILE:           return "WHILE";
        case TokenType::DO:              return "DO";
        case TokenType::IF:              return "IF";
        case TokenType::ELSE:            return "ELSE";
        case TokenType::RETURN:          return "RETURN";
        case TokenType::INT:             return "INT";
        case TokenType::FLOAT:           return "FLOAT";
        case TokenType::DOUBLE:          return "DOUBLE";
        case TokenType::CHAR:            return "CHAR";
        case TokenType::BOOL:            return "BOOL";
        case TokenType::VOID:            return "VOID";
        case TokenType::VECTOR:          return "VECTOR";
        case TokenType::COUT:            return "COUT";
        case TokenType::CIN:             return "CIN";
        case TokenType::IDENTIFIER:      return "IDENTIFIER";
        case TokenType::NUMBER:          return "NUMBER";
        case TokenType::ASSIGN:          return "ASSIGN(=)";
        case TokenType::PLUS:            return "PLUS(+)";
        case TokenType::MINUS:           return "MINUS(-)";
        case TokenType::MULTIPLY:        return "MULTIPLY(*)";
        case TokenType::DIVIDE:          return "DIVIDE(/)";
        case TokenType::MODULO:          return "MODULO(%)";
        case TokenType::INCREMENT:       return "INCREMENT(++)";
        case TokenType::DECREMENT:       return "DECREMENT(--)";
        case TokenType::PLUS_ASSIGN:     return "PLUS_ASSIGN(+=)";
        case TokenType::MINUS_ASSIGN:    return "MINUS_ASSIGN(-=)";
        case TokenType::MULTIPLY_ASSIGN: return "MULTIPLY_ASSIGN(*=)";
        case TokenType::DIVIDE_ASSIGN:   return "DIVIDE_ASSIGN(/=)";
        case TokenType::LESS:            return "LESS(<)";
        case TokenType::GREATER:         return "GREATER(>)";
        case TokenType::LESS_EQ:         return "LESS_EQ(<=)";
        case TokenType::GREATER_EQ:      return "GREATER_EQ(>=)";
        case TokenType::EQUAL:           return "EQUAL(==)";
        case TokenType::NOT_EQUAL:       return "NOT_EQUAL(!=)";
        case TokenType::AND:             return "AND(&&)";
        case TokenType::OR:              return "OR(||)";
        case TokenType::NOT:             return "NOT(!)";
        case TokenType::LPAREN:          return "LPAREN(()";
        case TokenType::RPAREN:          return "RPAREN())";
        case TokenType::LBRACE:          return "LBRACE({)";
        case TokenType::RBRACE:          return "RBRACE(})";
        case TokenType::LBRACKET:        return "LBRACKET([)";
        case TokenType::RBRACKET:        return "RBRACKET(])";
        case TokenType::SEMICOLON:       return "SEMICOLON(;)";
        case TokenType::COMMA:           return "COMMA(,)";
        case TokenType::DOT:             return "DOT(.)";
        case TokenType::COLON:           return "COLON(:)";
        case TokenType::UNKNOWN:         return "UNKNOWN";
        case TokenType::END_OF_FILE:     return "EOF";
        default:                         return "?";
    }
}

// A single token with its type, raw value, and which line it came from
struct Token {
    TokenType   type;
    std::string value;  // the actual text e.g. "for", "i", "42"
    int         line;   // line number in the source file (1-indexed)

    Token(TokenType t, std::string v, int l)
        : type(t), value(std::move(v)), line(l) {}
};