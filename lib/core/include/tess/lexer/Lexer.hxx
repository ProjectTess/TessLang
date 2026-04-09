//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_LEXER_HXX
#define TESSLANG_LEXER_HXX

#include <tess/lexer/Token.hxx>
#include <vector>

namespace tess
{
  namespace lexer
  {

    class Lexer
    {
      private:
        size_t __ln, __col, __pos, __maxPos;
        const std::string __code;

        bool isValid(long at = 0) const;

        bool isDigit(long at = 0) const;
        bool isAlpha(long at = 0) const;
        bool isAlphaOrNum(long at = 0) const;
        bool isSpace(long at = 0) const;

        void advance(unsigned long toPos = 1);

        char peek(long toPos = 0) const;
        char take();

      public:
        explicit Lexer(std::string code);
        ~Lexer() noexcept;

        std::vector<token::Token> tokenize();
    };

  }   // namespace lexer
}   // namespace tess

#endif   // TESSLANG_LEXER_HXX