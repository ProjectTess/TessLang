//
// Created by tess on 3/29/26.
//

#include <format>
#include <tess/errors/AlreadyUsedDecimalPointError.hxx>
#include <tess/errors/DecimalPointNotFollowedDigitError.hxx>
#include <tess/errors/EmptyValueError.hxx>
#include <tess/errors/FloatingPointNumberWithoutDecimalPointError.hxx>
#include <tess/errors/IntegralNumberWithDecimalPointError.hxx>
#include <tess/errors/InvalidArgError.hxx>
#include <tess/errors/InvalidBaseWithDecimalPointError.hxx>
#include <tess/errors/InvalidEscapeSeqError.hxx>
#include <tess/errors/OutOfRangeError.hxx>
#include <tess/errors/UnclosedLiteralError.hxx>
#include <tess/errors/UnexpectedCharsError.hxx>
#include <tess/lexer/Lexer.hxx>
#include <utility>

using namespace tess::lexer;
using namespace tess::lexer::token;
using namespace tess::error;

Lexer::Lexer(std::string code):
  __ln(1),
  __col(1),
  __pos(0),
  __maxPos(code.size()),
  __code(std::move(code))
{
}

Lexer::~Lexer() noexcept = default;

bool Lexer::isValid(const long at) const
{
  const long pos = static_cast<long>(this->__pos) + at;
  return std::cmp_greater_equal(pos, 0) && std::cmp_less(pos, this->__maxPos);
}

