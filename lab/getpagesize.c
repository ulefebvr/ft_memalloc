/*
** NAME
**  getpagesize - get memory page size
** 
** SYNOPSIS
**  #include <unistd.h>
**  int getpagesize(void);
** 
** DESCRIPTION
**  The function getpagesize() returns the number of bytes in a memory page, where "page"
**  is a fixed-length block, the unit for memory allocation and file mapping performed by
**  mmap(2).
** 
** NOTES
**  Whether  getpagesize() is present as a Linux system call depends on the architecture.
**  If it is, it returns the kernel symbol PAGE_SIZE, whose value depends on  the  archi‐
**  tecture  and  machine  model.  Generally, one uses binaries that are dependent on the
**  architecture but not on the machine model, in order to have a single binary distribu‐
**  tion  per  architecture.  This means that a user program should not find PAGE_SIZE at
**  compile time from a header file, but use an actual system call, at  least  for  those
**  architectures (like sun4) where this dependency exists.  Here libc4, libc5, glibc 2.0
**  fail because their getpagesize() returns a statically derived value, and does not use
**  a system call.  Things are OK in glibc 2.1.
** 
*/

#include <stdio.h>
#include <unistd.h> /* sysconf(3) */

int main(void) {
	printf("The page size for this system is %ld bytes.\n",
	       sysconf(_SC_PAGESIZE)); /* _SC_PAGE_SIZE is OK too. */
	printf("The page size for this system is %d bytes.\n",
			getpagesize());
	return 0;
}