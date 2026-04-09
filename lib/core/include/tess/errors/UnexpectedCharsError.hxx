//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_UNEXPECTEDCHARS_HXX
#define TESSLANG_UNEXPECTEDCHARS_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class UnexpectedCharsError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit UnexpectedCharsError(const lexer::token::TokenPosition& pos, std::string chars)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Unexpected chars at line: {}, between chars: {} - {}: {}", pos.lines().first,
              pos.columns().first, pos.columns().second, std::move(chars));
          else
            this->__message = std::format(
              "Unexpected chars at lines: {} - {}, between chars: {} - {}: {}", pos.lines().first,
              pos.lines().second, pos.columns().first, pos.columns().second, std::move(chars));
        }

        ~UnexpectedCharsError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_UNEXPECTEDCHARS_HXX
