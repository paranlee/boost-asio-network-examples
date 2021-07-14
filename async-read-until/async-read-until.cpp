/*
 *  Copyright (C) Boost.Asio를 이용한 네트워크 프로그래밍 - 한빛출판네트워크
 *
 *  Asynchronous Read Utility:  google cpplint and maintained by Paran Lee <p4ranlee@gmail.com>
 *
 */
#include <iostream>
#include <string>
#include <boost/ref.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

struct receiver {
    typedef void result_type;

    void operator() (const boost::system::error_code& error,
                const boost::asio::streambuf& buffer) {
        if (error) {
            std::cout << error.message() << std::endl;
        } else {
            const std::string str =
                boost::asio::buffer_cast<const char*>(buffer.data());
            std::cout << str << std::endl;
        }
    }
};

int main() {
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::socket soc(io_service);
    soc.connect(boost::asio::ip::tcp::endpoint(
              boost::asio::ip::address::from_string("127.0.0.1"),
              31400));

    boost::asio::streambuf buffer;
    boost::asio::async_read_until(soc, buffer, '\n',
                              boost::bind(receiver(),
                                boost::asio::placeholders::error,
                                boost::ref(buffer)));

    io_service.run();

    return 0;
}
