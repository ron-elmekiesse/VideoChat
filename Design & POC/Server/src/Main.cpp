#include <iostream>
#include <vector>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>

using namespace boost;
using boost::asio::ip::tcp;

class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler>
{
public:
    typedef boost::shared_ptr<ConnectionHandler> pointer;

    ConnectionHandler(boost::asio::io_service& io_service):
            m_sock(io_service)
    {}

    // creating the pointer
    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new ConnectionHandler(io_service));
    }

    //socket creation
    tcp::socket& socket()
    {
        return m_sock;
    }

    void basic_handle_read_check(const boost::system::error_code& err, size_t bytes_transferred)
    {
        std::cout << "Here" << std::endl;
        std::cout << m_packet_data << std::endl;
        if (err)
        {
            std::cerr << "error: " << err.message() << std::endl;
            m_sock.close();
        }
    }


    void basic_handle_write_check(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err) {
            std::cout << "Server sent Hello message!"<< std::endl;
        } else {
            std::cerr << "error: " << err.message() << std::endl;
            m_sock.close();
        }
    }

    void start()
    {
        m_sock.async_read_some(boost::asio::buffer(m_packet_data, m_max_packet_length),
                                boost::bind(&ConnectionHandler::handle_client_hello,
                                            shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_client_hello(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_read_check(err, bytes_transferred);

        std::string data = "Hello World!";
        m_sock.async_write_some(
                boost::asio::buffer(data, data.size()),
                boost::bind(&ConnectionHandler::handle_write_server_hello,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        std::cout << "Sent" << std::endl;
    }

    void handle_write_server_hello(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_write_check(err, bytes_transferred);
    }


private:
    tcp::socket m_sock;
    static constexpr uint32_t m_max_packet_length = 100;
    char m_packet_data[m_max_packet_length];
};


class ServerSetupNewClients{
public:
    ServerSetupNewClients(asio::io_service& io_service) :
            m_acceptor(io_service, tcp::endpoint(tcp::v4(), 1337))
    {
        _start_accept();
    }

    void handle_accept(ConnectionHandler::pointer& connection, const boost::system::error_code& err)
    {
        if (!err) {
            connection->start();
        }
        _start_accept();
    }
private:
    void _start_accept()
    {
        // socket
        ConnectionHandler::pointer connection = ConnectionHandler::create((asio::io_context&)(m_acceptor).get_executor
                ().context());
        std::cout << "accepting" << std::endl;
        // asynchronous accept operation and wait for a new connection.
        m_acceptor.async_accept(connection->socket(),
                               boost::bind(&ServerSetupNewClients::handle_accept, this, connection,
                                           boost::asio::placeholders::error));
    }

private:
    tcp::acceptor m_acceptor;
};


int main(int argc, char const *argv[]) {
    try
    {
        asio::io_service io_service;
        ServerSetupNewClients server(io_service);
        io_service.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
