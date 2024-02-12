#ifndef GENALLOC_H
#define GENALLOC_H

/*
 *  Revision 20210307, Erwin Hoffmann
 *  - 
*/

#include <sys/types.h>

/* GEN_ALLOC demystified: 
   
   GEN_ALLOC generates a list of self-defined types (structs) in an
   allocated contiguous heap chunk while copying the content of the 
   entire field members or appending the existing field.
   GEN_ALLOC types care of currently used and/or allocated bytes of field.

Makros: 
  GEN_ALLOC_ready    (ta,type,field,len,a,i,n,x,base,ta_ready)
  GEN_ALLOC_readyplus(ta,type,field,len,a,i,n,x,base,ta_rplus)
  GEN_ALLOC_append   (ta,type,field,len,a,i,n,x,base,ta_rplus,ta_append) 

   0. ta: 'type alloc' - typedef'ed struct name (aka ipalloc et al.)
   1. type: defined struct (used for size information) 
   2. field: declared public name of struct
   2. len: used length of string 
   4. a: allocated size
   5. i: current allocated size for member x
   6. n: bytes to allocate; in 'ready' mode: +size of one entry;
                            in 'readyplus' mode: +size of +used size of one entry
   7. x: local name (alias to field name)
   8. base: size of single entry
   9. ta_ready/ta_readyplus (operation)
  10. ta_append (operation)

*/

/* file: gen_alloc.h */
#define GEN_ALLOC_typedef(ta,type,field,len,a) \
  typedef struct ta { type *field; unsigned int len; unsigned int a; } ta;

/* file: gen_allocdefs.h   (deprecated) */
// used in: ipalloc, prioq, qmail-remote, qmail-inject, token822
#define GEN_ALLOC_ready(ta,type,field,len,a,i,n,x,base,ta_ready) \
int ta_ready(x,n) register ta *x; register unsigned int n; \
{ register unsigned int i; \
  if (x->field) { \
    i = x->a; \
    if (n > i) { \
      x->a = base + n + (n >> 3); \
      if (alloc_re(&x->field,i * sizeof(type),x->a * sizeof(type))) return 1; \
      x->a = i; return 0; } \
    return 1; } \
  x->len = 0; \
  return !!(x->field = (type *) alloc((x->a = n) * sizeof(type))); }

#define GEN_ALLOC_readyplus(ta,type,field,len,a,i,n,x,base,ta_rplus) \
int ta_rplus(x,n) register ta *x; register unsigned int n; \
{ register unsigned int i; \
  if (x->field) { \
    i = x->a; n += x->len; \
    if (n > i) { \
      x->a = base + n + (n >> 3); \
      if (alloc_re(&x->field,i * sizeof(type),x->a * sizeof(type))) return 1; \
      x->a = i; return 0; } \
    return 1; } \
  x->len = 0; \
  return !!(x->field = (type *) alloc((x->a = n) * sizeof(type))); }

#define GEN_ALLOC_append(ta,type,field,len,a,i,n,x,base,ta_rplus,ta_append) \
int ta_append(x,i) register ta *x; register type *i; \
{ if (!ta_rplus(x,1)) return 0; x->field[x->len++] = *i; return 1; }

#endif
