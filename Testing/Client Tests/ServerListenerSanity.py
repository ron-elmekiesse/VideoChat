import struct
import socket

MAGIC = b'RTVC'
meeting_id = 1
user_unique_id = 1337
name = b'king ron'
data_type = 1  # Text
data = b"Hello Client"
data_size = len(data)


def test_sanity_server_listener(ip: str, port: int):
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)

    server_sock.bind((ip, port))

    server_sock.listen(0)

    print('Server is listening...')

    connected_sock, addr_info = server_sock.accept()

    msg = struct.pack(f"<{len(MAGIC)}sII64sHI{data_size}s", MAGIC, meeting_id, user_unique_id, name, data_type,
                      data_size, data)

    connected_sock.send(msg)


if __name__ == '__main__':
    test_sanity_server_listener("127.0.0.1", 8080)
