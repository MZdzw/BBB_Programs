#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char **argv)
{
	int s, i; 
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Receive Demo\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}
    printf("Here I am\n");
	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

    frame.can_id = 0x101;
	frame.can_dlc = 2;
	sprintf(frame.data, "He");

    printf("Sending...\n");

	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

    for (int x = 0; x < 10; x++)
    {
	    // nbytes = read(s, &frame, sizeof(struct can_frame));
        nbytes = recv(s, &frame, sizeof(struct can_frame),
                      0);
        printf("siema\n");

 	    if (nbytes < 0) {
	    	perror("Read");
	    	return 1;
	    }

	    printf("%d: 0x%03X [%d] ", x, frame.can_id, frame.can_dlc);

	    for (i = 0; i < frame.can_dlc; i++)
	    	printf("%02X ",frame.data[i]);

	    printf("\r\n");
    }

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
