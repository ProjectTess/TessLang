//
// Created by tess on 3/29/26.
//

#include <gtest/gtest.h>
#include <tess/lexer/Token.hxx>

using namespace tess::lexer;

TEST(Tess, TokenCreation) {
    auto token1 = Token(Plus(), 1, { 0, 2 });
    auto token2 = Token{ Minus(), 1, { 2, 4 } };
}

TEST(Tess, TokenData) {
    auto token = Token(Plus(), 1, { 0, 2 });
    auto type = token.type();
    auto lines = token.lines();
    auto pos = token.pos();

    std::cout << std::visit(TokenVisitor(), type) << std::endl;
    std::cout << lines.first << std::endl;
    std::cout << lines.second << std::endl;
    std::cout << pos.first << std::endl;
    std::cout << pos.second << std::endl;
}