//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_TOKEN_HXX
#define TESSLANG_TOKEN_HXX

#include <tess/lexer/TokenType.hxx>

namespace tess
{
    namespace lexer
    {
        class Token
        {
            private:
                const TokenType _type;
                const std::pair<size_t, size_t> _lines, _pos;

            public:
                Token(TokenType type, std::pair<size_t, size_t> lines,
                      std::pair<size_t, size_t> pos);
                ~Token();

                TokenType type() const;
                std::pair<size_t, size_t> lines() const;
                std::pair<size_t, size_t> pos() const;
        };
    }
}

#endif //TESSLANG_TOKEN_HXX