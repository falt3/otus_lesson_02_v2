// #define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE my_test_IP
// #include <boost/test/unit_test.hpp>
 #include <boost/test/included/unit_test.hpp>

#include "ip.h"
#include <fstream>
#include <boost/uuid/detail/md5.hpp>

BOOST_AUTO_TEST_SUITE(test_suite)


BOOST_AUTO_TEST_CASE(file_ip)
{
    std::vector<ClIp> ipMas;

    // 1. загружаем данные из файла: ip_filter.tsv
    std::fstream fs("../ip_filter/ip_filter.tsv", std::fstream::in);
    BOOST_TEST(fs.is_open());
    if (fs.is_open()) {
        inputData(ipMas, fs);
        fs.close();
    }
    
    BOOST_TEST(ipMas.size() == 1000);
    
    if (ipMas.size() == 1000) {
        // 2. Манипулируем данными
        std::stringstream out;
        worker(ipMas, out);

        // 3. считаем MD5
        boost::uuids::detail::md5::digest_type digest {};
        boost::uuids::detail::md5 hh;
        hh.process_bytes((void *)out.str().data(), out.str().size());
        hh.get_digest(digest);

        // 3. проверяем MD5
        BOOST_CHECK(digest[0] == 0x24e7a7b2 && digest[1] == 0x270daee8 && 
            digest[2] == 0x9c64d3ca && digest[3] == 0x5fb3da1a);
    }
}

BOOST_AUTO_TEST_SUITE_END()