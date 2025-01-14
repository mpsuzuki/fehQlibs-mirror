#include "ndelay.h"
#include "socket_if.h"
#include "iopause.h"
#include "error.h"
#include "timeoutconn.h"
#include "ip.h"

/**
  @file timeoutconn.c
  @author djb, fefe, feh
  @source qmail
  @brief socket read/write timeout handling; return code of iopause considered
*/

int timeoutconn4(int s,char ip[4],uint16 port,unsigned int timeout)
{
  struct taia now;
  struct taia deadline;
  iopause_fd x;
  unsigned int p = 0;

  if (socket_connect4(s,ip,port) == -1) {
    if ((errno != EWOULDBLOCK) && (errno != EINPROGRESS)) return -1;
    x.fd = s;
    x.events = IOPAUSE_WRITE;
    taia_now(&now);
    taia_uint(&deadline,timeout);
    taia_add(&deadline,&now,&deadline);
    for (;;) {
      taia_now(&now);
      iopause(&x,1,&deadline,&now);
      if (x.revents) break;  /* 's' available */
      if (taia_less(&deadline,&now)) {
        errno = ETIMEDOUT; /* note that connect attempt is continuing */
        return -1;
      }
      p++;
    }
    if (!socket_connected(s)) return -1;
  }

  if (ndelay_off(s) == -1) return -1;
  return 0;
}

int timeoutconn6(int s,char ip[16],uint16 port,unsigned int timeout,uint32 netif)
{
  struct taia now;
  struct taia deadline;
  iopause_fd x;
  unsigned int p = 0;

  if (socket_connect6(s,ip,port,netif) == -1) {
    if ((errno != EWOULDBLOCK) && (errno != EINPROGRESS)) return -1;
    x.fd = s;
    x.events = IOPAUSE_WRITE;
    taia_now(&now);
    taia_uint(&deadline,timeout);
    taia_add(&deadline,&now,&deadline);
    for (;;) {
      taia_now(&now);
      iopause(&x,1,&deadline,&now);
      if (x.revents) break;  /* 's' available */
      if (taia_less(&deadline,&now)) {
        errno = ETIMEDOUT; /* note that connect attempt is continuing */
        return -1;
      }
      p++;
    }
    if (!socket_connected(s)) return -1;
  }

  if (ndelay_off(s) == -1) return -1;
  return 0;
}

int timeoutconn(int s,char ip[16],uint16 port,unsigned int timeout,uint32 netif)
{
  struct taia now;
  struct taia deadline;
  iopause_fd x;
  unsigned int p = 0;
  int r;

  if (ip6_isv4mapped(ip)) 
    r = socket_connect4(s,ip + 12,port);
  else
    r = socket_connect6(s,ip,port,netif);

  if (r == -1) {
    if ((errno != EWOULDBLOCK) && (errno != EINPROGRESS)) return -1;
    x.fd = s;
    x.events = IOPAUSE_WRITE;
    taia_now(&now);
    taia_uint(&deadline,timeout);
    taia_add(&deadline,&now,&deadline);
    for (;;) {
      taia_now(&now);
      iopause(&x,1,&deadline,&now);
      if (x.revents) break;  /* 's' available */
      if (taia_less(&deadline,&now)) {
        errno = ETIMEDOUT; /* note that connect attempt is continuing */
        return -1;
      }
      p++;
    }
    if (!socket_connected(s)) return -1;
  }

  if (ndelay_off(s) == -1) return -1;
  return 0;
}
