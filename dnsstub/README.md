/*! \mainpage

Stub Resolver
=============

Simple DJBDNS stub-resolver based on 'djbdns-1.05(IPv6)' allowing for each 
calling application individually to include up to 16 DNSCACHEIP(s) 
as DNS forwarding/resolving servers to be tried sequentially.

IP Addresses
------------

Here,
 - global IPv6,
 - IPv6 ULA, and
 - IPv6 LLU addresses with a given Interface-Id
can be specified. The IPv4 format could be either a 
 - legacy dotted-decimal or a
 - IPv4-mapped IPv6 address.

In any case, compactified IPv6 addresses are understood.
IPv4/IPv6 addresses in brackets are understood by dns_ip.

Resolver Call
-------------

If $DNSCACHEIP is not provided as environment variable, the stub-resolver
will use the system-wide 
  - /etc/resolv.conf 
file; however now without the capability for IPv6 LLU addresses.
While IPv4-mapped IPv6 addresses are supported here by default as well, 
care has to taken not to jeopardize other client's usage.

Name Qualification
------------------

If provided, the stub-resolver uses either a system-wide configuration file
  - /etc/dnsrewritefile or assumes this file to available as given in
  - $DNSREWRITEFILE 
in order to define persistent mapping-rules of local domain names to public 
ones (for lookup) or IP addresses (for direct matching).

Well-known domain names 'localhost', 'ip4-loopback' and 'ip6-loopback'
are handled locally, thus no DNS query is used (RFC 6761).
'localhost' is advertised as '::1' and '::ff:127.0.0.1' in it's native
IPv6 format. It is up to the caller to convert the IPv6-mapped IPv4
address to the IPv4 format.

Local domain names can be alternatively specified (per application) using
the environment variable
  - $LOCALDOMAIN
to be appended to unqualified hostnames dynamically. This is roughly equivalent
with the 'search' string in /etc/resolv. Several domains names may be
specified within $LOCALDOMAIN separated by blanks.

See: https://cr.yp.to/djbdns/qualify.html


Specific DNS Record type lookup
-------------------------------

* dns_ip (A, AAAAA)
* dns_name (PTR)
* dns_cname (CNAME)
* dns_txt (TXT) -- now considering several 'labels'
* dns_mx (MX)


Internals
---------

* UDP message size:
Unlike other implementations, this DNS stub-resolver supports UDP packet 
sizes up to 1028 byte without the need for (E)DNS0 packet enhancements. 

* DNS UDP query retrials:
In case the NS is not able to initally reply to the query, 
it is retried again at the intervalls {1, 2, 4, 8, 16} secs.

* DNS name qualification (dns_ip_qualify):
Well-known domain names are qualified locally without invoking a DNS query
while handling IPv4 and IPv6 addresses separately.

* NS qualification/sorting for NS replies:
NS qualification is not supported (yet), thus we use a randomly sorted
list of NS IP addresses. 

* Query/Reply to/from DNS Cache servers/forwarders:
Neither message (CurveDNS) nor transport layer (TLS) encryption is provided;
the sub-resolver 'trusts' it's upstream caches/forwarders. We recommend to
setup communication on private IPv4/IPv6 addresses; if applicable.

* DNS TXT Records:
The label substructure is now recognized in the RDATA section;
each label may have the size of 255 byte.
The length information is excluded from the output. 
Only printable characters are recognized in the output.

* Return Codes:
Different from DJB's initial routines, the DNS front-end routines
  dns_cname*, dns_ip*, dns_mx*, dns_name*, dns dns_txt* 
return now the number of replies received (not bytes!). 
Thus, three cases need to be considered:

 - rc <  0: Problem occured (SOFTFAIL, HARDFAIL)
 - rc =  0: No answer obtained (but query was successful) = NXDOMAIN
 - rc >  0: rc answers received; positive reply

For return codes < 0, the following conventions have been applied:

	include/dnsresolv.h

\#define DNS_NXD	 0
\#define DNS_MEM  -1
\#define DNS_ERR  -2              /* parsing errors and others */
\#define DNS_COM  -3              /* (socket) communication errors */
\#define DNS_INT  -4              /* internal errors */
\#define DNS_SOFT -5              /* either -2 or -3 */
\#define DNS_HARD -6              /* CNAME loop problem */

The modification of the return code is typically not problematic,
since mostly just rc = -1 is checked.

In the future, these return codes are subject of change. 
Thus, instead of

   if (dns_XX(...) == -1) 

one shoud use the more general syntax

   if (dns_XX(...) < 0)

to check for 'negative' results, allowing further actions
and refinements given the calling sequence.



Environment Variables Read
--------------------------

$DNSCACHEPIP	The upstream resolver's IP[v4|v6] addresses (up to 32).
	IPv6 LLU addresses may be suffixed with the interface name.
$DNSREWRITEFILE Alternate location for the system-wide
	/etc/dnsrewrite
file
$LOCALDOMAIN 	Additional local domain name appended to unqualified
	hostnames dynamically. 

Sample for the file /etc/dnsrewrite:

\#annything.local -> me
\-.example.com:me
\# me -> 127.0.0.1
\=me:127.0.0.1
\# any.name.a -> any.name.af.mil
\*.a:.af.mil
\# any-name-without-dots -> any-name-without-dots.heaven.af.mil
\?:.heaven.af.mil
\# remove trailing dot
\*.:

and DJB's explanations are given here:

Instructions are followed in order, each at most once. There are four types of instructions:

\=post:new means that the host name post is replaced by new.
\*post:new means that any name of the form prepost is replaced by prenew.
\?post:new means that any name of the form prepost, where pre does not contain dots or brackets, is replaced by prenew.
\-post:new means that any name of the form prepost is replaced by new.

Erwin Hoffmann, June 2023.
