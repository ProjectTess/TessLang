//
// Created by tess on 4/8/26.
//

#include <gtest/gtest.h>
#include <tess/lexer/Lexer.hxx>
#include <tess/errors/TessError.hxx>

using namespace tess::lexer;
using namespace tess::lexer::token;
using namespace tess::error;

TEST(Tess, FirstLexerTest)
{
  auto lex = Lexer("75b; \"test-string\"; 'l'; \"\\n\"; true;");
  const auto processed = lex.tokenize();

  const std::vector<Token> expected {
    { I8Literal(75), { { 1, 1 }, { 0, 4 } } },
    { Semicolon(), { { 1, 1 }, { 3, 5 } } },
    { StringLiteral(std::string("test-string")), { { 1, 1 }, { 5, 18 } } },
    { Semicolon(), { { 1, 1 }, { 18, 20 } } },
    { CharLiteral('l'), { { 1, 1 }, { 20, 24 } } },
    { Semicolon(), { { 1, 1 }, { 23, 25 } } },
    { StringLiteral("\\n"), { { 1, 1 }, { 25, 29 } } },
    { Semicolon(), { { 1, 1 }, { 29, 31 } } },
    { BoolLiteral(true), { { 1, 1 }, { 31, 36 } } },
    { Semicolon(), { { 1, 1 }, { 35, 37 } } }
  };

  // for(auto token: processed)
  //   std::cout << token.toString() << std::endl;
  //
  // std::cout << std::endl;
  //
  // for(auto token: expected)
  //   std::cout << token.toString() << std::endl;

  EXPECT_EQ(expected, processed);
}

TEST(Tess, SecondLexerTest)
{
  auto lex = Lexer(R"(byte init() {
  ret 0;
}
)");
  const auto processed = lex.tokenize();

  const std::vector<Token> expected {
    { Identifier("byte"), { { 1, 1 }, { 0, 5 } } }, { Identifier("init"), { { 1, 1 }, { 5, 10 } } },
    { LeftParen(), { { 1, 1 }, { 9, 11 } } },       { RightParen(), { { 1, 1 }, { 10, 12 } } },
    { LeftBrace(), { { 1, 1 }, { 12, 14 } } },      { Keyword::Return, { { 2, 2 }, { 2, 6 } } },
    { I64Literal(0), { { 2, 2 }, { 6, 8 } } },      { Semicolon(), { { 2, 2 }, { 7, 9 } } },
    { RightBrace(), { { 3, 3 }, { 0, 2 } } }
  };

  // for(auto token: processed)
  //   std::cout << token.toString() << std::endl;
  //
  // std::cout << std::endl;
  //
  // for(auto token: expected)
  //   std::cout << token.toString() << std::endl;

  EXPECT_EQ(processed, expected);
}

TEST(Tess, ThirdLexerTest)
{
  auto lex = Lexer("0b1001_B; 0o037651_i; 0x7fffffff_l;");
  const auto processed = lex.tokenize();

  const std::vector<Token> expected {
    { U8Literal(0b1001), { { 1, 1 }, { 0, 9 } } },        { Semicolon(), { { 1, 1 }, { 8, 10 } } },
    { I32Literal(0037651), { { 1, 1 }, { 10, 21 } } },    { Semicolon(), { { 1, 1 }, { 20, 22 } } },
    { I64Literal(0x7fffffff), { { 1, 1 }, { 22, 35 } } }, { Semicolon(), { { 1, 1 }, { 34, 36 } } }
  };

  // for(auto token: processed)
  //   std::cout << token.toString() << std::endl;
  //
  // std::cout << std::endl;
  //
  // for(auto token: expected)
  //   std::cout << token.toString() << std::endl;

  EXPECT_EQ(expected, processed);
}

TEST(Tess, FourthLexerTest)
{
  auto lex = Lexer("0x7fffffffI");
  const auto processed = lex.tokenize();

  const std::vector<Token> expected { { U32Literal(0x7fffffff), { { 1, 1 }, { 0, 12 } } } };

  for(auto token: processed)
    std::cout << token.toString() << std::endl;

  std::cout << std::endl;

  for(auto token: expected)
    std::cout << token.toString() << std::endl;

  EXPECT_EQ(expected, processed);
}

TEST(Tess, FifthLexerTest)
{
  try
  {
    auto lex = Lexer("0x7fffffffffI");
    const auto processed = lex.tokenize();
  }
  catch(const TessError& err)
  {
    std::cout << err.message() << std::endl;
  }
  catch(const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }
}