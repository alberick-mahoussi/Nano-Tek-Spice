/*
** EPITECH PROJECT, 2023
** tekspice
** File description:
** controle of circuit by programm in c++
*/

#include "ErrorHandling.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>

int compter(std::string v, unsigned int n)
{
    int i = 0;
    for (; n < v.size(); n++)
        if (v[n] == ' ') i+=1;
    return i;
}

std::string check_contain(std::string str)
{
    std::string copy_value = "";
    for (unsigned int i = 0; i < str.size(); i++) {
        if ((str[i] >= 'A' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
            copy_value += str[i];
        else if (str[i] == ' ' && i != 0 && compter(str, (i + 1)) == 0)
            copy_value += str[i];
    }
    return copy_value;
}

std::string check_line_links(std::string link)
{
    std::string copy = "";
    for (unsigned int i = 0; i < link.size(); i++) {
        if ((link[i] >= 'A' && link[i] <= 'z') || (link[i] >= '0' && link[i] <= '9') || link[i] == '_')
            copy += link[i];
        else if (link[i] == ' ' && i != 0 && compter(link, (i + 1)) == 0)
            copy += link[i];
        else if (link[i] == ':' && (link[i + 1] >= '0' && link[i + 1] <= '9'))
            copy += link[i];
    }
    return copy;
}

std::vector<std::string> clean_line_chipset(std::vector<std::string> chipsets_line)//function whoes verify the reggex of line and return all line of chipset without chipsets
{
    std::vector<std::string> good_forms;
    for (unsigned int i = 1; i < chipsets_line.size(); i++)
            good_forms.push_back(check_contain(chipsets_line[i]));
    return good_forms;
}

std::vector<std::string> clean_line_links(std::vector<std::string> links)
{
    std::vector<std::string> good_forms;
    for (unsigned int i = 1; i < links.size(); i++)
            good_forms.push_back(check_line_links(links[i]));
    return good_forms;
}

std::vector<std::string> split(std::string str, char delim)
{
    std::vector<std::string> v;
    std::string s;
    std::stringstream ss(str);
    while (std::getline(ss, s, delim)) {
        v.push_back(s);
    }
    return v;
}

bool nts::Parsing::check_empty_line(std::string line)
{
    for (unsigned int y = 0; y < line.length(); y++)
        if (line[y] != ' ')
            return true;
    return false;
}

void nts::Parsing::get_all_line()
{
    unsigned int v = 0;
    int chipsetFound = 0;
    std::vector<std::string> checker;
    std::string File = file_nts, info;
    std::ifstream file (file_nts, std::ifstream::in);
    if (File.find(".nts") == std::string::npos || !file)
        throw ErrorHandling("Error: Bad file name");
    
    while (getline(file, info))
        if (info.c_str()[0] != '#' && check_empty_line(info) == true)
            checker.push_back(info);
    
    for (unsigned int i = 0; i < checker.size(); i++) {
        if (checker[i].find(".chipsets:") != std::string::npos) {
            chipsetFound++;
        }
    }
    if (chipsetFound != 1)
        throw ErrorHandling("Error: Bad Configuation file");

    for (v = 0; v < checker.size(); v++) {
        nts_line.push_back(checker[v]);
    }
    if (nts_line[0].find(".chipsets:") == std::string::npos)
        throw ErrorHandling("Error: Bad Configuation file No start with chipsets");
}

void nts::Parsing::get_info_chipset()
{
    get_all_line();
    chip info;
    std::vector<std::string> line = this->nts_line;
    std::vector<std::string> info_chipset;
    for (unsigned int i = 0; i < line.size(); i++) {
        if (line[i].find(".links:") != std::string::npos)
            break;
        else
            info_chipset.push_back(line[i]);
    }

    for (unsigned int y = 1; y < info_chipset.size(); y++) {
        if ((split(info_chipset[y], ' ').size() != 2) || std::regex_match(info_chipset[y], std::regex("([[:blank:]]+)?[[:alnum:]]+[[:blank:]]+[[:alnum:]_]+([[:blank:]]+)?")) == false)
            throw ErrorHandling("Error: Bad Configuation file");
    }

    std::vector<std::string> all_chips = clean_line_chipset(info_chipset);
    for (unsigned int i = 0; i < all_chips.size(); i++) {
        std::istringstream strem(all_chips[i].c_str());
        strem >> info.type;
        strem >> info.value;
        this->chips.push_back(info);
    }
    std::sort(chips.begin(), chips.end(), [] (chip &x, chip &y) { return x.value < y.value; });
}

bool nts::Parsing::verify_components(std::string type)
{
    int i = 0;
    std::string component[25] = 
    {
        "logger", "output", "clock", "false",
        "true", "4001", "4069", "4030",
        "4071", "4081", "4011", "4008",
        "4013", "4017", "4094", "4040",
        "4512", "4514", "4801", "2716",
        "input", "and", "xor", "or", "not"
    };
    while (i < 25) {
        if ( component[i] == type)
            return true;
        i+=1;
    }
    return false;
}

bool nts::Parsing::exits(std::string value)
{
    for (unsigned int u = 0; u < this->chips.size(); u++)
        if (value == this->chips[u].value)
            return true;
    return false;
}

void nts::Parsing::get_info_link()
{
    unsigned int y = 0;
    link all_link;
    get_info_chipset();
    std::vector<std::string> take_one, take, take_two, info_links;
    std::vector<std::string> links, all_line = this->nts_line;

    for (y = 0; y < all_line.size(); y++)
        if (all_line[y].find(".links:") != std::string::npos) break;
    
    for (; y < all_line.size(); y++) info_links.push_back(all_line[y]);
    
    for (unsigned int y = 1; y < info_links.size(); y++) {
        if (std::regex_match(info_links[y], std::regex("([[:blank:]]+)?[[:alnum:]_]+:[[:digit:]]+[[:blank:]]+[[:alnum:]_]+:[[:digit:]]+([[:blank:]]+)?")) == false)
            throw ErrorHandling("Error: Bad Configuation file");
    }
    
    links = clean_line_links(info_links);
    for (unsigned int y = 0; y < links.size(); y++) {
        take = split(links[y], ' ');
        take_one = split(take[0], ':');
        take_two = split(take[1], ':');
        all_link.chip_one = take_one[0];
        all_link.chip_one_val = take_one[1];
        all_link.chip_two = take_two[0];
        all_link.chip_two_val = take_two[1];
        this->links.push_back(all_link);
    }
}

bool check_type_line(std::string line)
{
    if (std::regex_match(line.c_str(), std::regex("([[:blank:]]+)?[[:alnum:]_]+:[[:digit:]]+[[:blank:]]+[[:alnum:]_]+:[[:digit:]]+([[:blank:]]+)?")) ||
        std::regex_match(line, std::regex("([[:blank:]]+)?[[:alnum:]]+[[:blank:]]+[[:alnum:]_]+([[:blank:]]+)?")) ||
        std::regex_match(line, std::regex("([[:blank:]]+)?.chipsets:([[:blank:]]+)?")) || std::regex_match(line, std::regex("([[:blank:]]+)?.links:([[:blank:]]+)?")))
        return true;
    return false;
}

bool nts::Parsing::new_component(std::string component)
{
    int n = 0;
    for (unsigned int i = 0; i < this->chips.size(); i++)
        if (component == chips[i].value)
            n++;
    if (n > 1) 
        return false;
    return true;
}

void nts::Parsing::error_checker()
{
    get_info_link();
    if (this->chips.size() == 0)
        throw ErrorHandling("Error: No chipset");
    for (unsigned int y = 0; y < this->nts_line.size(); y++)
        if (check_type_line(nts_line[y]) == false)
            throw ErrorHandling("Error: wrong configuration file");
    

    for (unsigned int y = 0; y < this->chips.size(); y++) {
        if (verify_components(chips[y].type) == false)
            throw ErrorHandling("Error: components type don't exist");
        
        if (new_component(chips[y].value) == false)
            throw ErrorHandling("Error: component already exist");
    }

    for (unsigned int u = 0; u < links.size(); u++)
        if (exits(links[u].chip_one) == false || exits(links[u].chip_two) == false)
            throw ErrorHandling("Error: components don't exist");

    for (unsigned int y = 0; y < links.size(); y++)
        if (std::regex_match(this->links[y].chip_one + ':' + this->links[y].chip_one_val, std::regex("[[:alnum:]_]+:[[:digit:]]+")) == false
        || std::regex_match(this->links[y].chip_two + ':' + this->links[y].chip_two_val, std::regex("[[:alnum:]_]+:[[:digit:]]+")) == false)
            throw ErrorHandling("Error: wrong links format");
}
