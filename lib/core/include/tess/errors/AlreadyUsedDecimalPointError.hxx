//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_ALREADYUSEDDECIMALPOINTERROR_HXX
#define TESSLANG_ALREADYUSEDDECIMALPOINTERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class AlreadyUsedDecimalPointError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit AlreadyUsedDecimalPointError(
          const lexer::token::TokenPosition& pos, std::string num)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Decimal point is already used in number at line: {}, between chars: {} - {}: {}",
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(num));
          else
            this->__message = std::format(
              "Decimal point is already used in number at lines: {} - {}, between chars: {} - {}: "
              "{}",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(num));
        }

        ~AlreadyUsedDecimalPointError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_ALREADYUSEDDECIMALPOINTERROR_HXX
