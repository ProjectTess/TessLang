//
// Created by tess on 3/29/26.
//

#include <utility>
#include <format>
#include <stdexcept>
#include <tess/lexer/Lexer.hxx>

using namespace tess::lexer;

Lexer::Lexer(std::string sourceCode): _line(1), _col(1), _pos(0),
                                      _maxSize(sourceCode.size()),
                                      _sourceCode(
                                          std::move(sourceCode))
{
}

Lexer::~Lexer() = default;

bool Lexer::isValid(long at) const
{
    const long pos = static_cast<long>(this->_pos) + at;
    return std::cmp_greater_equal(pos, 0) && std::cmp_less(
               pos, this->_maxSize);
}

bool Lexer::isDigit(long at) const
{
    return this->isValid(at) && std::isdigit(
               static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isAlpha(long at) const
{
    return this->isValid(at) && std::isalpha(
               static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isAlphaOrNum(long at) const
{
    return this->isValid(at) && std::isalnum(
               static_cast<unsigned char>(this->peek(at)));
}

bool Lexer::isSpace(long at) const
{
    return this->isValid(at) && std::isspace(
               static_cast<unsigned char>(this->peek(at)));
}

void Lexer::advance()
{
    if(!this->isValid())
        return;

    if(this->peek() == '\n')
    {
        this->_line++;
        this->_col = 1;
    }
    else
        this->_col++;

    this->_pos++;
}

char Lexer::peek(long to) const
{
    return !this->isValid(to)
               ? '\0'
               : this->_sourceCode[
                   static_cast<long>(this->_pos) + to ];
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
        auto stLine = this->_line;
        auto stCol = this->_col == 0 ? this->_col : this->_col - 1;

        switch(this->peek())
        {
            default:
                if(this->isDigit())
                {
                    std::string buf;
                    while(this->isDigit() || this->peek() == '.')
                    {
                        if(buf.find('.') != std::string::npos)
                        {
                            if(stLine == this->_line)
                                throw std::runtime_error(
                                    std::format(
                                        "Invalid floating-point number type at line: {}, pos {} - {}: {}{}",
                                        stLine, stCol, this->_col, buf, this->take()));
                            throw std::runtime_error(std::format(
                                "Invalid floating-point number type at lines: {} - {}, pos {} - {}: {}{}",
                                stLine, this->_line, stCol,
                                this->_col, buf, this->take()));
                        }

                        buf += this->take();
                    }

                    tokens.push_back(
                        Token(NumberLiteral(std::move(buf), this->take()),
                              { stLine, this->_line },
                              { stCol, this->_col }));
                    break;
                }
                else if(this->isAlpha())
                {
                    std::string buf;
                    while(this->isAlphaOrNum() || this->peek() == '_')
                        buf += this->take();

                    if(auto kw = representation::keywords::AS_STR.find(buf);
                        kw != representation::keywords::AS_STR.end())
                    {
                        tokens.push_back(Token(kw->second, { stLine, this->_line },
                                               { stCol, this->_col }));
                        break;
                    }

                    tokens.push_back(Token(Identifier(buf), { stLine, this->_line },
                                           { stCol, this->_col }));
                    break;
                }
                else
                {
                    std::string buf;
                    while(!this->isSpace())
                        buf += this->take();

                    if(stLine == this->_line)
                        throw std::runtime_error(std::format(
                            "Unknown characters at line: {}, pos: {} - {}: {}", stLine,
                            stCol, this->_col, buf));
                    throw std::runtime_error(std::format(
                        "Unknown characters at lines: {} - {}, pos: {} - {}: {}", stLine,
                        this->_line, stCol, this->_col, buf));
                }

            case '\n':
            case '\r':
            case '\t':
            case ' ':
                this->advance();
                break;

            case '+':
                this->take();
                tokens.push_back(Token(Plus(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '-':
                this->take();
                tokens.push_back(Token(Minus(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '*':
                this->take();
                tokens.push_back(Token(Asterisk(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '/':
                this->take();
                tokens.push_back(Token(Slash(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '{':
                this->take();
                tokens.push_back(Token(LeftBrace(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '}':
                this->take();
                tokens.push_back(Token(RightBrace(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '(':
                this->take();
                tokens.push_back(Token(LeftParen(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case ')':
                this->take();
                tokens.push_back(Token(RightParen(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '[':
                this->take();
                tokens.push_back(Token(LeftBracket(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case ']':
                this->take();
                tokens.push_back(Token(RightBracket(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '.':
                this->take();
                tokens.push_back(Token(Dot(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case ',':
                this->take();
                tokens.push_back(Token(Comma(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case ':':
                this->take();
                tokens.push_back(Token(Colon(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case ';':
                this->take();
                tokens.push_back(Token(Semicolon(),
                                       { stLine, this->_line },
                                       { stCol, this->_col }));
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

                        if(esc == representation::escapes::AS_ESC.end())
                        {
                            if(stLine == this->_line)
                                throw std::runtime_error(std::format(
                                    "Invalid escape sequence at line: {}, pos: {} - {}: {}",
                                    stLine, stCol, this->_col,
                                    "\\" + std::to_string(value)));
                            throw std::runtime_error(std::format(
                                "Invalid escape sequence at lines: {} - {}, pos: {} - {}: {}",
                                stLine, this->_line, stCol, this->_col,
                                "\\" + std::to_string(value)));

                        }

                        if(esc->second == '\'')
                        {
                            if(stLine == this->_line)
                                throw std::runtime_error(std::format(
                                    "Char-variable's value cannot be empty at line: {}, pos: {} - {}",
                                    stLine, stCol, this->_col));
                            throw std::runtime_error(std::format(
                                "Char-variable's value cannot be empty at lines: {} - {}, pos: {} - {}",
                                stLine, this->_line, stCol, this->_col));
                        }

                        value = esc->second;
                        break;
                }

                if(this->peek() != '\'')
                {
                    auto buf = std::string(1, value);
                    while(this->isValid() && this->peek() != '\'')
                    {
                        buf += this->take();
                    }

                    if(!this->isValid())
                    {
                        if(stLine == this->_line)
                            throw std::runtime_error(std::format(
                                "Unclosed char literal at line: {}, pos: {} - {}",
                                stLine, stCol, this->_col));
                        throw std::runtime_error(std::format(
                            "Unclosed char literal at lines: {} - {}, pos: {} - {}",
                            stLine, this->_line, stCol, this->_col));

                    }

                    if(stLine == this->_line)
                        throw std::runtime_error(std::format(
                            "Invalid char value at line: {}, pos: {} - {}: {}", stLine,
                            stCol, this->_col, value));
                    throw std::runtime_error(std::format(
                        "Invalid char at lines: {} - {}, pos: {} - {}: {}", stLine,
                        this->_line, stCol, this->_col, value));
                }

                this->advance();
                tokens.push_back(Token(CharLiteral(value), { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
            case '"':
                this->advance();

                std::string buf;
                while(this->isValid() && this->peek() != '"')
                {
                    buf += this->take();
                }

                if(!this->isValid())
                {
                    if(stLine == this->_line)
                        throw std::runtime_error(std::format(
                            "Unclosed string literal at line: {}, pos: {} - {}", stLine,
                            stCol, this->_col));

                    throw std::runtime_error(std::format(
                        "Unclosed string literal at lines: {} - {}, pos: {} - {}", stLine,
                        this->_line, stCol, this->_col));
                }

                this->advance();
                tokens.push_back(Token(StringLiteral(buf), { stLine, this->_line },
                                       { stCol, this->_col }));
                break;
        }
    }

    return tokens;
}