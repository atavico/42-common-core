#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _data;
    
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange &src);
        ~BitcoinExchange(void) {};

        void doExchange(char *file);
};
#endif