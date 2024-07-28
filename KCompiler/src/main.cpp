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
    std::optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value())
    {
        std::cerr << "No exitr statment found";
        exit(EXIT_FAILURE);
    }

    Generator generator(prog.value());


    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}