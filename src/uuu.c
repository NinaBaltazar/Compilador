#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
    _return,
    init_lint,
    semi
};

struct Token{
    TokenType type;
    std::optional<std::string> value;

};

std::vector<Token> tokenize(const std::string& str){
    for (int i = 0; i < str.length(); i++){
        char c = str.at(i)
    }
    
}

int main (int argc, char* argv[]){

    if (argc != 2){
        std::cerr << "Incorrect usage. Corret usage is ..." << std::endl;
        std::cerr << "P- <input.hy>" << std::endl;
        return EXIT_FAILURE;
    }

   std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    tokenize(contents);

    return EXIT_SUCCESS;
}