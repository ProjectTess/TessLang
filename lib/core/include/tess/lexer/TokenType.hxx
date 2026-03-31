//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_TOKENTYPE_HXX
#define TESSLANG_TOKENTYPE_HXX

#include <map>
#include <string>
#include <variant>

namespace tess
{
    namespace lexer
    {
        enum class Keyword
        {
            If,
            Elif,
            Else,
            Return,
        };

        namespace representation
        {
            namespace keywords
            {
                inline const std::map<std::string, Keyword> AS_STR{
                    { "if", Keyword::If },
                    { "elif", Keyword::Elif },
                    { "else", Keyword::Else },
                    { "ret", Keyword::Return }
                };

                inline const std::map<Keyword, std::string> AS_KW{
                    { Keyword::If, "if" },
                    { Keyword::Elif, "elif" },
                    { Keyword::Else, "else" },
                    { Keyword::Return, "ret" }
                };
            }

            namespace escapes
            {
                inline const std::map<char, char> AS_ESC{
                    { '0', '\0' },
                    { '\\', '\\' },
                    { '\'', '\'' },
                    { '"', '\"' },
                    { 'a', '\a' },
                    { 'b', '\b' },
                    { 'f', '\f' },
                    { 't', '\t' },
                    { 'n', '\n' },
                    { 'r', '\r' },
                    { 'v', '\v' }
                };

                inline const std::map<std::string, std::string> AS_STR{
                    { "\0", "\\0" },
                    { "\\", "\\\\" },
                    { "'", "\\'" },
                    { "\"", "\\\"" },
                    { "\a", "\\a" },
                    { "\b", "\\b" },
                    { "\f", "\\f" },
                    { "\t", "\\t" },
                    { "\n", "\\n" },
                    { "\v", "\\v" }
                };
            }
        }

        class Plus
        {
            public:
                Plus() = default;
                ~Plus() = default;

                std::string toString() const
                {
                    return "Plus";
                }

                auto operator<=>(const Plus&) const = default;
        };

        class Minus
        {
            public:
                Minus() = default;
                ~Minus() = default;

                std::string toString() const
                {
                    return "Minus";
                }

                auto operator<=>(const Minus&) const = default;
        };

        class Asterisk
        {
            public:
                Asterisk() = default;
                ~Asterisk() = default;

                std::string toString() const
                {
                    return "Asterisk";
                }

                auto operator<=>(const Asterisk&) const = default;
        };

        class Slash
        {
            public:
                Slash() = default;
                ~Slash() = default;

                std::string toString() const
                {
                    return "Slash";
                }

                auto operator<=>(const Slash&) const = default;
        };

        class LeftBrace
        {
            public:
                LeftBrace() = default;
                ~LeftBrace() = default;

                std::string toString() const
                {
                    return "Left Brace";
                }

                auto operator<=>(const LeftBrace&) const = default;
        };

        class RightBrace
        {
            public:
                RightBrace() = default;
                ~RightBrace() = default;

                std::string toString() const
                {
                    return "Right Brace";
                }

                auto operator<=>(const RightBrace&) const = default;
        };

        class LeftParen
        {
            public:
                LeftParen() = default;
                ~LeftParen() = default;

                std::string toString() const
                {
                    return "Left Paren";
                }

                auto operator<=>(const LeftParen&) const = default;
        };

        class RightParen
        {
            public:
                RightParen() = default;
                ~RightParen() = default;

                std::string toString() const
                {
                    return "Right Paren";
                }

                auto operator<=>(const RightParen&) const = default;
        };

        class LeftBracket
        {
            public:
                LeftBracket() = default;
                ~LeftBracket() = default;

                std::string toString() const
                {
                    return "Left Bracket";
                }

                auto operator<=>(const LeftBracket&) const = default;
        };

        class RightBracket
        {
            public:
                RightBracket() = default;
                ~RightBracket() = default;

                std::string toString() const
                {
                    return "Right Bracket";
                }

                auto operator<=>(const RightBracket&) const = default;
        };

