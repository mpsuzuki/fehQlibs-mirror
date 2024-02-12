#ifndef STRALLOC_H
#define STRALLOC_H

/*
 *  Revision 20210307, Erwin Hoffmann
 *  - 
*/

#include <sys/types.h>

/* stralloc is the internal data structure all functions are working on.
 * s is the string.
 * len is the used length of the string.
 * a is the allocated length of the string.
 */

typedef struct stralloc {
  char* s;
  size_t len;
  size_t a;
} stralloc;

//extern int stralloc_ready(stralloc *,unsigned int);
extern int stralloc_ready(stralloc *sa,size_t len);
//extern int stralloc_readyplus(stralloc *,unsigned int);
extern int stralloc_readyplus(stralloc *sa,size_t len);
extern int stralloc_copy(stralloc *,stralloc *);
extern int stralloc_cat(stralloc *,stralloc *);
extern int stralloc_copys(stralloc *,const char *);
extern int stralloc_cats(stralloc *,const char *);
extern int stralloc_copyb(stralloc *,const char *,unsigned int);
extern int stralloc_catb(stralloc *,const char *,unsigned int);
//extern int stralloc_append(stralloc *,char *); /* beware: this takes a pointer to 1 char */
extern int stralloc_append(stralloc *sa,const char *in); /* beware: this takes a pointer to 1 char */
extern int stralloc_starts(stralloc *,const char *);

#define stralloc_0(sa) stralloc_append(sa,"")

extern int stralloc_catulong0(stralloc *,unsigned long,unsigned int);
extern int stralloc_catlong0(stralloc *,long,unsigned int);

extern void stralloc_free(stralloc *);

#define stralloc_catlong(sa,l) (stralloc_catlong0((sa),(l),0))
#define stralloc_catuint0(sa,i,n) (stralloc_catulong0((sa),(i),(n)))
#define stralloc_catint0(sa,i,n) (stralloc_catlong0((sa),(i),(n)))
#define stralloc_catint(sa,i) (stralloc_catlong0((sa),(i),0))

#endif
