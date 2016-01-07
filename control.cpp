#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>
#include "motors.h"

//-----------------------------------------------------------


void error(const char *str) {
	printf("error %s\n", str);
	exit(-1);
}

//-----------------------------------------------------------

class AO {
public:	
	AO();
	~AO();
	void Recenter() {};
	void Set(float x, float y);		//0-1 range
private:
	Motors *m;	
};

//-----------------------------------------------------------
	
	AO::AO()
{
	m = new Motors();
}

//-----------------------------------------------------------


void	AO::Set(float x, float y)
{
}


//-----------------------------------------------------------

class Pos {
public:
	Pos();
	Pos(float xx, float yy, float bb);	
	float	x;
	float	y;
	float   brightness;
};

//-----------------------------------------------------------

	Pos::Pos()
{
	x = -1;
	y = -1;
	brightness = -1;
}

//-----------------------------------------------------------

	Pos::Pos(float xx, float yy, float bb)
{
	x = xx;
	y = yy;
	brightness = bb;
}

//-----------------------------------------------------------


class GuideCam {
public:
	GuideCam();
	~GuideCam();
	
	void SetExposure(float time) {};
	
	Pos  FindStar();
	Pos  GetPos(); 
	void TakeImage();
private:
};

//-----------------------------------------------------------

	GuideCam::GuideCam()
{
}

//-----------------------------------------------------------

Pos	GuideCam::FindStar()
{
	return Pos(0, 0, 0);
}

//-----------------------------------------------------------

void 	GuideCam::TakeImage()
{
}

//-----------------------------------------------------------

Pos	GuideCam::GetPos()
{
	return Pos(0, 0, 0);
}	

//-----------------------------------------------------------

class	Com 
{
public:	

	Com();
	~Com();
	void		init();
	int		GetCommand() {return 0;};
private:
    	
	pthread_t	th;
	int 		sockfd;
	int		newsockfd;
	int		portno;
     	socklen_t 	clilen;

	sockaddr_in 	serv_addr;
	sockaddr_in 	cli_addr;

	void		ListenLoop();
};

	
//-----------------------------------------------------------

void Com::ListenLoop()
{
     int  n;
     char buffer[256];


     printf("got connect\n"); 
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
}

//-----------------------------------------------------------

void Com::init()
{
     printf("th2\n");

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        exit(-1);

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 50000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");

     while(1) ListenLoop();
}

//-----------------------------------------------------------


void *com_init_private(void *com_param)
{
	Com	*c;

	c = (Com *)com_param;

	c->init();

	return NULL;
}

//-----------------------------------------------------------

     Com::Com()
{
	pthread_create(&th, NULL, com_init_private, (void *)this); 
}

//-----------------------------------------------------------

     Com::~Com()
{
     close(newsockfd);
     close(sockfd);
}	

//-----------------------------------------------------------

int main()
{
	AO	*ao;
	GuideCam*guide;

	ao = new AO();
	guide = new GuideCam();
	Pos a_pos = guide->FindStar();

	Com *com = new Com();	
	while(1) {
		guide->TakeImage();
		ao->Set(0.5, 0.5);
		if (com->GetCommand() != 0) {
		}	
	}	
	return 0;
}
