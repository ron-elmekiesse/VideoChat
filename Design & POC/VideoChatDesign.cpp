Client:

using Buffer = std::vector<uint8_t>;

class AutoInitWinSock;

class AutoCloseSocket;

class Socket
{
    Socket(AutoCloseSocket& socket)

    size_t recv_data(Buffer& buffer)
    {
        buffer.resize(MAXIMUM_PACKET_SIZE);
        num_bytes = recv(socket.get(), buffer.data(), buffer.size(), ...);
        if (-1 == num_bytes)
        {
            throw VideoChatException(VideoChatStatus::SOCKET_RECV_FAILED, errno)
        }
        buffer.resize(num_bytes);
    }

    size_t send_data(Buffer& buffer)
    {
        send(socket.get(), ...)
    }
private:
    AutoCloseSocket& socket;
}

class IInput
{
public:
    virtual void take_input() = 0;

    Buffer& get_data()
    {
        return m_data;
    }

    PacketDataTypes get_type()
    {
        return m_input_type;
    }
protected:
    const PacketDataTypes m_input_type;
    Buffer m_data;
}

class TextInput : IInput
{
    TextInput() :
        m_input_type(PacketDataTypes::Text)
    {}

    void take_input()
    {
        std::get_line(std::cin, m_data);
    }
}

class ImageInput : IInput
{
    ImageInput() :
        m_input_type(PacketDataTypes::Image)

    void take_input(){...}
}

class IOutput
{
public:
    virtual void show_output(Buffer& out) = 0;

}

/* TODO: Add overload to "Socket >> " which gets this struct. */
struct PacketHeaders // 80 bytes
{
    RT_Magic;       // 2 bytes
    meeting_id;     // 4 bytes
    user_unique_id; // 4 bytes
    name[64];       // 64 bytes
    data_type;      // 2 byte
    data_size;      // 4 bytes
};

class PacketCreator
{
    PacketCreator(uint32_t meeting_id, const std::string& name, uint32_t user_unique_id);

    void create(PacketDataTypes data_type, const Buffer& data)
    {
        PacketHeaders headers;

        headers.RT_Magic = MAGIC;
        headers.meeting_id = m_meeting_id;
        headers.user_unique_id = m_user_unique_id;
        std::strncpy(headers.name, m_name.c_str(), 63); // to obtain null terminator.
        headers.data_type = data_type;
        headers.data_size = data.size();

        m_raw_packet.resize(FIXED_HEADERS_SIZE + data.size())

        auto const ptr = reinterpret_cast<unsigned char*>(&headers);

        std::copy(ptr, ptr + sizeof(headers), std::back_inserter(m_raw_packet));

        std::copy(data.begin(), data.end(), std::back_inserter(m_raw_packet));
    }

    const Buffer& get_raw_packet()
    {
        return m_raw_packet;
    }

    m_meeting_id;
    m_name;
    m_user_unique_id;
    Buffer m_raw_packet;
}

enum class PacketDataTypes : uint16_t
{
    ...
}

//////////

client main:
main()
{
    /* Fix this. */


    get_meeting_id()

    AutoCloseSocket auto_close_socket(SERVER_IP, SERVER_PORT)
    // Make this section look better.
    Socket socket(auto_close_socket)

    socket.send_data(meeting_id)

    listener_thread = std::thread(listener, {socket, meeting_id})
    sender_thread = std::thread(sender, {socket, meeting_id})

    listener_thread.start()
    sender_thread.start()

    // wait until the threads are dead / infinitly.
}

/////
client thread1:
listener(const Socket& socket, uint32_t meeting_id, IOutput output_device)
{
    // TODO: Later on pickup the output device by the data_type from the packet headers.
    try 
    {
        PacketHeaders packet_headers{};

        while (true)
        {
            socket >> packet_headers;

            validate_packet(packet_headers, meeting_id)

            Buffer data(packet_headers.data_size);

            socket >> data;

            output_device.show_output(data);
        }
    }
    catch (...)
    {}
}

///////

client thread2:
sender(const Socket& socket, uint32_t meeting_id, const std::string& name, uint32_t user_unique_id, IInput input_device)
{
    // Thread for each input activity / device.
    try
    {
        PacketCreator packet_creator(meeting_id, name, user_unique_id);
        IInput input;

        while (true)
        {
            input.get_input()

            packet_creator.create(input.get_type(), input.get_data())

            socket << packet_creator.get_raw_packet()
        }
    }
    catch (...)
    {}
}

