//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_OUTOFRANGEERROR_HXX
#define TESSLANG_OUTOFRANGEERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class OutOfRangeError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit OutOfRangeError(const lexer::token::TokenPosition& pos, std::string outed)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Object's value ({}) out-of-range at line: {}, between chars: {} - {}",
              std::move(outed), pos.lines().first, pos.columns().first, pos.columns().second);
          else
            this->__message = std::format(
              "Object's value ({}) out-of-range at lines: {} - {}, between chars: {} - {}",
              std::move(outed), pos.lines().first, pos.lines().second, pos.columns().first,
              pos.columns().second);
        }

        ~OutOfRangeError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_OUTOFRANGEERROR_HXX