bool Lexer::isDigit(const long at) const
{
  return this->isValid(at) && std::isdigit(static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isAlpha(const long at) const
{
  return this->isValid(at) && std::isalpha(static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isAlphaOrNum(const long at) const
{
  return this->isValid(at) && std::isalnum(static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isSpace(const long at) const
{
  return this->isValid(at) && std::isspace(static_cast<unsigned char>(this->peek(at)));
}

void Lexer::advance(unsigned long toPos)
{
  while(toPos > 0)
  {
    if(!this->isValid())
      return;

    if(this->peek() == '\n')
    {
      this->__ln++;
      this->__col = 1;
    }
    else
      this->__col++;

    this->__pos++;
    --toPos;
  }
}

char Lexer::peek(const long toPos) const
{
  return !this->isValid(toPos) ? '\0' : this->__code[ static_cast<long>(this->__pos) + toPos ];
}

char Lexer::take()
{
  if(!this->isValid())
    return '\0';

  this->advance();
  return this->peek(-1);
}

std::vector<Token> Lexer::tokenize()
{
  std::vector<Token> tokens;
  while(this->isValid())
  {
    auto stLn = this->__ln;
    auto stCol = this->__col == 0 ? this->__col : this->__col - 1;

    switch(this->peek())
    {
      default:
        if(this->isDigit())
        {
          std::string buf;

          int8_t base = 10;
          bool hasPoint = false;
          bool incompatibleBaseWithFloat = false;
          bool doublePointError = false;
          bool pointNotFollowedByDigit = false;

          if(this->peek() == '0')
          {
            switch(this->peek(1))
            {
              default:
                break;

              case 'b':
              case 'B':
                base = 2;
                this->advance(2);
                break;

              case 'o':
              case 'O':
                base = 8;
                this->advance(2);
                break;

              case 'x':
              case 'X':
                base = 16;
                this->advance(2);
                break;
            }
          }

          auto isValidNum = [ base ](const char ch) -> bool
          {
            switch(base)
            {
              default:
                return false;

              case 2:
                return ch == '0' || ch == '1';
              case 8:
                return ch >= '0' && ch <= '7';
              case 10:
                return std::isdigit(static_cast<unsigned char>(ch));
              case 16:
                return std::isxdigit(static_cast<unsigned char>(ch));
            }
          };

          while(
            this->isValid() && (isValidNum(this->peek()) || (base == 10 && this->peek() == '.')))
          {
            if(this->peek() == '.')
            {
              incompatibleBaseWithFloat = base != 10;
              doublePointError = hasPoint;
              pointNotFollowedByDigit = !this->isDigit(1);

              hasPoint = true;
            }

            buf += this->take();
          }

          if(this->peek() == '_')
            while(this->peek() == '_')
              this->advance();

          char suffix;
          switch(this->peek())
          {
            default:
              suffix = 'l';
              break;

            case 'b':
            case 's':
            case 'i':
            case 'l':
            case 'B':
            case 'S':
            case 'I':
            case 'L':
            case 'f':
            case 'd':
              suffix = this->take();
              break;
          }

          const TokenPosition pos { { stLn, this->__ln }, { stCol, this->__col } };

          if(incompatibleBaseWithFloat)
            throw InvalidBaseWithDecimalPointError(pos, std::move(buf));
          if(doublePointError)
            throw AlreadyUsedDecimalPointError(pos, std::move(buf));
          if(pointNotFollowedByDigit)
            throw DecimalPointNotFollowedDigitError(pos, std::move(buf));
          if(buf.empty())
            throw EmptyValueError(pos, "numerical");

          if((suffix == 'b' || suffix == 'B' || suffix == 's' || suffix == 'S' || suffix == 'i'
              || suffix == 'I' || suffix == 'l' || suffix == 'L')
             && hasPoint)
            throw IntegralNumberWithDecimalPointError(std::move(pos), std::move(buf));
          if((suffix == 'f' || suffix == 'd') && !hasPoint)
            throw FloatingPointNumberWithoutDecimalPointError(std::move(pos), std::move(buf));

          auto convert = [ base, pos ]<typename T0>(std::string _buf) -> T0
          {
            using T1 = std::decay_t<T0>;
            using T2 = std::conditional_t<
              std::is_same_v<T1, int8_t>, int16_t,
              std::conditional_t<std::is_same_v<T1, uint8_t>, uint16_t, T1>
            >;

            T2 value;
            std::from_chars_result res;

            if constexpr(std::is_same_v<T2, float> || std::is_same_v<T2, double>)
              res = std::from_chars(
                _buf.data(), _buf.data() + _buf.size(), value, std::chars_format::general);
            else
              res = std::from_chars(_buf.data(), _buf.data() + _buf.size(), value, base);

            if(res.ec != std::errc())
            {
              if(res.ec == std::errc::invalid_argument)
                throw InvalidArgError(std::move(pos), "number", std::move(_buf));
              if(res.ec == std::errc::result_out_of_range)
                throw OutOfRangeError(std::move(pos), std::move(_buf));
            }

            if constexpr(std::is_same_v<T1, int8_t>)
            {
              if(value < -128 || value > 127)
                throw OutOfRangeError(std::move(pos), std::move(_buf));

              return static_cast<int8_t>(value);
            }
            else if constexpr(std::is_same_v<T1, uint8_t>)
            {
              if(value > 255)
                throw OutOfRangeError(std::move(pos), std::move(_buf));

              return static_cast<uint8_t>(value);
            }
            else
              return value;
          };

          switch(suffix)
          {
            case 'b':
              tokens.emplace_back(
                I8Literal(convert.operator()<int8_t>(std::move(buf))), std::move(pos));
              break;
            case 'B':
              tokens.emplace_back(
                U8Literal(convert.operator()<uint8_t>(std::move(buf))), std::move(pos));
              break;
            case 's':
              tokens.emplace_back(
                I16Literal(convert.operator()<int16_t>(std::move(buf))), std::move(pos));
              break;
            case 'S':
              tokens.emplace_back(
                U16Literal(convert.operator()<uint16_t>(std::move(buf))), std::move(pos));
              break;
            case 'i':
              tokens.emplace_back(
                I32Literal(convert.operator()<int32_t>(std::move(buf))), std::move(pos));
              break;
            case 'I':
              tokens.emplace_back(
                U32Literal(convert.operator()<uint32_t>(std::move(buf))), std::move(pos));
              break;
            default:
            case 'l':
              tokens.emplace_back(
                I64Literal(convert.operator()<int64_t>(std::move(buf))), std::move(pos));
              break;
            case 'L':
              tokens.emplace_back(
                U64Literal(convert.operator()<uint64_t>(std::move(buf))), std::move(pos));
              break;
            case 'f':
              tokens.emplace_back(
                FloatLiteral(convert.operator()<float>(std::move(buf))), std::move(pos));
              break;
            case 'd':
              tokens.emplace_back(
                DoubleLiteral(convert.operator()<double>(std::move(buf))), std::move(pos));
              break;
          }

          break;
        }
        else if(this->isAlpha() || this->peek() == '_')
        {
          std::string buf;
          while(this->isAlphaOrNum() || this->peek() == '_')
            buf += this->take();

          const TokenPosition pos { { stLn, this->__ln }, { stCol, this->__col } };

          if(buf == "true")
          {
            tokens.emplace_back(BoolLiteral(true), std::move(pos));
            break;
          }
          if(buf == "false")
          {
            tokens.emplace_back(BoolLiteral(false), std::move(pos));
            break;
          }

          if(auto kw = representation::keywords::AS_STR.find(buf);
             kw != representation::keywords::AS_STR.end())
          {
            tokens.emplace_back(kw->second, std::move(pos));
            break;
          }

          tokens.emplace_back(Identifier(std::move(buf)), std::move(pos));
          break;
        }
        else
        {
          std::string buf;
          while(!this->isSpace())
            buf += this->take();

          throw UnexpectedCharsError(
            { { stLn, this->__ln }, { stCol, this->__col } }, std::move(buf));
        }

      case '\n':
      case '\r':
      case '\t':
      case ' ':
        this->advance();
        break;

      case '+':
        this->take();
        tokens.push_back({ Plus(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '-':
        this->take();
        tokens.push_back({ Minus(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '*':
        this->take();
        tokens.push_back({ Asterisk(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '/':
        this->take();
        tokens.push_back({ Slash(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '{':
        this->take();
        tokens.push_back({ LeftBrace(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '}':
        this->take();
        tokens.push_back({ RightBrace(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '(':
        this->take();
        tokens.push_back({ LeftParen(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case ')':
        this->take();
        tokens.push_back({ RightParen(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '[':
        this->take();
        tokens.push_back({ LeftBracket(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case ']':
        this->take();
        tokens.push_back({ RightBracket(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '.':
        this->take();
        tokens.push_back({ Dot(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case ',':
        this->take();
        tokens.push_back({ Comma(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case ':':
        this->take();
        tokens.push_back({ Colon(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case ';':
        this->take();
        tokens.push_back({ Semicolon(), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;

      case '\'':
        this->advance();

        char value;
        switch(this->peek())
        {
          default:
            value = this->take();
            break;

          case '\\':
            this->advance();

            value = this->take();
            auto esc = representation::escapes::AS_ESC.find(value);

            const TokenPosition pos { { stLn, this->__ln }, { stCol, this->__col } };

            if(esc == representation::escapes::AS_ESC.end())
            {
              throw InvalidEscapeSeqError(std::move(pos), "\\" + std::to_string(value));
            }

            if(esc->second == '\'')
              throw EmptyValueError(std::move(pos), "char");

            value = esc->second;
            break;
        }

        if(this->peek() != '\'')
        {
          auto buf = std::string(1, value);
          while(this->isValid() && this->peek() != '\'')
            buf += this->take();

          const TokenPosition pos { { stLn, this->__ln }, { stCol, this->__col } };

          if(!this->isValid())
            throw UnclosedLiteralError(std::move(pos), "char");

          throw InvalidArgError(std::move(pos), "char", std::move(buf));
        }

        this->advance();
        tokens.push_back({ CharLiteral(value), { { stLn, this->__ln }, { stCol, this->__col } } });
        break;
      case '"':
        this->advance();

        std::string buf;
        while(this->isValid() && this->peek() != '"')
        {
          buf += this->take();
        }

        const TokenPosition pos { { stLn, this->__ln }, { stCol, this->__col } };

        if(!this->isValid())
          throw UnclosedLiteralError(std::move(pos), "string");

        this->advance();
        tokens.emplace_back( StringLiteral(std::move(buf)), std::move(pos) );
        break;
    }
  }

  return tokens;
}