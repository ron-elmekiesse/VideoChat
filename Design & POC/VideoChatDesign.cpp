Client:

using Buffer = std::vector<uint8_t>;

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

protected:
    Buffer m_data;
}

class TextInput : IInput
{
    void take_input()
    {
        std::get_line(std::cin, m_data);
    }
}

class ImageInput : IInput
{
    void take_input(){...}
}

class IOutput
{
public:
    virtual void show_output(Buffer& out) = 0;

}

struct PacketFormat
{
    uint32_t meeting_id;
    std::unique_ptr<uint8_t> content;
}

class PacketCreator
{
    PacketCreator(uint32_t meeting_id);

    void create(Buffer& packet_content)
    {
        m_created_packet.meeting_id = meeting_id;
        m_created_packet.content = packet_content.data();
    }

    PacketFormat& get()
    {
        return m_created_packet;
    }

    m_meeting_id;
    PacketFormat m_created_packet;
}

struct ThreadData
{
    const Socket& socket;
    uint32_t meeting_id;
}

//////////

client main:
main()
{
    get_meeting_id()

    AutoCloseSocket auto_close_socket(SERVER_IP, SERVER_PORT)

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
listener(ThreadData thread_data)
{
    // try except
    try 
    {
        const Socket& socket = thread_data.socket;
        IOutput out;
        Buffer buf;
        
        while (true)
        {
            num_bytes = socket.recv_data(buf)

            out.show_output(buf);
        }
    }
    catch (...)
    {}
}

///////

client thread2:
sender(ThreadData thread_data)
{
    // try except
    try
    {
        PacketCreator packet_creator(thread_data.meeting_id);
        const Socket& socket = thread_data.socket;
        IInput input;

        while (true)
        {
            //get input (maybe threads for av)
            input.get_input()

            input.get_data()

            socket.send_data(input.get_data())
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

