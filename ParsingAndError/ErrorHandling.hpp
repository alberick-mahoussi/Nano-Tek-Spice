/*
** EPITECH PROJECT, 2023
** nanotekspice
** File description:
** file
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cerrno>

class chip {
    public:
        chip(){};
        ~chip(){};
        std::string type;
        std::string value;
};

class link {
    public:
        link(){};
        ~link(){};
        std::string chip_one;
        std::string chip_one_val;
        std::string chip_two;
        std::string chip_two_val;
};

namespace nts
{
    class Parsing {
        private:
            std::string file_nts;
        public:
            std::vector<std::string> nts_line;
            std::vector<link> links;
            std::vector<chip> chips;
            Parsing(std::string file) {
                file_nts = file;
                error_checker();    
            };
            ~Parsing(){};
            void get_all_line();
            void get_info_chipset();
            bool verify_components(std::string type);
            bool exits(std::string value);
            void get_info_link();
            void error_checker();
            bool check_empty_line(std::string line);
            bool new_component(std::string component);
    };

    class ErrorHandling : public std::exception {
        public:
            ErrorHandling(const std::string &error) : _error(error) {}
            ~ErrorHandling() = default;
            const char* what() const noexcept { return _error.c_str(); }
        private:
            std::string _error;
    };
};

#endif /* !ERRORHANDLING_HPP_ */
