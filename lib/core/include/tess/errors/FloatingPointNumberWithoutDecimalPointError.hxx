//
// Created by tess on 4/8/26.
//

#ifndef TESSLANG_FLOATINGPOINTNUMERWITHOUTDECIMALPOINTERROR_HXX
#define TESSLANG_FLOATINGPOINTNUMERWITHOUTDECIMALPOINTERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class FloatingPointNumberWithoutDecimalPointError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit FloatingPointNumberWithoutDecimalPointError(
          const lexer::token::TokenPosition& pos, std::string num)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Decimal point not found in floating-point value at line: {}, between chars: {} "
              "- {}: {}",
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(num));
          else
            this->__message = std::format(
              "Decimal point not found in floating-point value at lines: {} - {}, between "
              "chars: {} - {}: {}",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(num));
        }

        ~FloatingPointNumberWithoutDecimalPointError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_FLOATINGPOINTNUMERWITHOUTDECIMALPOINTERROR_HXX
