import socket
from threading import Thread

from Common.Common import PacketTypes, pack_to_server_packet, unpack_to_server_packet

MAGIC = b'RTVC'
user_unique_id = 1337

def sanity_test_client_hello(sock: socket.socket):
    # get client hello
    packet = sock.recv(1024)
    headers, data = unpack_to_server_packet(packet)
    print(headers, data)

    msg = pack_to_server_packet(MAGIC, 4294967295, user_unique_id, headers.name, PacketTypes.ServerHello, b'', 0)

    sock.send(msg)


def sanity_test_client_connect_to_meeting(sock: socket.socket):
    packet = sock.recv(1024)

    headers, data = unpack_to_server_packet(packet)
    print(headers, data)
    meeting_id = headers.meeting_id if headers.packet_type == PacketTypes.ConnectToExistingMeeting else 1234
    msg = pack_to_server_packet(MAGIC,
                                meeting_id,
                                headers.uuid, headers.name, PacketTypes.ServerEnterMeeting, b'', 0)

    sock.send(msg)
    return meeting_id


def sanity_test_client_listen(meeting_id: int, sock: socket.socket):
    data = b'Hello World!'
    msg = pack_to_server_packet(MAGIC, meeting_id, user_unique_id, b'Ron', PacketTypes.SendText, data, len(data))
    sock.send(msg)

    data2 = b'Yaaaaaaas!'
    msg = pack_to_server_packet(MAGIC, meeting_id, user_unique_id, b'Ron', PacketTypes.SendText, data2, len(data))
    sock.send(msg)


def sanity_test_client_send(sock: socket.socket):
    while True:
        packet = sock.recv(1024)

        if len(packet) == 0:  # When connection is lost.
            return

        packet_fields = unpack_to_server_packet(packet)

        print(packet_fields)


def create_sock(ip: str, port: int):
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    server_sock.bind((ip, port))
    server_sock.listen(5)
    print('Server is listening...')

    connected_sock, addr_info = server_sock.accept()

    return connected_sock


if __name__ == '__main__':
    sock = create_sock('127.0.0.1', 8080)
    sanity_test_client_hello(sock)
    meeting_id = sanity_test_client_connect_to_meeting(sock)

    t1 = Thread(target=sanity_test_client_listen, args=(meeting_id, sock,))
    t2 = Thread(target=sanity_test_client_send, args=(sock,))

    # start the threads
    t1.start()
    t2.start()

    # wait for the threads to complete
    t1.join()
    t2.join()
