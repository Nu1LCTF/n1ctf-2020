#define _CRT_SECURE_NO_WARNINGS
#define STRSAFE_NO_CCH_FUNCTIONS

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <strsafe.h>
#include <cstdio>
#include "Common.h"
#include "ALPC.h"

#pragma comment(lib, "alpc.lib")

#define PORT_FORMAT L"\\RPC Control\\%S"
#define PORT_MSG_SIZE 0x1000
#define TOKEN_FILE L"C:\\token.txt"
#define FLAG_FILE L"C:\\flag.txt"

extern "C" DWORD GetFileHandleSize(HANDLE hFile) {
  DWORD dwRet;
  if (SetFilePointer(hFile, 0, 0, SEEK_END) == INVALID_SET_FILE_POINTER) {
    return -1;
  }
  dwRet = SetFilePointer(hFile, 0, nullptr, SEEK_CUR);
  if (SetFilePointer(hFile, 0, 0, SEEK_SET) == INVALID_SET_FILE_POINTER) {
    return -1;
  }
  return dwRet;
}

extern "C" BOOL Authenticate(USHORT hFile, void* data, DWORD size) {
  CHAR buffer[256];
  DWORD file_size = GetFileHandleSize(reinterpret_cast<HANDLE>(hFile));
  if (file_size == -1) {
    return FALSE;
  }
  DWORD read_size = file_size > 256 ? 256 : file_size, ret;
  if (read_size != size) {
    return FALSE;
  }
  if (!ReadFile(reinterpret_cast<HANDLE>(hFile), buffer, read_size, &ret, nullptr)) {
    return FALSE;
  }
  if (!memcmp(buffer, data, read_size)) {
    return TRUE;
  }
  return FALSE;
}

namespace auth {
  int main(std::vector<std::string>& args) {
    WCHAR portname[256] = { 0 };
    if (args.size() < 2) {
      std::cout << "Please provide pipe uuid\n";
      return 1;
    }

    if (!SUCCEEDED(::StringCbPrintfW(portname, sizeof(portname), PORT_FORMAT, args[1].c_str()))) {
      return 101;
    }

    auto server = ALPCServer::create(portname, 2 * PORT_MSG_SIZE);
    if (!server) {
      return 103;
    }
    auto msg = std::make_unique<ALPCMessage>(PORT_MSG_SIZE);
    msg->with_attribute(new ALPCMessageAttribute(ALPC_MESSAGE_ALL_ATTRIBUTE));

    bool bye = false;
    while (true) {
      if (!server->recv(*msg)) {
        return 3;
      }
      if (msg->type() == LPC_CONNECTION_REQUEST) {
        if (!server->accept(*msg)) {
          return 4;
        }
      } else if (msg->type() == LPC_REQUEST) {
        uint32_t size = reinterpret_cast<uint32_t*>(msg->data())[0];
        uint32_t opcode = reinterpret_cast<uint32_t*>(msg->data())[1];
        uint8_t* buf = reinterpret_cast<uint8_t*>(msg->data()) + 8;
        uint32_t result = 0;
        if (size <= PORT_MSG_SIZE) {
          if (opcode == 0x1337) {   // GetFlag
            HANDLE hTokenFile = CreateFile(TOKEN_FILE, FILE_READ_ACCESS, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
            if (hTokenFile == INVALID_HANDLE_VALUE) {
              return 102;
            }
            if (Authenticate(reinterpret_cast<USHORT>(hTokenFile), buf, size - 8)) {
              HANDLE hFlagFile = CreateFile(FLAG_FILE, FILE_READ_ACCESS, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
              if (hFlagFile == INVALID_HANDLE_VALUE) {
                return 104;
              }
              DWORD sz = GetFileHandleSize(hFlagFile);
              if (sz == -1) {
                return 105;
              }
              char* buffer = reinterpret_cast<char*>(HALLOC(sz));
              if (!buffer) {
                return 119;
              }
              if (!ReadFile(hFlagFile, buffer, sz, &sz, nullptr)) {
                return 106;
              }
              reinterpret_cast<uint32_t*>(msg->data())[0] = 8 + sz;
              reinterpret_cast<uint32_t*>(msg->data())[1] = 1;
              std::memcpy(reinterpret_cast<uint8_t*>(msg->data()) + 8, buffer, sz);
              HFREE(buffer);
              CloseHandle(hFlagFile);
            } else {
              reinterpret_cast<uint32_t*>(msg->data())[0] = 8;
              reinterpret_cast<uint32_t*>(msg->data())[1] = 0;
            }
          } else if (opcode == 0x0) {
            bye = true;
            reinterpret_cast<uint32_t*>(msg->data())[0] = 8;
            reinterpret_cast<uint32_t*>(msg->data())[1] = 1;
          } else {
            reinterpret_cast<uint32_t*>(msg->data())[0] = 8;
            reinterpret_cast<uint32_t*>(msg->data())[1] = 1;
          }
        }

        msg->attrib()->disable(ALPC_MESSAGE_TOKEN_ATTRIBUTE);
        msg->attrib()->disable(ALPC_MESSAGE_HANDLE_ATTRIBUTE);
        msg->attrib()->disable(ALPC_MESSAGE_VIEW_ATTRIBUTE);
        msg->attrib()->disable(ALPC_MESSAGE_DIRECT_ATTRIBUTE);

        if (!server->send(*msg)) {
          return 5;
        }
      }
      msg->clear();

      if (bye) {
        break;
      }
    }
    delete server;

    return 0;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(std::string(argv[i]));
  }
  return auth::main(args);
}
