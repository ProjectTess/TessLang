//
// Created by tess on 3/29/26.
//

#include <gtest/gtest.h>
#include <tess/lexer/Token.hxx>

using namespace tess::lexer::token;

TEST(Tess, TokenCreationTest)
{
  auto token1 = Token(Plus(), { { 1, 0 }, { 0, 2 } });
  auto token2 = Token { Minus(), { { 1, 0 }, { 2, 4 } } };
  Token token3 = { I32Literal(674736222), { { 1, 0 }, { 0, 9 } } };
}

TEST(Tess, FirstTokenDataTest)
{
  const auto token = Token(Plus(), { { 1, 0 }, { 0, 2 } });
  std::cout << token.toString() << std::endl;
}

TEST(Tess, SecondTokenDataTest)
{
  const auto token = Token(I64Literal(74665278990998), { { 1, 0 }, { 0, 14 } });
  std::cout << token.toString() << std::endl;
}

TEST(Tess, ThirdTokenDataTest)
{
  const auto token = Token(DoubleLiteral(153.3827287364), { { 1, 0 }, { 0, 14 } });
  std::cout << token.toString() << std::endl;
}

TEST(Tess, FourthTokenDataTest)
{
  const auto token = Token(BoolLiteral(true), { { 1, 0 }, { 0, 5 } });
  std::cout << token.toString() << std::endl;
}

TEST(Tess, FifthTokenDataTest)
{
  const auto token = Token(Identifier("foobar"), { { 1, 0 }, { 0, 7 } });
  std::cout << token.toString() << std::endl;
}