        class Dot
        {
            public:
                Dot() = default;
                ~Dot() = default;

                std::string toString() const
                {
                    return "Dot";
                }

                auto operator<=>(const Dot&) const = default;
        };

        class Comma
        {
            public:
                Comma() = default;
                ~Comma() = default;

                std::string toString() const
                {
                    return "Comma";
                }

                auto operator<=>(const Comma&) const = default;
        };

        class Colon
        {
            public:
                Colon() = default;
                ~Colon() = default;

                std::string toString() const
                {
                    return "Colon";
                }

                auto operator<=>(const Colon&) const = default;
        };

        class Semicolon
        {
            public:
                Semicolon() = default;
                ~Semicolon() = default;

                std::string toString() const
                {
                    return "Semicolon";
                }

                auto operator<=>(const Semicolon&) const = default;
        };

        class Identifier
        {
            private:
                std::string _value;

            public:
                explicit Identifier(std::string value): _value(
                    std::move(value))
                {
                }

                ~Identifier() = default;

                std::string toString() const
                {
                    return "Identifier: " + this->_value;
                }

                auto operator<=>(const Identifier& other) const
                = default;
        };

        class CharLiteral
        {
            private:
                char _value;

            public:
                explicit CharLiteral(char value): _value(value)
                {
                }

                ~CharLiteral() = default;

                std::string toString() const
                {
                    std::string result = { this->_value };
                    if(auto esc = representation::escapes::AS_STR.find(result);
                        esc != representation::escapes::AS_STR.end())
                        result = esc->second;

                    return "Char Literal: " + result;
                }

                auto operator<=>(const CharLiteral& other) const
                = default;
        };

        class BoolLiteral
        {
            private:
                bool _value;

            public:
                explicit BoolLiteral(bool value): _value(value)
                {
                }

                ~BoolLiteral() = default;

                std::string toString() const
                {
                    return "Bool Literal: " + std::to_string(
                               this->_value);
                }

                auto operator<=>(const BoolLiteral& other) const
                = default;
        };

        class StringLiteral
        {
            private:
                std::string _value;

            public:
                explicit StringLiteral(std::string value): _value(
                    std::move(value))
                {
                }

                ~StringLiteral() = default;

                std::string toString() const
                {
                    return "String Literal: " + this->_value;
                }

                auto operator<=>(const StringLiteral& other) const
                = default;
        };

        class NumberLiteral
        {
            private:
                std::string _value;
                char _suffix;

            public:
                explicit
                    NumberLiteral(std::string value, char suffix):
                    _value(std::move(value)), _suffix(suffix)
                {
                }

                ~NumberLiteral() = default;

                std::string toString() const
                {
                    return "Number Literal: " + this->_value +
                           std::to_string(this->_suffix);
                }
        };

        using TokenType = std::variant<
            Keyword, Plus, Minus, Asterisk, Slash, LeftBrace, RightBrace,
            LeftParen, RightParen, LeftBracket, RightBracket, Dot,
            Comma, Colon, Semicolon, Identifier, CharLiteral,
            BoolLiteral,
            StringLiteral, NumberLiteral
        >;

        class TokenVisitor
        {
            public:
                std::string operator()(const Plus& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Minus& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Asterisk& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Slash& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const LeftBrace& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const RightBrace& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const LeftParen& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const RightParen& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const LeftBracket& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const RightBracket& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Dot& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Comma& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Colon& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Semicolon& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Identifier& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const CharLiteral& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const BoolLiteral& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const StringLiteral& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const NumberLiteral& arg) const
                {
                    return arg.toString();
                }

                std::string operator()(const Keyword& arg) const
                {
                    std::string result = "Unknown";
                    if(auto kw = representation::keywords::AS_KW.find(arg);
                        kw != representation::keywords::AS_KW.end())
                        result = kw->second;

                    return "Keyword: " + result;
                }
        };
    } // namespace lexer
}     // namespace tess

#endif // TESSLANG_TOKENTYPE_HXX