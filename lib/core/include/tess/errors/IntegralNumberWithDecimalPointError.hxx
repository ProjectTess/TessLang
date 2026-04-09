//
// Created by tess on 4/8/26.
//

#ifndef TESSLANG_INTEGRALNUMBERWITHDECIMALPOINTERROR_HXX
#define TESSLANG_INTEGRALNUMBERWITHDECIMALPOINTERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class IntegralNumberWithDecimalPointError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit IntegralNumberWithDecimalPointError(
          const lexer::token::TokenPosition& pos, std::string num)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Decimal point not allowed in integral value at line: {}, between chars: {} "
              "- {}: {}",
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(num));
          else
            this->__message = std::format(
              "Decimal point not allowed in integral value at lines: {} - {}, between "
              "chars: {} - {}: {}",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(num));
        }

        ~IntegralNumberWithDecimalPointError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess
;

#endif   // TESSLANG_INTEGRALNUMBERWITHDECIMALPOINTERROR_HXX
