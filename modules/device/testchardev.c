#include <stdio.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int fd;
	int i;
	char buffer[20];

	fd =  open("/dev/char_dev", O_RDWR);
	if(fd < 0) {
		printf("open error: %s\n\n", strerror(errno));
		return 1;
	} else
		printf("open----success!\nThe fd:%d\n\n", fd);

	if(read(fd, buffer, sizeof(buffer)) < 0){
		printf("read file error: %s\n", strerror(errno));
	} else {
        	printf("read----success!\nThe readings: ");
		for(i = 0; i < sizeof(buffer); i++)printf("%c", buffer[i]);
        	printf("\n\n");
	}

        if(write(fd, buffer, sizeof(buffer)) < 0) {
                printf("write----failed!\nthe error: %s\n\n", strerror(errno));
        } else printf("write---success!\n\n");

	if(close(fd) < 0) printf("close file error!\n");
	else printf("close----success!\n\n");
  	return 0;
}
