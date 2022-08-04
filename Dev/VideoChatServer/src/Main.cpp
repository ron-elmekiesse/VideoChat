#include <iostream>
#include <boost/asio.hpp>

using namespace boost;
using boost::asio::ip::tcp;

int main()
{
    std::cout << "Using Boost "
              << BOOST_VERSION / 100000 << "."      // major version
              << BOOST_VERSION / 100 % 1000 << "."  // minor version
              << BOOST_VERSION % 100                // patch level
              << std::endl;
    asio::io_service io_service;
    //socket creation
    tcp::socket socket(io_service);
    //connection
    socket.connect(tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 8080));

    const std::string msg = "Hello from Client!\n";
    boost::system::error_code error;
    asio::write(socket, asio::buffer(msg), error);
    if (!error)
    {
        std::cout << "Client sent hello message!" << std::endl;
    }
    else
    {
        std::cout << "send failed: " << error.message() << std::endl;
    }
    // getting response from server
    asio::streambuf receive_buffer;
    asio::read(socket, receive_buffer, error);
    if (error && error != asio::error::eof)
    {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    else
    {
        auto data = asio::buffer_cast<const char *>(receive_buffer.data());
        std::cout << data << std::endl;
    }
    return 0;
}