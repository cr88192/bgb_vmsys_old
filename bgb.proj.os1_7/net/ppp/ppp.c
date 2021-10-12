#include <general.h>
#include <net/ppp.h>

ppp_ctx *ppp_context;
int ppp_sync;

int ppp_loop(ppp_ctx *ctx)
{
	int i;
	byte *buf, *s;

	kprint("ppp loop 0.\n");

	buf=kalloc(65536); //official default mru is 1500, but this does not hurt...

	kprint("ppp loop 1.\n");

	while(1)
	{
		if(!ppp_sync)
		{
			kthread_blocked();
			continue;
		}

//		kprint("ppp loop 2.\n");

		i=vfgetc(ctx->fd);
//		kprint("%d ", i);

		if(i==0x7e) //begining of frame?
		{
//			kprint("frame1 {\n");
//			i=vfgetc(ctx->fd);
//			if(i!=0xff)continue; //garbage
//			i=vfgetc(ctx->fd);
//			if(i!=0x03)continue; //garbage

			kprint("frame2\n");

			//begin decoding frame
			s=buf;
			while(1)
			{
				i=vfgetc(ctx->fd);
//				kprint("%d ", i);

				if(i==0x7e)break;
				if(i==0x7d)
				{
					i=vfgetc(ctx->fd);
					i^=0x20;
				}
				*s++=i;

				if((int)(s-buf)>=65536)
				{
					kprint("frame size error.\n");
					break;
				}
			}
//			kprint("}\nframe3\n");

			//here I would check verify checksum
			PPP_DecodeFrame(ctx, buf, (int)(s-buf)-2);
			memset(buf, 0, 1024);

			kprint("frame4\n");
		}
	}
}

int PPP_TrySync()
{
	kprint("PPP_TrySync\n");
	ppp_sync=1;
	PPP_SendLCP(ppp_context, LCP_CONF_REQ, 0, 0, ppp_context);
}

int PPP_NoSync()
{
	ppp_sync=0;
}

int PPP_Init()
{
	kthread *th1, *th2;
	VFILE *dev1, *dev2;
	ppp_ctx *ctx1, *ctx2;

	kprint("PPP Init.\n");

	dev1=vffopen("/devices/serial/0", "r+b");
	if(!dev1)
	{
		kprint("vffopen failed.\n");
		return(0);
	}

//	vfpipe(&dev1, &dev2);

	ctx1=kalloc(sizeof(ppp_ctx));
	ctx1->fd=dev1;
	ctx1->peer_mru=1500;

	ppp_context=ctx1;

//	ctx2=kalloc(sizeof(ppp_ctx));
//	ctx2->fd=dev2;
//	ctx2->peer_mru=1500;

//	kprint("ctx %X\n", ctx);

	th1=kthread_spawn(0, &ppp_loop, ctx1);
	kthread_start(th1, PRIORITY_NORMAL);

//	th2=kthread_spawn(0, &ppp_loop, ctx2);
//	kthread_start(th2, PRIORITY_NORMAL);

//	ppp_sync=1;
//	PPP_SendLCP(ctx1, LCP_CONF_REQ, 0, 0, ctx1);
}
