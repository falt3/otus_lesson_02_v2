#include "ip.h"


int main()//int argc, char* argv[])
{
    std::vector<ClIp> ipMas;

    inputData(ipMas);

    if (ipMas.size() > 0)
        worker(ipMas);

    return 0;
}
