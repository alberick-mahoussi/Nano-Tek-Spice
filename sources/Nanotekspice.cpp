/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-alberick.mahoussi
** File description:
** Nanotekspice
*/

#include "Nanotekspice.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <csignal>

nts::Nanotekspice::Nanotekspice(nts::Parsing *ns)
{
    _tick = 0;
    for (std::vector<chip>::size_type i = 0; i != ns->chips.size(); i++)
        _CircuitComponents[ns->chips[i].value] = createComponent(ns->chips[i].type, ns->chips[i].value);
    for (std::vector<chip>::size_type i = 0; i != ns->links.size(); i++) {
        _CircuitComponents[ns->links[i].chip_one].get()->setLink(stoi(ns->links[i].chip_one_val), *_CircuitComponents[ns->links[i].chip_two], stoi(ns->links[i].chip_two_val));
    }
}

nts::Nanotekspice::~Nanotekspice()
{
}

void nts::Nanotekspice::displayNano(nts::Parsing *ns)
{
    std::cout << "tick: " << _tick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (std::vector<chip>::size_type i = 0; i != ns->chips.size(); i++) {
        if (ns->chips[i].type == "input" || ns->chips[i].type == "clock") {
            std::string value = (_CircuitComponents[ns->chips[i].value].get()->compute(1) == -1) ? "U" : std::to_string(_CircuitComponents[ns->chips[i].value].get()->compute(1));
            std::cout << "  " << ns->chips[i].value << ": " <<  value << std::endl;
        }
    }
    std::cout << "output(s):" << std::endl;
    for (std::vector<chip>::size_type i = 0; i != ns->chips.size(); i++) {
        if (ns->chips[i].type == "output") {
            std::string value = (_CircuitComponents[ns->chips[i].value].get()->compute(1) == -1) ? "U" : std::to_string(_CircuitComponents[ns->chips[i].value].get()->compute(1));
            std::cout << "  " << ns->chips[i].value << ": " <<  value << std::endl;

        }
    }
}

std::vector<std::string> splitString(std::string str, char delim)
{
    std::vector<std::string> v;
    std::string s;
    std::stringstream ss(str);
    while (std::getline(ss, s, delim)) {
        v.push_back(s);
    }
    return v;
}

void nts::Nanotekspice::getCommandPrompt(std::string str, nts::Parsing *ns)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == "exit")
        setExit(1);
    if ((str.find('=') != std::string::npos) && (str.find('=', str.find('=') + 1) == std::string::npos)) {
        nts::type_v comp;
        std::vector<std::string> input = splitString(str, '=');
        for (std::vector<chip>::size_type i = 0; i != ns->chips.size(); i++) {
            if (input[0] == ns->chips[i].value && (ns->chips[i].type == "input" || ns->chips[i].type == "clock" || ns->chips[i].type == "true" || ns->chips[i].type == "false")) {
                if (input[1] == "0" || input[1] == "1" || input[1] == "u") {
                    comp.type = input[0];
                    comp.value = input[1];
                    _inputValue.push_back(comp);
                }
                return;
            }
        }
    }

    if (str == "display")
        displayNano(ns);
    if (str == "simulate") {
        addTick();
        for (std::vector<chip>::size_type i = 0; i != ns->chips.size(); i++) {
            if (ns->chips[i].type == "clock") {
                _CircuitComponents[ns->chips[i].value].get()->setState("");
            }
        }
        for (size_t i = 0; i != _inputValue.size(); i++) {
            _CircuitComponents[_inputValue[i].type].get()->setState(_inputValue[i].value);
        }
        _inputValue.clear();
    }
}

void nts::Nanotekspice::prompt(nts::Parsing *ns)
{
    while (getExit() != 1) {
        std::cout << "> ";
        std::getline(std::cin, _str);
        if (!std::cin)
            break;
        getCommandPrompt(_str, ns);
    }
}

int main(int ac, char const **av)
{
    if (ac < 2) {
		std::cout << "Usage:\n\t./nanotekspice filepath" << std::endl;
		return 84;
	}
    
    try {
        nts::Parsing ns(av[1]);
        nts::Nanotekspice nanoteks(&ns);
        nanoteks.prompt(&ns);
    } catch (nts::ErrorHandling &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    };
    return 0;
}
