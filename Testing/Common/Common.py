import enum
import struct
from dataclasses import dataclass

PACK_PACKET_STRUCT_FORMAT = '<4sII64sHI{data_size}s'
NO_DATA_PACK_PACKET_STRUCT_FORMAT = '<4sII64sHI'

UNPACK_PACKET_STRUCT_FORMAT = '<4sII64sHI'

HEADERS_SIZE = 82


class PacketTypes(enum.IntEnum):
    Uninitialized = 0
    ClientHello = 1
    ServerHello = 2
    CreateNewMeeting = 3
    ConnectToExistingMeeting = 4
    ServerEnterMeeting = 5
    SendText = 6
    SendImage = 7
    SendAudio = 8


def pack_to_server_packet(MAGIC, meeting_id, user_unique_id, name, data_type, data, data_size):
    """
    Create a Bytes network stream from the server packet parameters.
    :return: Bytes.
    """
    if data_size:
        return struct.pack(PACK_PACKET_STRUCT_FORMAT.format(data_size=data_size), MAGIC, meeting_id,
                           user_unique_id, name, data_type,
                           data_size, data)
    return struct.pack(NO_DATA_PACK_PACKET_STRUCT_FORMAT, MAGIC, meeting_id,
                       user_unique_id, name, data_type, data_size)


@dataclass
class PacketHeaders:
    magic: str
    meeting_id: int
    uuid: int
    name: str
    packet_type: PacketTypes
    data_size: int


def unpack_to_server_packet(raw_packet):
    """

    """
    packet_header = struct.unpack(UNPACK_PACKET_STRUCT_FORMAT.format(), raw_packet[:HEADERS_SIZE])
    packet_data = raw_packet[HEADERS_SIZE:]
    return PacketHeaders(*packet_header), packet_data
