#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <zconf.h>
#include "headers/Lexer.hpp"
#include "headers/Operand.hpp"
#include "headers/AbstractVM.hpp"

std::string name;

void read_from_file(char* file_name)
{

    AbstractVM *VM = new AbstractVM(1);
    int i = 0;
    std::ifstream file_reader;
    file_reader.open(file_name);
    std::string line;

    while (std::getline(file_reader, line)) {
        i++;
        try {
            VM->analyze_line(line);
            if(VM->get_exit_flag()) {
                break;
            }
        }
        catch (std::exception &e)
        {
            printf("Error on line : %d - ", i);
            printf("%s\n", e.what());

        }
    }
    if(!VM->get_exit_flag()) {
        delete (VM);
        printf("Error on line : %d - ", i);
        throw NonExit();
    }
    delete (VM);
}

int read_input() {

    std::string line;
    auto *VM = new AbstractVM(0);

    std::cout << "Write correct command and " << name << " program will be started\n\n";

    while (std::getline (std::cin,line))
    {
        try {
            VM->analyze_line(line);
            if(VM->get_exit_flag()) {
                delete (VM);
                std::cout << "\nIf you want close VM write ;;\n";
                std::cout << "If you want continue Write the name of program\n";
                std::getline (std::cin,line);
                if (line == ";;") {
                    return 0;
                }
                else {
                    name = line;
                    return 1;
                }
            }
        }
        catch (std::exception &e)
        {
            printf("Error : ");
            printf("%s", e.what());
            printf(" - Try one more time\n");
        }
    }
    return 0;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "If you want continue Write the name of program\n";
        std::getline (std::cin,name);

        while (read_input() == 1);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            std::cout << argv[i] << std::endl;
            try {
                read_from_file(argv[i]);
            }
            catch (std::exception &e)
            {
                printf("%s\n", e.what());
            }
        }
    }
    sleep(15);
    return 0;
}



