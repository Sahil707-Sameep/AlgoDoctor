#pragma once
#include <string>
#include <vector>
#include "token.h"

class Lexer {
public:
    // Pass the full source code as a string
    explicit Lexer(const std::string& source);

    // Run the lexer — returns all tokens
    std::vector<Token> tokenize();

private:
    std::string source;   // the raw source code
    int pos;              // current position in source
    int line;             // current line number

    // ── helpers ──────────────────────────────────────────
    char current() const;           // character at pos
    char peek(int offset = 1) const;// look ahead without consuming
    char advance();                 // return current char, move pos forward
    bool isAtEnd() const;

    void skipWhitespace();
    void skipLineComment();         // handles //
    void skipBlockComment();        // handles /* ... */

    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readOperatorOrPunct();

    // Maps a string like "for" → TokenType::FOR
    TokenType classifyKeyword(const std::string& word) const;
};