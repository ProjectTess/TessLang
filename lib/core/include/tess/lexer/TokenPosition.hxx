//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_TOKENPOSITION_HXX
#define TESSLANG_TOKENPOSITION_HXX

#include <utility>

namespace tess
{
  namespace lexer
  {
    namespace token
    {

      class TokenPosition
      {
        private:
          std::pair<std::size_t, std::size_t> __lns;
          std::pair<std::size_t, std::size_t> __cols;

        public:
          TokenPosition(
            std::pair<std::size_t, std::size_t> lns, std::pair<std::size_t, std::size_t> cols):
            __lns(std::move(lns)),
            __cols(std::move(cols)) { };
          ~TokenPosition() noexcept = default;

          std::pair<std::size_t, std::size_t> lines() const
          {
            return this->__lns;
          }

          std::pair<std::size_t, std::size_t> columns() const
          {
            return this->__cols;
          }

          bool operator==(const TokenPosition& other) const
          {
            return this->lines() == other.lines() && this->columns() == other.columns();
          }

          bool operator!=(const TokenPosition& other) const
          {
            return !(*this == other);
          }
      };

    }   // namespace token
  }   // namespace lexer
}   // namespace tess

#endif   // TESSLANG_TOKENPOSITION_HXX
