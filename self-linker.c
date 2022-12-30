#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <stdio.h>
#include <stdlib.h>

extern void *_GLOBAL_OFFSET_TABLE_;

int main(int argc, char*argv[]){
	void *libc_p; /* the address of the libc */
	void *puts_offset; /* the offset of the puts function within libc */

	if (!(libc_p = dlopen(LIBC_SO, RTLD_LAZY))) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();

	if (!(puts_offset = dlsym(libc_p, "puts"))) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();

	unsigned long *puts_entry = &_GLOBAL_OFFSET_TABLE_ + 3; /* puts' entry in the got */
	*puts_entry = (unsigned long)puts_offset; /* set puts' entry to the libc puts */

	puts("TEST1");
	puts("TEST2");
}

