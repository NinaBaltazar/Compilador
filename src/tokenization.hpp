#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <cassert>

enum class TokenType {
    exit,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    let,
    eq,
    plus,
    star,
    minus,
    fslash,
    open_curly,
    close_curly,
    if_,
    elif,
    else_,
};

inline std::string to_string(const TokenType type)
{
    switch (type) {
    case TokenType::exit:
        return "`exit`";
    case TokenType::int_lit:
        return "int literal";
    case TokenType::semi:
        return "`;`";
    case TokenType::open_paren:
        return "`(`";
    case TokenType::close_paren:
        return "`)`";
    case TokenType::ident:
        return "identifier";
    case TokenType::let:
        return "`let`";
    case TokenType::eq:
        return "`=`";
    case TokenType::plus:
        return "`+`";
    case TokenType::star:
        return "`*`";
    case TokenType::minus:
        return "`-`";
    case TokenType::fslash:
        return "`/`";
    case TokenType::open_curly:
        return "`{`";
    case TokenType::close_curly:
        return "`}`";
    case TokenType::if_:
        return "`if`";
    case TokenType::elif:
        return "`elif`";
    case TokenType::else_:
        return "`else`";
    }
    assert(false);
}

inline std::optional<int> bin_prec(const TokenType type)
{
    switch (type) {
    case TokenType::minus:
    case TokenType::plus:
        return 0;
    case TokenType::fslash:
    case TokenType::star:
        return 1;
    default:
        return {};
    }
}

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;
        int line_count = 1;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back(match_keyword(buf, line_count));
                buf.clear();
            }
            else if (std::isdigit(peek().value())) {
                tokens.push_back(tokenize_number(line_count));
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
                skip_line_comment();
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
                skip_block_comment();
            }
            else {
                tokens.push_back(tokenize_single_char(line_count));
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    Token match_keyword(const std::string& buf, int line_count)
    {
        if (buf == "exit") return { TokenType::exit, line_count };
        if (buf == "let") return { TokenType::let, line_count };
        if (buf == "if") return { TokenType::if_, line_count };
        if (buf == "elif") return { TokenType::elif, line_count };
        if (buf == "else") return { TokenType::else_, line_count };
        return { TokenType::ident, line_count, buf };
    }

    Token tokenize_number(int line_count)
    {
        std::string buf;
        while (peek().has_value() && std::isdigit(peek().value())) {
            buf.push_back(consume());
        }
        return { TokenType::int_lit, line_count, buf };
    }

    void skip_line_comment()
    {
        consume(); consume();
        while (peek().has_value() && peek().value() != '\n') {
            consume();
        }
    }

    void skip_block_comment()
    {
        consume(); consume();
        while (peek().has_value()) {
            if (peek().value() == '*' && peek(1).has_value() && peek(1).value() == '/') {
                break;
            }
            consume();
        }
        consume(); consume(); // To consume '*/'
    }

    Token tokenize_single_char(int line_count)
    {
        switch (consume()) {
        case '(':
            return { TokenType::open_paren, line_count };
        case ')':
            return { TokenType::close_paren, line_count };
        case ';':
            return { TokenType::semi, line_count };
        case '=':
            return { TokenType::eq, line_count };
        case '+':
            return { TokenType::plus, line_count };
        case '*':
            return { TokenType::star, line_count };
        case '-':
            return { TokenType::minus, line_count };
        case '/':
            return { TokenType::fslash, line_count };
        case '{':
            return { TokenType::open_curly, line_count };
        case '}':
            return { TokenType::close_curly, line_count };
        case '\n':
            line_count++;
            break;
        case ' ':
        case '\t':
            break;
        default:
            throw std::runtime_error("Invalid token");
        }
        return {};
    }

    [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};
