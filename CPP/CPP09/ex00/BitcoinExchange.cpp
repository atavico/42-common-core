#include "BitcoinExchange.hpp"

static void csv(std::map<std::string, float> &csv, std::ifstream &file)
{
    std::string before, after, line;
    getline(file, line);

    while(getline(file, line))
    {
        size_t pos = line.find(",");
        before = line.substr(0, pos);
        after = line.substr(pos + 1, line.length());
        csv[before] = atof(after.c_str());
    }
}

bool   isDateValid(std::string &date) {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    if (date[0] < '0' || date[0] > '9' || date[1] < '0' || date[1] > '9' || date[2] < '0' || date[2] > '9' || date[3] < '0' || date[3] > '9')
        return false;
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        return false;
    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;
    return true;
}

std::string checkDigit(std::string &s) {
    for (std::string::const_iterator i = s.begin(); i != s.end(); ++i) {
        if (!isdigit(*i) && *i != '.')
            throw std::invalid_argument("Error: bad value");
    }
    return s;
}

template<typename Iterator>
Iterator my_prev(Iterator it, typename std::iterator_traits<Iterator>::difference_type n = 1)
{
    std::advance(it, +n);
    return it;
}

BitcoinExchange::BitcoinExchange()
{
    std::ifstream   f;
    std::exception  e;

    try
    {
        f.open("data.csv");
        if(!f)
            throw e;
    }
    catch(const std::exception& e)
    {
        std::cout << "error: " << e.what() << '\n';
    }
    csv(this->_data, f);
    f.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){
    *this = src;
}

void    BitcoinExchange::doExchange(char *file)
{
    std::string before, after, line;
    std::exception  e;
    std::ifstream   f;
    size_t          pos;

    try
    {
        f.open(file);
        if(!f)
            throw e;
    }
    catch(const std::exception& e)
    {
        std::cout << "error: " << e.what() << '\n';
    }
    getline(f, line);
    if(line.compare("date | value") != 0)
    {
        std::cout << "Error: bad heading" << std::endl;
        return;
    }
    while(getline(f, line))
    {
        pos = line.find("|");
        if (pos == std::string::npos) //npos static const di string class, posizione invalita o non trovata
            std::cout << "Error: separator \" | \" not found" << std::endl;
        else
        {
            before = line.substr(0, pos);
            after = line.substr(pos + 3, line.length());
            std::map<std::string, float>::iterator it = this->_data.find(before);
            if(!isDateValid(before))
                std::cout << "Error: bad date" << std::endl;
            if(it != this->_data.end())
            {
                try
                {
                    if(!isDateValid(before))
                        std::cout << "Error: bad date" << std::endl;
                    if (atof(before.c_str()) >= 0 && atof(after.c_str()) <= 1000)
                    {
                        checkDigit(after);
                        std::cout << before << " => " << after << " = " << atof(after.c_str()) * this->_data[before] << std::endl;
                    }
                    else
                        std::cout << "Error: bad value" << std::endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            else
            {
                std::map<std::string, float>::iterator it2 =_data.lower_bound(before);
                if (it2 == this->_data.end())
                    std::cout << "Data not found." << std::endl;
                else
                {
                    std::map<std::string, float>::iterator it3 = my_prev(it2);
                    std::cout << "Data not fount for " << before << ", using exchange rate from " << it2->first << std::endl;
                    try
                    {
                        if (atof(after.c_str()) >= 0 && atof(after.c_str()) <= 1000)
                        {   
                            checkDigit(after);
                            std::cout << it3->first << " => " << after << " = " << atof(after.c_str()) * it3->second << std::endl;
                        }
                        else
                        {
                            std::cout << "Error: not a significant number." << std::endl;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cout << e.what() << '\n';
                    }
                    
                }
            }
        }

    }
    
}