/////////////////////////

Server:

// TODO: check "register_async_operation" validity.
void register_async_operation(const Buffer& buffer, std::function<...> async_operation, void* handler)
{
    async_operation(boost::asio::buffer(buffer.data(), buffer.size()),
                    boost::bind(handler,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

class MeetingHub : public boost::enable_shared_from_this<NewClientConnectionHandler>
{

};

class NewClientConnectionHandler : public boost::enable_shared_from_this<NewClientConnectionHandler>
{
public:
    typedef boost::shared_ptr<NewClientConnectionHandler> pointer;

    NewClientConnectionHandler(boost::asio::io_service& io_service):
        m_sock(io_service),
        m_packet_headers(0)
    {}

    // creating the pointer
    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new NewClientConnectionHandler(io_service));
    }

    //socket creation
    tcp::socket& socket()
    {
        return sock;
    }

    void basic_handle_read_check(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (err)
        {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }


    void basic_handle_write_check(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err) {
            cout << "Server sent Hello message!"<< endl;
        } else {
            std::cerr << "error: " << err.message() << endl;
            sock.close();
        }
    }

    void start()
    {
        // TODO: change to asio::async_read everywhere (we know how many to read).
        sock.async_read_some(
                boost::asio::buffer(m_packet_headers, sizeof(m_packet_headers)),
                boost::bind(&NewClientConnectionHandler::handle_client_hello,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_client_hello(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_read_check(err, bytes_transferred);

        uuid = generate_uuid();

        PacketCreator.create(uuid=uuid);

        data = PacketCreator.get_raw_packet()

        sock.async_write_some(
                boost::asio::buffer(data, data.size()),
                boost::bind(&NewClientConnectionHandler::handle_write_server_hello,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_write_server_hello(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_write_check(err, bytes_transferred);

        sock.async_read_some(
                boost::asio::buffer(m_packet_headers, sizeof(m_packet_headers)),
                boost::bind(&NewClientConnectionHandler::handle_enter_meeting,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_enter_meeting(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_read_check(err, bytes_transferred);

        // TODO: When ExistingMeeting PacketType is given and no meeting exists:
        //       Return a corresponding PacketType and register again.
        //       Change in client - ClientStartup::client_startup_menu,
        //       if fails so return from there
        meeting_id = get_new_or_existing_meeting_id(m_packet_headers);

        PacketCreator.create(...);

        data = PacketCreator.get_raw_packet()

        sock.async_write_some(
                boost::asio::buffer(data, data.size()),
                boost::bind(&NewClientConnectionHandler::handle_write_server_enter_meeting,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_write_server_enter_meeting(const boost::system::error_code& err, size_t bytes_transferred)
    {
        basic_handle_write_check(err, bytes_transferred);

        if client meetind_id not in map:
            std::thread(async_loop_service<MeetingHub>)

        map_mutex.lock()
        map.insert(Client...)
        map_mutex.unlock()
    }


private:
    tcp::socket m_sock;
    PacketHeaders m_packet_headers;
};


class ServerSetupNewClients
{
public:
    //constructor for accepting connection from client
    ServerSetupNewClients(io_service& io_service):
        acceptor(io_service, tcp::endpoint(tcp::v4(), 1337))
    {
        _start_accept();
    }

    void handle_accept(NewClientConnectionHandler::pointer connection, const boost::system::error_code& err)
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
        NewClientConnectionHandler::pointer connection = NewClientConnectionHandler::create(
                (asio::io_context&)(m_acceptor).get_executor().context());

        // asynchronous accept operation and wait for a new connection.
        acceptor_.async_accept(connection->socket(),
                               boost::bind(&Server::handle_accept, this, connection,
                                           boost::asio::placeholders::error));
    }

private:
    tcp::acceptor m_acceptor;
};

template <typename ConnectionClass>
void async_loop_service(int meeting_id = 0)
{
    try
    {
        asio::io_service io_service;

        if (meeting_id == 0)
        {
            ConnectionClass connection_class(io_service);
        }
        else
        {
            ConnectionClass connection_class(io_service, meeting_id);
        }

        io_service.run();
    }
    catch (const VideoChatServerException &exc)
    {

    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {

    }
}


/*
 * Notes:
 * Each meeting will have its own thread.
 * When a new client is connected, the server adds the newly created socket to the
 * map at the specific meeting ID.
 *
 * Change to UDP.
 *
 * Thoughts:
 * Validate that no Mutex is needed for the map.
 *
 */
