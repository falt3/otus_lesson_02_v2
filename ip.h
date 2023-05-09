#pragma once

#include <iostream>
#include <vector>


// храним байты в обратном порядке, для удобства сравнения в операторах <>=
class ClIp
{
public:
    using TarIp = uint8_t[4];

    ClIp(TarIp a) { for(int i = 0; i < 4; ++i) mData.b[i] = a[3-i]; } 

    bool operator< (const ClIp &other) const {return this->mData.u < other.mData.u;};
    bool operator> (const ClIp &other) const {return this->mData.u > other.mData.u;};
    uint8_t operator[] (int i) const {return this->mData.b[3 - (i & 3)];}
    friend std::ostream & operator<< (std::ostream &out, const ClIp &ip)
    {   
        out << (int)ip.mData.b[3] << "." << (int)ip.mData.b[2] << "." << (int)ip.mData.b[1] << "." << (int)ip.mData.b[0]; 
        return out;
    };

private:
    union TunionIp {
        TarIp    b;
        uint32_t u;
    };
    TunionIp mData;
};


void inputData(std::vector<ClIp> &mas, std::istream &in = std::cin);
void worker(std::vector<ClIp> &ipMas, std::ostream &out = std::cout);
