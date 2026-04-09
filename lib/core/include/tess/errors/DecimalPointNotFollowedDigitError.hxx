//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_DECIMALPOINTNOTFOLLOWEDDIGITERROR_HXX
#define TESSLANG_DECIMALPOINTNOTFOLLOWEDDIGITERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class DecimalPointNotFollowedDigitError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit DecimalPointNotFollowedDigitError(
          const lexer::token::TokenPosition& pos, std::string num)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Decimal point is not followed by digit at line: {}, between chars: {} "
              "- {}: {}",
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(num));
          else
            this->__message = std::format(
              "Decimal point must be followed by digit at lines: {} - {}, between "
              "chars: {} - {}: {}",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(num));
        }

        ~DecimalPointNotFollowedDigitError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_DECIMALPOINTNOTFOLLOWEDDIGITERROR_HXX
