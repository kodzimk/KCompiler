#include<iostream>
#include<fstream>
#include<sstream>
#include<optional>
#include<vector>

#include"generation.h"


int main(int argc, char* argv[]) {

    std::string contents;

    {
        std::stringstream contents_stream;
        std::fstream input("test.kk", std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(tokens);
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value())
    {
        std::cerr << "No exitr statment found";
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());


    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}