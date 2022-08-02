import enum
import struct

PACKET_STRUCT_FORMAT = '<{magic_len}sII64sHI{data_size}s'


class DataTypes(enum.IntEnum):
    TEXT = 1


def pack_to_server_packet(MAGIC, meeting_id, user_unique_id, name, data_type, data, data_size):
    """
    Create a Bytes network stream from the server packet parameters.
    :return: Bytes.
    """
    return struct.pack(PACKET_STRUCT_FORMAT.format(magic_len=len(MAGIC), data_size=data_size), MAGIC, meeting_id,
                       user_unique_id, name, data_type,
                       data_size, data)
