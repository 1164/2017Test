/*
 * FetchZed.h
 *
 *  Created on: Feb 14, 2017
 *      Author: neoadmin
 */

#ifndef SRC_FETCHZED_H_
#define SRC_FETCHZED_H_
#include "WPIlib.h"
#include <NetworkTables/NetworkTable.h>
#include <stdio.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <time.h>

#include <string.h>


using namespace frc;


class FetchZed : Command {
public:
	FetchZed();


	void Execute();
	void Initialize();
	void Interrupted();
	void End();
	bool IsFinished();
	std::shared_ptr<NetworkTable> table;


	int num;

private:

      bool running_;
      int sockfd, portno, n;
      struct sockaddr_in serv_addr;
      struct hostent *server;
      int x, y, depth;
      clock_t now, then;

      char *myint;

      char buffer[256];



};



#endif /* SRC_FETCHZED_H_ */
