/*
 * FetchZed.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: neoadmin
 */

#include "Autonomous/FetchZed.h"



FetchZed::FetchZed() : Command("FetchZed") {
	// TODO Auto-generated constructor stub
   x=0;
   y=0;
   depth=-1;
   running_ = true;
  num=1000;
  portno=5001;

  DriverStation::GetInstance().ReportError("FetcZed START\n");
  table = NetworkTable::GetTable("ZED");
  now=clock();
  table->PutNumber("x",-1);
  table->PutNumber("y",-1);
  table->PutNumber("depth",-1);
  table->PutNumber("time",-1);

  /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
       perror("ERROR opening socket");
       exit(1);
    }

    server = gethostbyname("tegra-ubuntu.local"); // This will be the mDNS name for the ubuntu

    if (server == NULL) {
       fprintf(stderr,"ERROR, no such host\n");
       exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
      serv_addr.sin_port = htons(portno);



} // of FetchZed constructor

void FetchZed::Initialize()
{

}

void FetchZed::Execute(){
	char mystring[100];
	 x=-1;
	 y=-1;
	 depth=-1;
	 now=clock();
	 then=table->GetNumber("time",0);

	 if (now < then + CLOCKS_PER_SEC ) return;   // if a second has not occurred then do nothing

	 /* Create a socket point */
	     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	     int mytrue = 1;
	     setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&mytrue,sizeof(int));

	     if (sockfd < 0) {
	        perror("ERROR opening socket");
	        exit(1);
	     }

	     server = gethostbyname("tegra-ubuntu.local"); // This will be the mDNS name for the ubuntu

	     if (server == NULL) {
	        fprintf(stderr,"ERROR, no such host\n");
	        exit(0);
	     }

	     bzero((char *) &serv_addr, sizeof(serv_addr));
	     serv_addr.sin_family = AF_INET;

	     bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	       serv_addr.sin_port = htons(portno);


	  /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
	      //perror("ERROR connecting");
	    // exit(1);
    } // of if-connect
    else {
      bzero(buffer,256);
      n = read(sockfd, buffer, 255);

      if (n < 0) {
         perror("ERROR reading from socket");
      }
      else {
         myint=strtok(buffer,",");
         x=atoi(myint);
         myint=strtok(NULL,",");
         y=atoi(myint);
         myint=strtok(NULL,",");
         depth=atoi(myint);
      }
    }


    if ( x > 2 && y > 2 && depth > 2) {
		table->PutNumber("x",x);
		table->PutNumber("y",y);
		table->PutNumber("depth",depth);
		table->PutNumber("time",clock());
    }



	sprintf(mystring,"I am running %d %d %d %d\n",(int)table->GetNumber("x",-1),
			        (int)table->GetNumber("y",-1),(int)table->GetNumber("depth",-1),num);
	DriverStation::GetInstance().ReportError(mystring);
	if (num-- <= 0) running_ = false;
	shutdown(sockfd,SHUT_RDWR);
	close(sockfd);

}


bool  FetchZed::IsFinished()  {
	return(!running_);

}

void FetchZed::End()
{

}

// Make this return true when this Command no longer needs to run execute()
void FetchZed::Interrupted()
{

}







