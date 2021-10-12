#ifndef __OS1_IOCTLS_H__
#define __OS1_IOCTLS_H__

//ioctl:
//upper 16 bits: reserved
//middle 6 bits: request class
//lower 10 bits: request id
//request classes:
//	0=generic;
//	1=net device.

#define IOCTL_GETMAC	((1<<10)+1)
#define IOCTL_SETMAC	((1<<10)+2)
#define IOCTL_RESETMAC	((1<<10)+3)

#define IOCTL_ACCEPT	((1<<10)+256)

#endif
