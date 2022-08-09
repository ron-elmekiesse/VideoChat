import socket

from Common.Common import unpack_to_server_packet


def test_sanity_server_listener(ip: str, port: int):
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)

    server_sock.bind((ip, port))

    server_sock.listen(0)

    print('Server is listening...')

    connected_sock, addr_info = server_sock.accept()

    while True:
        packet = connected_sock.recv(1024)

        if len(packet) == 0:  # When connection is lost.
            return

        packet_fields = unpack_to_server_packet(packet)

        print(packet_fields)


if __name__ == '__main__':
    test_sanity_server_listener('127.0.0.1', 8080)
