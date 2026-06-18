#include "lexer.h"
#include <cctype>
#include <stdexcept>

// ── Constructor ───────────────────────────────────────────────────────────────

Lexer::Lexer(const std::string& source)
    : source(source), pos(0), line(1) {}

// ── Public ────────────────────────────────────────────────────────────────────

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;

        // Skip single-line comments
        if (current() == '/' && peek() == '/') {
            skipLineComment();
            continue;
        }

        // Skip block comments
        if (current() == '/' && peek() == '*') {
            skipBlockComment();
            continue;
        }

        // Identifier or keyword (starts with letter or _)
        if (std::isalpha(current()) || current() == '_') {
            tokens.push_back(readIdentifierOrKeyword());
            continue;
        }

        // Number literal
        if (std::isdigit(current())) {
            tokens.push_back(readNumber());
            continue;
        }

        // Operator or punctuation
        tokens.push_back(readOperatorOrPunct());
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "EOF", line);
    return tokens;
}

// ── Private helpers ───────────────────────────────────────────────────────────

char Lexer::current() const {
    if (isAtEnd()) return '\0';
    return source[pos];
}

char Lexer::peek(int offset) const {
    int target = pos + offset;
    if (target >= (int)source.size()) return '\0';
    return source[target];
}

char Lexer::advance() {
    char c = source[pos++];
    if (c == '\n') line++;
    return c;
}

bool Lexer::isAtEnd() const {
    return pos >= (int)source.size();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(current())) {
        advance();
    }
}

void Lexer::skipLineComment() {
    // consume everything until end of line
    while (!isAtEnd() && current() != '\n') {
        advance();
    }
}

void Lexer::skipBlockComment() {
    advance(); // consume '/'
    advance(); // consume '*'
    while (!isAtEnd()) {
        if (current() == '*' && peek() == '/') {
            advance(); // consume '*'
            advance(); // consume '/'
            return;
        }
        advance();
    }
    // if we reach here, block comment was never closed — that's a bug in user code
}

// ── Token readers ─────────────────────────────────────────────────────────────

Token Lexer::readIdentifierOrKeyword() {
    int startLine = line;
    std::string word;

    while (!isAtEnd() && (std::isalnum(current()) || current() == '_')) {
        word += advance();
    }

    TokenType type = classifyKeyword(word);
    return Token(type, word, startLine);
}

Token Lexer::readNumber() {
    int startLine = line;
    std::string num;

    while (!isAtEnd() && std::isdigit(current())) {
        num += advance();
    }

    // handle decimal point e.g. 3.14
    if (!isAtEnd() && current() == '.' && std::isdigit(peek())) {
        num += advance(); // consume '.'
        while (!isAtEnd() && std::isdigit(current())) {
            num += advance();
        }
    }

    return Token(TokenType::NUMBER, num, startLine);
}

Token Lexer::readOperatorOrPunct() {
    int startLine = line;
    char c = advance();

    switch (c) {
        case '(': return Token(TokenType::LPAREN,    "(", startLine);
        case ')': return Token(TokenType::RPAREN,    ")", startLine);
        case '{': return Token(TokenType::LBRACE,    "{", startLine);
        case '}': return Token(TokenType::RBRACE,    "}", startLine);
        case '[': return Token(TokenType::LBRACKET,  "[", startLine);
        case ']': return Token(TokenType::RBRACKET,  "]", startLine);
        case ';': return Token(TokenType::SEMICOLON, ";", startLine);
        case ',': return Token(TokenType::COMMA,     ",", startLine);
        case '.': return Token(TokenType::DOT,       ".", startLine);
        case ':': return Token(TokenType::COLON,     ":", startLine);

        case '+':
            if (current() == '+') { advance(); return Token(TokenType::INCREMENT,    "++", startLine); }
            if (current() == '=') { advance(); return Token(TokenType::PLUS_ASSIGN,  "+=", startLine); }
            return Token(TokenType::PLUS, "+", startLine);

        case '-':
            if (current() == '-') { advance(); return Token(TokenType::DECREMENT,    "--", startLine); }
            if (current() == '=') { advance(); return Token(TokenType::MINUS_ASSIGN, "-=", startLine); }
            return Token(TokenType::MINUS, "-", startLine);

        case '*':
            if (current() == '=') { advance(); return Token(TokenType::MULTIPLY_ASSIGN, "*=", startLine); }
            return Token(TokenType::MULTIPLY, "*", startLine);

        case '/':
            if (current() == '=') { advance(); return Token(TokenType::DIVIDE_ASSIGN, "/=", startLine); }
            return Token(TokenType::DIVIDE, "/", startLine);

        case '%': return Token(TokenType::MODULO, "%", startLine);

        case '<':
            if (current() == '=') { advance(); return Token(TokenType::LESS_EQ,  "<=", startLine); }
            return Token(TokenType::LESS, "<", startLine);

        case '>':
            if (current() == '=') { advance(); return Token(TokenType::GREATER_EQ, ">=", startLine); }
            return Token(TokenType::GREATER, ">", startLine);

        case '=':
            if (current() == '=') { advance(); return Token(TokenType::EQUAL,  "==", startLine); }
            return Token(TokenType::ASSIGN, "=", startLine);

        case '!':
            if (current() == '=') { advance(); return Token(TokenType::NOT_EQUAL, "!=", startLine); }
            return Token(TokenType::NOT, "!", startLine);

        case '&':
            if (current() == '&') { advance(); return Token(TokenType::AND, "&&", startLine); }
            return Token(TokenType::UNKNOWN, "&", startLine);

        case '|':
            if (current() == '|') { advance(); return Token(TokenType::OR, "||", startLine); }
            return Token(TokenType::UNKNOWN, "|", startLine);

        default:
            return Token(TokenType::UNKNOWN, std::string(1, c), startLine);
    }
}

// ── Keyword classifier ────────────────────────────────────────────────────────

TokenType Lexer::classifyKeyword(const std::string& word) const {
    if (word == "for")     return TokenType::FOR;
    if (word == "while")   return TokenType::WHILE;
    if (word == "do")      return TokenType::DO;
    if (word == "if")      return TokenType::IF;
    if (word == "else")    return TokenType::ELSE;
    if (word == "return")  return TokenType::RETURN;
    if (word == "int")     return TokenType::INT;
    if (word == "float")   return TokenType::FLOAT;
    if (word == "double")  return TokenType::DOUBLE;
    if (word == "char")    return TokenType::CHAR;
    if (word == "bool")    return TokenType::BOOL;
    if (word == "void")    return TokenType::VOID;
    if (word == "vector")  return TokenType::VECTOR;
    if (word == "cout")    return TokenType::COUT;
    if (word == "cin")     return TokenType::CIN;

    // not a keyword → it's an identifier (variable/function name)
    return TokenType::IDENTIFIER;
}