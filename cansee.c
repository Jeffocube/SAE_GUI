#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "lib.h"

int main(int argc, char **argv)
{
        int s; /* can raw socket */ 
        int nbytes;
        struct sockaddr_can addr;
        struct can_frame frame;
        struct ifreq ifr;
	unsigned int spd = 0;
        int i;

        /* CAN message to be sent out */
        unsigned char buff[] = "7DF#0201050000000000";

        fprintf(stderr,"CAN testing\n");

        /* parse CAN frame */
        if (parse_canframe(buff, &frame)){
                fprintf(stderr, "\nWrong CAN-frame format!\n\n");
                fprintf(stderr, "Try: <can_id>#{R|data}\n");
                fprintf(stderr, "can_id can have 3 (SFF) or 8 (EFF) hex chars\n");
                fprintf(stderr, "data has 0 to 8 hex-values that can (optionally)");
                fprintf(stderr, " be seperated by '.'\n\n");
                fprintf(stderr, "e.g. 5A1#11.2233.44556677.88 / 123#DEADBEEF / ");
                fprintf(stderr, "5AA# /\n     1F334455#1122334455667788 / 123#R ");
                fprintf(stderr, "for remote transmission request.\n\n");
                return 1;
        }
        /* open socket */
        if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
                perror("socket");
                return 1;
        }
        addr.can_family = AF_CAN;
        strcpy(ifr.ifr_name, "vcan0");
        if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) 
                perror("SIOCGIFINDEX");
        addr.can_ifindex = ifr.ifr_ifindex;


	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

        if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("bind");
                return 1;
        }

        /* send frame */
        for(i=0;i<100;i)
        {	
		spd = 0;
                if ((nbytes = read(s, &frame, sizeof(frame))) != sizeof(frame)) {
                        perror("read");
                        return 1;
                }

//                fprintf(stderr, "%d \n", i);
                //new testing code
                int dlc = (frame.can_dlc > 8)? 8 : frame.can_dlc;
                if(frame.can_id & CAN_ERR_FLAG)
                        fprintf(stdout, "%08X# \n", (frame.can_id & (CAN_ERR_MASK|CAN_ERR_FLAG)));
//                for(unsigned i = 0; i < dlc; i++){
//                       fprintf(stdout, "%02X ", frame.data[i]);
//                }
		if(dlc > 1)
			spd = spd | frame.data[0];
		fprintf(stdout, "%u mph", spd);
                fprintf(stdout, "\n");
                //changed usleep by adding 1 more zeroes
                //end testing
                usleep(1000); /* Delay before next loop */
        }

        close(s);
        return 0;

}
