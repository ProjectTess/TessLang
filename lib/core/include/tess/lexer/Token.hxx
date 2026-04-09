//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_TOKEN_HXX
#define TESSLANG_TOKEN_HXX

#include <tess/lexer/TokenPosition.hxx>
#include <tess/lexer/TokenType.hxx>

namespace tess
{
  namespace lexer
  {
    namespace token
    {

      class Token
      {
        private:
          TokenType __type;
          TokenPosition __pos;

        public:
          Token(TokenType type, TokenPosition pos);
          ~Token() noexcept;

          TokenType type() const;
          TokenPosition pos() const;

          std::string toString() const;

          bool operator==(const Token& other) const
          {
            return this->type() == other.type() && this->pos() == other.pos();
          }

          bool operator!=(const Token& other) const
          {
            return !(*this == other);
          }
      };

    }   // namespace token
  }   // namespace lexer
}   // namespace tess

#endif   // TESSLANG_TOKEN_HXX