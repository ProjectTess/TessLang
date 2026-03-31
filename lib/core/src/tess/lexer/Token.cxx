//
// Created by tess on 3/29/26.
//

#include <tess/lexer/Token.hxx>

using namespace tess::lexer;

Token::Token(TokenType type, std::pair<size_t, size_t> lines,
             std::pair<size_t, size_t> pos):
    _type(std::move(type)), _lines(std::move(lines)),
    _pos(std::move(pos))
{
}
Token::~Token() = default;

TokenType Token::type() const
{
    return this->_type;
}
std::pair<std::size_t, std::size_t> Token::lines() const
{
    return this->_lines;
}
std::pair<std::size_t, std::size_t> Token::pos() const
{
    return this->_pos;
}