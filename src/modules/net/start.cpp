#include "mbed.h"
#include "EthernetInterface.h" /* net/eth */

namespace {
  const int HTTP_SERVER_PORT = 8080;
}

int start (void) {
  EthernetInterface eth;
  eth.init(); // Use DHCP
  eth.connect();
  printf("MBED: Server IP Address is %s:%d" NL, eth.getIPAddress(), HTTP_SERVER_PORT);

  HTTPServer server;
  server.bind(HTTP_SERVER_PORT);
  server.listen();
  server.set_blocking(false,10);

  while(true) {
    TCPSocketConnection client;
    int response = server.accept(client);
    if(response < 0)
      return;
    client.set_blocking(false,10);
  }

