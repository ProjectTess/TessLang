//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_INVALIDARGERROR_HXX
#define TESSLANG_INVALIDARGERROR_HXX

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class InvalidArgError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit InvalidArgError(
          const lexer::token::TokenPosition& pos, std::string argType, std::string arg)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Invalid {} at line: {}, between chars: {} - {}: {}", std::move(argType),
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(arg));
          else
            this->__message = std::format(
              "Invalid {} at lines: {} - {}, between chars: {} - {}: {}", std::move(argType),
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(arg));
        }

        ~InvalidArgError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_INVALIDARGERROR_HXX
