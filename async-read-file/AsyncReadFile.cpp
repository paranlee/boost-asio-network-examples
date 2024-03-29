/*
 *  Copyright (C) Boost.Asio를 이용한 네트워크 프로그래밍 - 한빛출판네트워크
 *
 *  Asynchronous TCP Client:  google cpplint and maintained by Paran Lee <p4ranlee@gmail.com>
 *
 */
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

void read_end(const boost::system::error_code& error,
          const std::vector<char>& result) {
    if (error) {
        std::cout << error.message() << std::endl;
    } else {
        const std::string s(result.begin(), result.end());
        std::cout << "success : " << s << std::endl;
    }
}

int main() {
    boost::asio::io_service io_service;

    HANDLE handle = ::CreateFileA("AsyncReadFile.txt",
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_FLAG_OVERLAPPED,
                NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cout << "cannot open" << std::endl;
        return 0;
    }

    std::vector<char> buffer(::GetFileSize(handle, NULL));

    boost::asio::windows::stream_handle file(io_service, handle);

    boost::asio::async_read(file,
                        boost::asio::buffer(buffer.data(), buffer.size()),
                        boost::bind(read_end, _1, boost::ref(buffer)));

    io_service.run();

    getchar();
    ::CloseHandle(handle);
    return 0;
}
