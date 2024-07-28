#include<iostream>
#include<fstream>
#include<sstream>
#include<optional>
#include<vector>

enum class TokenType
{
    _return,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};

std::vector<Token> tokenize(const std::string& str) {
    std::vector<Token> tokens = {};

    std::string buffer;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        if (isalpha(c)) {
            buffer.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buffer.push_back(str.at(i));
                i++;
            }
            i--;

            if (buffer == "return") {
                Token token;
                token.type = TokenType::_return;
                tokens.push_back(token);
                buffer.clear();
                continue;
            }
            else {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        else if (std::isdigit(c)) {
            buffer.push_back(c);
            i++;
            while (std::isdigit(str.at(i)))
            {
                buffer.push_back(str.at(i));
                i++;
            }
            i--;

            Token token;
            token.type = TokenType::int_lit;
            token.value = buffer;
            tokens.push_back(token);
        }
        else if (c == ';')
        {
            Token token;
            token.type = TokenType::semi;
            tokens.push_back(token);
        }

        else if (std::isspace(c)) {
            continue;
        }
        else {
            std::cerr << "You messed up!" << std::endl;

        }
    }

    return tokens;
}

int main(int argc, char* argv[]) {

    std::string contents;

    {
        std::stringstream contents_stream;
        std::fstream input("test.hy", std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::vector<Token> tokens = tokenize(contents);
    std::cout << tokens.size();
    return EXIT_SUCCESS;
}