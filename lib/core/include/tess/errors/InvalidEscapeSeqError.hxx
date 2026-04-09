//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_INVALIDESCAPESEQERROR_HXX
#define TESSLANG_INVALIDESCAPESEQERROR_HXX

#include "fmt/base.h"

#include <format>
#include <tess/errors/TessError.hxx>
#include <tess/lexer/TokenPosition.hxx>

namespace tess
{
  namespace error
  {

    class InvalidEscapeSeqError: public TessError
    {
      private:
        std::string __message;

      public:
        explicit InvalidEscapeSeqError(
          const lexer::token::TokenPosition& pos, std::string invalidEsc)
        {
          if(pos.lines().first == pos.lines().second)
            this->__message = std::format(
              "Invalid escape sequence at line: {}, between chars: {} - {}: '{}'",
              pos.lines().first, pos.columns().first, pos.columns().second, std::move(invalidEsc));
          else
            this->__message = std::format(
              "Invalid escape sequence at lines: {} - {}, between chars: {} - "
              "{}: '{}'",
              pos.lines().first, pos.lines().second, pos.columns().first, pos.columns().second,
              std::move(invalidEsc));
        }

        ~InvalidEscapeSeqError() noexcept override = default;

        const char* message() const noexcept override
        {
          return this->__message.c_str();
        }
    };

  }   // namespace error
}   // namespace tess

#endif   // TESSLANG_INVALIDESCAPESEQERROR_HXX
