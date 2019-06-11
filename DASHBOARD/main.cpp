#include "mainwindow.h"
#include <QApplication>
#include <QEventLoop>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "linux-can-utils/lib.h"
int main(int argc, char *argv[])
{
    int s; /* can raw socket */
    int nbytes;
    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;
    fprintf(stderr,"CAN testing\n");
    /* open socket */
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
            perror("socket");
            return 1;
    }
    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, "can0");
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0){
            perror("SIOCGIFINDEX");
            //return 1;
    }
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("bind");
            return 1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    bool killLoopflag = false;
    w.show();
    int i = 0;
    while(1){

        //if ((nbytes = read(s, &frame, sizeof(frame))) != sizeof(frame)) {
                 //perror("read");
                 //return 1;
        //}

        int dlc = (frame.can_dlc > 8)? 8 : frame.can_dlc;
        w.run(i);
        i++;
        QApplication::processEvents();
        if(killLoopflag)
               break;
        QThread::msleep(50);
    }
    return a.exec();
}
