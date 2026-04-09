//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_UNCLOSEDLITERALERROR_HXX
#define TESSLANG_UNCLOSEDLITERALERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class UnclosedLiteralError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit UnclosedLiteralError(
          const lexer::token::TokenPosition& pos, std::string literalType)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Unclosed {} literal at line: {}", std::move(literalType), pos.lines().first);
          else
            this->__message = std::format(
              "Unexpected {} literal at lines: {} - {}", std::move(literalType), pos.lines().first,
              pos.lines().second);
        }

        ~UnclosedLiteralError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_UNCLOSEDLITERALERROR_HXX
