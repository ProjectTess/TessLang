//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_DECIMALPOINTERROR_HXX
#define TESSLANG_DECIMALPOINTERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class InvalidBaseWithDecimalPointError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit InvalidBaseWithDecimalPointError(const lexer::token::TokenPosition& pos, std::string num)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Decimal point is not allowed in non-10-based numbers at line: {}, between chars: {} - {}: {}",
              pos.lines().first, pos.columns().first, pos.columns().second,  std::move(num));
          else
            this->__message = std::format(
              "Decimal point is not allowed in non-10-based numbers at lines: {} - {}, between chars: {} - {}: {}",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second, std::move(num));
        }

        ~InvalidBaseWithDecimalPointError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_DECIMALPOINTERROR_HXX
