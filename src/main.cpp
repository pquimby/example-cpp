#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 This example creates a server that listens for incoming UDP packets that are control
 instructions. It then does something using the payload of the packet, which is
 expected to be an integer number in ascii format.

 To test, run, and then send packets locally like this:
 `echo "314" > /dev/udp/127.0.0.1/8000`
 **/

int SERVER_PORT = 8000; // Or whatever you want, 8000 is commonly available

int main(int argc, char* argv[]) {

  // Make a motor connection
  printf("Created a motor connection\n");
  // Exit program if that doesn't work
  // Send some message about current position since it might not be zero?
  printf("Starting network stuff.\n");

  // Setup some network objects
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(SERVER_PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  // Try to make a socket
  int sock;
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("Could not create a socket\n");
    return 1;
  }
  if ((bind(sock, (struct sockaddr *)&server_address,
	    sizeof(server_address))) < 0) {
    printf("Could not bind socket\n");
    return 1;
  }

  // Get setup to receive a connection
  struct sockaddr_in client_address;
  socklen_t client_address_len = 0;

  // Start asking for connections
  while (true) {
    printf("Waiting for network traffic...\n");
    char buffer[8]; // Some tiny amount of temp storage for the payload

    // Read the content into buffer from an incoming client
    int len = recvfrom(sock, buffer, sizeof(buffer)-1, 0,
		       (struct sockaddr *)&client_address,
		       &client_address_len);
    buffer[len] = '\0';

    // Figure out what time it is to print a helpful status update
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    
    // Say something helpful about what network traffic was received at current time
    printf("%.*s: received: '%.*s'\n",
	   19, // Magic length of asctime format that looks like this: 'Wed Sep  9 22:25:34'
	   asctime(timeinfo), // Convert time to a human-readable text format
	   len-1, // One less than the length of the message, to cut the newline
	   buffer);

    int steps = -1; // An integer to store the packet contents
    steps = atoi(buffer); // Parse the packet into a number

    // Do something in response to the packet
    printf("Move the motor by %d steps now.\n", steps);
  }

  // This will never happen due to the infinite loop, but for good measure return 0.
  return 0;
}
