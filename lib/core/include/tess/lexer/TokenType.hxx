//
// Created by tess on 3/29/26.
//

#ifndef TESSLANG_TOKENTYPE_HXX
#define TESSLANG_TOKENTYPE_HXX

#include <cstdint>
#include <map>
#include <string>
#include <variant>

namespace tess
{
  namespace lexer
  {
    namespace token
    {

      enum class Keyword
      {
        If,
        Elif,
        Else,
        Return,
        Include,
        Switch,
        Case
      };

      namespace representation
      {
        namespace keywords
        {

          inline const std::map<std::string, Keyword> AS_STR {
            { "if", Keyword::If },           { "elif", Keyword::Elif },
            { "else", Keyword::Else },       { "ret", Keyword::Return },
            { "include", Keyword::Include }, { "switch", Keyword::Switch },
            { "case", Keyword::Case }
          };

          inline const std::map<Keyword, std::string> AS_KW {
            { Keyword::If, "if" },           { Keyword::Elif, "elif" },
            { Keyword::Else, "else" },       { Keyword::Return, "ret" },
            { Keyword::Include, "include" }, { Keyword::Switch, "switch" },
            { Keyword::Case, "case" }
          };

        }   // namespace keywords

        namespace escapes
        {

          inline const std::map<char, char> AS_ESC {
            { '0', '\0' }, { '\\', '\\' }, { '\'', '\'' }, { '"', '\"' },
            { 'a', '\a' }, { 'b', '\b' },  { 'f', '\f' },  { 't', '\t' },
            { 'n', '\n' }, { 'r', '\r' },  { 'v', '\v' }
          };

          inline const std::map<char, std::string> AS_STR {
            { '\0', "\\0" }, { '\\', "\\\\" }, { '\'', "'" },   { '"', "\"" },   { '\a', "\\a" },
            { '\b', "\\b" }, { '\f', "\\f" },  { '\t', "\\t" }, { '\n', "\\n" }, { '\v', "\\v" }
          };

        }   // namespace escapes
      }   // namespace representation

      class Plus
      {
        public:
          Plus() = default;
          ~Plus() = default;

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
          {
            return "Slash";
          }

          auto operator<=>(const Slash&) const = default;
      };

      class Assign
      {
        public:
          Assign() = default;
          ~Assign() = default;

          static std::string toString()
          {
            return "Assign";
          }

          auto operator<=>(const Assign&) const = default;
      };

      class LeftBrace
      {
        public:
          LeftBrace() = default;
          ~LeftBrace() = default;

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
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

          static std::string toString()
          {
            return "Semicolon";
          }

          auto operator<=>(const Semicolon&) const = default;
      };

      class Identifier
      {
        private:
          std::string __attr;

        public:
          explicit Identifier(std::string attr):
            __attr(std::move(attr))
          {
          }

          ~Identifier() = default;

          std::string attr() const
          {
            return this->__attr;
          }

          auto operator<=>(const Identifier& other) const = default;
      };

      template<typename T>
      class Literal
      {
        private:
          T __attr;

        public:
          explicit Literal(T attr):
            __attr(attr)
          {
          }

          ~Literal() noexcept = default;

          T attr() const
          {
            return this->__attr;
          }

          auto operator<=>(const Literal&) const = default;
      };

      using CharLiteral = Literal<char>;
      using BoolLiteral = Literal<bool>;
      using I8Literal = Literal<int8_t>;
      using U8Literal = Literal<uint8_t>;
      using I16Literal = Literal<int16_t>;
      using U16Literal = Literal<uint16_t>;
      using I32Literal = Literal<int32_t>;
      using U32Literal = Literal<uint32_t>;
      using I64Literal = Literal<int64_t>;
      using U64Literal = Literal<uint64_t>;
      using FloatLiteral = Literal<float>;
      using DoubleLiteral = Literal<double>;
      using StringLiteral = Literal<std::string>;

      using TokenType = std::variant<
        Keyword,
        Plus,
        Minus,
        Asterisk,
        Assign,
        Slash,
        LeftBrace,
        RightBrace,
        LeftParen,
        RightParen,
        LeftBracket,
        RightBracket,
        Dot,
        Comma,
        Colon,
        Semicolon,
        Identifier,
        CharLiteral,
        BoolLiteral,
        I8Literal,
        U8Literal,
        I16Literal,
        U16Literal,
        I32Literal,
        U32Literal,
        I64Literal,
        U64Literal,
        FloatLiteral,
        DoubleLiteral,
        StringLiteral
      >;

      class TokenVisitor
      {
        public:
          template<typename T>
          std::string operator()(const T& arg) const
          {
            if constexpr(requires { std::decay_t<T>::toString(); })
              return std::decay_t<T>::toString();
            else if constexpr(requires { arg.attr(); })
            {
              using T0 = std::decay_t<T>;
              if constexpr(std::is_same_v<T0, Identifier>)
                return "Identifier: " + arg.attr();
              else if constexpr(std::is_same_v<T0, CharLiteral>)
              {
                auto ch = arg.attr();
                if(auto esc = representation::escapes::AS_STR.find(ch);
                   esc != representation::escapes::AS_STR.end())
                  return "Char Literal: " + esc->second;

                return "Char Literal: " + std::to_string(ch);
              }
              else if constexpr(std::is_same_v<T0, BoolLiteral>)
                return "Bool Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, I8Literal>)
                return "I8 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, U8Literal>)
                return "U8 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, I16Literal>)
                return "I16 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, U16Literal>)
                return "U16 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, I32Literal>)
                return "I32 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, U32Literal>)
                return "U32 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, I64Literal>)
                return "I64 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, U64Literal>)
                return "U64 Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, FloatLiteral>)
                return "Float Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, DoubleLiteral>)
                return "Double Literal: " + std::to_string(arg.attr());
              else if constexpr(std::is_same_v<T0, StringLiteral>)
                return "String Literal: " + arg.attr();
              else
                return "Other Literal: " + arg.attr();
            }
            else
              return "Unknown";
          }

          std::string operator()(const Keyword& arg) const
          {
            std::string result = "Unknown";
            if(const auto kw = representation::keywords::AS_KW.find(arg);
               kw != representation::keywords::AS_KW.end())
              result = kw->second;

            return "Keyword: " + result;
          }
      };

    }   // namespace token
  }   // namespace lexer
}   // namespace tess

#endif   // TESSLANG_TOKENTYPE_HXX