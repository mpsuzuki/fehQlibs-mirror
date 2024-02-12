#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "close.h"         /* better use unistd.h ? */
#include "ndelay.h"
#include "socket_if.h"
#include "error.h"

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT EINVAL
#endif

/**
	@file socket_tcp.c
	@author djb, fefe, feh
	@source ucspi-tcp6
	@brief setup TCP stream socket
*/

int socket_tcp4(void)
{
  int s;

  s = socket(AF_INET,SOCK_STREAM,0);
  if (s != -1) 
    if (ndelay_on(s) == -1) { close(s); return -1; }

  return s;
}

int socket_tcp6(void)
{
  int s;

  s = socket(AF_INET6,SOCK_STREAM,0);
  if (s != -1) 
    if (ndelay_on(s) == -1) { close(s); return -1; }

  return s;
}

int socket_tcp(void)
{
  int s;

  s = socket(AF_INET6,SOCK_STREAM,0);
  if (s == -1) 
    if (errno == EINVAL || errno == EAFNOSUPPORT || errno == EPROTO || errno == EPROTONOSUPPORT) 
       s = socket(AF_INET,SOCK_STREAM,0);

  if (s != -1) 
    if (ndelay_on(s) == -1) { close(s); return -1; }

  return s;
}

int socket_tcpnodelay(int s)
{
  int opt = 1;
  return setsockopt(s,IPPROTO_TCP,1,&opt,sizeof(opt)); /* 1 == TCP_NODELAY */
}
