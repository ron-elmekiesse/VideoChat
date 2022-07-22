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


namespace meeting
{

}

extern std::map<uint32_t, std::vector<AutoCloseSocket>> meetings;

class Server
{
public:
    Server(port) :
            m_server_socket(_s_init_socket())
    {}

    ~Server(){}

    void start_server()
    {

    }
    
private:
    static Socket _s_init_socket(){
        Socket s = bind;
        listen
        return s;
    }
    AutoCloseSocket m_server_socket;
}

/*
 * Notes:
 * Each meeting will have its own thread.
 * When a new client is connected, the server adds the newly created socket to the
 * map at the specific meeting ID.
 *
 * Thoughts:
 * Validate that no Mutex is needed for the map.
 *
 */

