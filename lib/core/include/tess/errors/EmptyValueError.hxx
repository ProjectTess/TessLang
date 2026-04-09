//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_EMPTYVALUEERROR_HXX
#define TESSLANG_EMPTYVALUEERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class EmptyValueError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit EmptyValueError(const lexer::token::TokenPosition& pos, std::string type)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Empty {}-type value at line: {}, between chars: {} - {}", std::move(type),
              pos.lines().first, pos.columns().first, pos.columns().second);
          else
            this->__message = std::format(
              "Empty {}-type value at lines: {} - {}, between chars: {} - {}", std::move(type),
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second);
        }

        ~EmptyValueError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_EMPTYVALUEERROR_HXX
