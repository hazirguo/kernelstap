#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main()
{
	int rc;
	rc = syscall(223);
	if (rc == -1)
		fprintf(stderr, "failed! errno is %d\n", errno);
	else
		printf("succeess! return no is %d\n", rc);
	return 0;
}
