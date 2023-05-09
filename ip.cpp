#include "ip.h"
#include <algorithm>


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


int parsingString(const std::string &line, ClIp::TarIp &a) 
{
    std::vector<std::string> v = split(line, '\t');
    if (v.size() != 3) return 1;

    std::vector<std::string> v2 = split(v.at(0), '.');
    if (v2.size() != 4) return 2;

    int i = 0;
    for (auto el = v2.cbegin(); el != v2.end(); ++el, ++i) {
        try {
            a[i] = std::stoi(*el);
        }
        catch (const std::exception &e) {
            return 3;
        }        
    }

    return 0;
}


// ввод пустой строки -> выход
void inputData(std::vector<ClIp> &mas, std::istream &in)
{
    std::string line;    
    while (std::getline(in, line) && !line.empty()) {
        ClIp::TarIp ar;
        if (parsingString(line, ar) == 0) 
            mas.push_back(ar);
        else
            std::cout << "Ошибка ввода строки" << std::endl;
    }
}



void worker(std::vector<ClIp> &ipMas, std::ostream &out)
{
    // 1. обратная сортировка
    std::sort(ipMas.begin(), ipMas.end(), [](ClIp &a, ClIp &b) {return !(a < b);});
    for(auto el: ipMas)
        out << el << std::endl;

    // 2. список адресов, первый байт которых равен 1
    std::for_each(ipMas.begin(), ipMas.end(), [&out](const ClIp &a)
    {
        if (a[0] == 1) 
            out << a << std::endl;
    }
    );

    // 3. список адресов, первый байт которых равен 46, а второй 70
    std::for_each(ipMas.begin(), ipMas.end(), [&out](const ClIp &a)
    {
        if ((a[0] == 46) && (a[1] == 70))
            out << a << std::endl;
    }
    );

    // 4. список адресов, любой байт которых равен 46
    std::for_each(ipMas.begin(), ipMas.end(), [&out](const ClIp &a)
    {
        for (int i = 0; i < 4; ++i)
            if (a[i] == 46) {
                out << a << std::endl;
                break;
            }
    }
    );  
}