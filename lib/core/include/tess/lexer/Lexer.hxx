//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_LEXER_HXX
#define TESSLANG_LEXER_HXX

#include <vector>
#include <tess/lexer/Token.hxx>

namespace tess
{
    namespace lexer
    {
        class Lexer
        {
            private:
                size_t _line, _col, _pos;
                const size_t _maxSize;
                const std::string _sourceCode;

                bool isValid(long at = 0) const;

                bool isDigit(long at = 0) const;
                bool isAlpha(long at = 0) const;
                bool isAlphaOrNum(long at = 0) const;
                bool isSpace(long at = 0) const;

                void advance();

                char peek(long to = 0) const;
                char take();

            public:
                explicit Lexer(std::string sourceCode);
                ~Lexer();

                std::vector<Token> tokenize();
        };
    }
}

#endif //TESSLANG_LEXER_HXX