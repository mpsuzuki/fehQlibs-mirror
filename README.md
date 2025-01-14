/*! \mainpage

qlibs - C library and headers based on "djb's libs" and libowfat
================================================================

Initially, these libs were excluded from *qmail and forseen to use with eQmail. 
As the packages of djb (D.J. Bernstein) uses these libs in different versions, 
there comes up the need to have a consistent state. 
As time was going on, there was also a need to include additional functionality 
and up-to-date best practices. 
Short - this was the point where some parts from libowfat were included.

The current fehQlibs rather accustom to the needs of different OS.

In theorie - these libs can be used with any djb software.

Achievements
------------

- IPv4/IPv6 unification:

The current package supports unified IPv4/IPv6 socket calls, while IPv6 is the default.

- DNS stub-resolver:

The provided DNS stub-resolver is IPv4 and IPv6 aware.
See the README in the ./dnsstub directory for details.


Installation
------------

Some build options can be configured through 'conf-build'.  
Read the comments in this file for more information. 

* Building:

a) Static libs:

Execute

     $ make

which does the steps of './configure && make'. 
Don't forget to make sure that libs and headers will be found by the compiler/linker.
For convenience, link the current version of fehQlibs to qlibs

     $ ln -s fehQlibs-XY qlibs

b) Shared objects libs:

You can also build dynamic libaries for qlibs and dnsresolv. After

     $ make

call 

     $ make shared

* Deployment:

In case conf-build has been customized to include the location of

- HDRDIR
- LIBDIR

issue 

     $ make install

to deploy the include files and libs at the given location.
By default, for the libs the parent directory is used.

* Verification:

Check the ELFCLASS of the generated binaries in the source directory while calling

     $ file open.o

They need to comply with your OS. See 'conf-build' for options.

* Resulting libraries:

The following libraries are generated:

- qlibs.a - static basic [w/o DNS] lib (linked to libqlibs.a)
- dnsresolv.a - static DNS resolver lib (linked to libdnsresolv.a)

and perhaps

- libqlibs.so - dynamic, position independent (PIC) 'shared object' lib
- libdnsresolv.so - dynamic, position independent (PIC) 'shared object' lib

These libs are of type ELF64 or ELF32 depending on the system.

Use 'ar -t' to get the included members of the static libs.
Use 'nm' to view the members and symbols of the libs.

The shared object libs are known NOT not work on MacOS.


Man pages
---------

In the ./man directory the current man pages for the basic qlibs routines are included.
Determine the current $mandir and (as root) install the man pages:

     $ cp *.3 $mandir/man3/


Packaging
---------

The fehQlibs are incompatible with Gentoo's parallel compilation flag '-jN' for N > 1.


Compilation
-----------

Starting with version fehQlibs-15b, GCC 10 and Clang compatibility is provided, 
which means ISO C conformance.
Since fehQlibs-17 strong coupling of application routines previously introduced 
by the global (external) 'ipv4socket' variable are avoided. 
stralloc.h is decoupled from genalloc.h (to be included separately).
This respects the GCC 10 compilation unit behavior.


-----

Updated: 20170329, Kai Peter

Updated: 20220706, Erwin Hoffmann
