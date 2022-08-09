import enum
import struct

PACK_PACKET_STRUCT_FORMAT = '<4sII64sHI{data_size}s'

UNPACK_PACKET_STRUCT_FORMAT = '<4sII64sHI'

HEADERS_SIZE = 82


class DataTypes(enum.IntEnum):
    TEXT = 1


def pack_to_server_packet(MAGIC, meeting_id, user_unique_id, name, data_type, data, data_size):
    """
    Create a Bytes network stream from the server packet parameters.
    :return: Bytes.
    """
    return struct.pack(PACK_PACKET_STRUCT_FORMAT.format(data_size=data_size), MAGIC, meeting_id,
                       user_unique_id, name, data_type,
                       data_size, data)


def unpack_to_server_packet(raw_packet):
    """

    """
    packet_header = struct.unpack(UNPACK_PACKET_STRUCT_FORMAT.format(), raw_packet[:HEADERS_SIZE])
    packet_data = raw_packet[HEADERS_SIZE:]
    return packet_header + (packet_data,)
