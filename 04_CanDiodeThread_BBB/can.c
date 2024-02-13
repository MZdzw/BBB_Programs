#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

void* canThread(void* args)
{
    printf("Initialize can thread...\n");

	int s, i; 
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
		perror("Socket");
		return 1;
	}
    printf("Here I am\n");
	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
		perror("Bind");
		return 1;
	}

    for(;;)
    {
        nbytes = recv(s, &frame, sizeof(struct can_frame), 0);

 	    if (nbytes < 0) 
        {
	    	perror("Read");
	    	return 1;
	    }

	    printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);

	    for (i = 0; i < frame.can_dlc; i++)
	    	printf("%02X ",frame.data[i]);

	    printf("\r\n");
    }

	if (close(s) < 0) 
    {
		perror("Close");
		return 1;
	}
}

