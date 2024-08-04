#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

#include "generation.h"

int main(int argc, char* argv[])
{
    std::string inputFile;
    
    std::cout << "Enter file name: ";
    std::cin >> inputFile;
    if (inputFile.size() < 4 || inputFile[inputFile.size() - 1] != 'k' || inputFile[inputFile.size() - 2] != 'k' ||
        inputFile[inputFile.size() - 3] != '.')
        exit(EXIT_FAILURE);

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(inputFile, std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value()) {
        std::cerr << "Invalid program" << std::endl;
        exit(EXIT_FAILURE);
    }

    {
        Generator generator(prog.value());
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }
    system("bash");

    return EXIT_SUCCESS;
}