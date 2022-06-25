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

class IOutput
{
public:
    virtual void show_output(Buffer& out) = 0;

}

class ImageInput : IInput
{
    void take_input(){...}
}
//////////
thread1:
listener(socket)
{
    // try except
    IOutput out;
    Buffer buf;
    while (true)
    {
        num_bytes = socket.recv_data(buf)

        out.show_output(buf);
    }
}
///////
thread2:
sender()
{
    // try except
    IInput input;
    while (true)
    {
        //get input (maybe threads for av)
        input.get_input()
        socket.send_data(input.get_data())
    }
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
            m_server_socket(_s_init_socket)
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

