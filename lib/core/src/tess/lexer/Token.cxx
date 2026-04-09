//
// Created by tess on 3/29/26.
//

#include <format>
#include <tess/lexer/Token.hxx>

using namespace tess::lexer::token;

Token::Token(TokenType type, TokenPosition pos):
  __type(std::move(type)),
  __pos(std::move(pos))
{
}

Token::~Token() noexcept = default;

TokenType Token::type() const
{
  return this->__type;
}

TokenPosition Token::pos() const
{
  return this->__pos;
}

std::string Token::toString() const
{
  if(this->pos().lines().second == 0 || this->pos().lines().first == this->pos().lines().second)
    return std::format(
      "Token ({}): at line: {}, between chars: {} - {}", std::visit(TokenVisitor(), this->type()),
      this->pos().lines().first, this->pos().columns().first, this->pos().columns().second);

  return std::format(
    "Token ({}): at lines: {} - {}, between chars: {} - {}",
    std::visit(TokenVisitor(), this->type()), this->pos().lines().first, this->pos().lines().second,
    this->pos().columns().first, this->pos().columns().second);
}