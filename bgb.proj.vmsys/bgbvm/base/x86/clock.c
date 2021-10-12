int clock_hour,clock_minute,time_second;

int time_seconds_count;
extern int time_msec_count; /* count in 976usec fractions of second */
extern void _irq0_ISR();
extern void _irq8_ISR();

/*
   called every second by irq8 isr
*/
void clock_second()
{
	time_second++;
	time_seconds_count++;

	if(time_second>=60)
	{
		clock_minute++;
		time_second=0;
	}
	if(clock_minute>=60)
	{
		clock_hour++;
		clock_minute=0;
	}
	if(clock_hour>=24)
	{
		clock_nextday();
		clock_hour=0;
	}
}

/* make do something */
int clock_nextday()
{
}

int Clock_Init()
{
	kprint("Setting up timing and clock.\n");
	/* make read from cmos */
	clock_hour=0;
	clock_minute=0;
	time_second=0;

	time_msec_count=0;
	time_seconds_count=0;

	pit_set(0,100);
	NewIntISR(&_irq0_ISR,0x20,0);
	NewIntISR(&_irq8_ISR,0x28,0);
	enable_irq(0);
	enable_irq(8);
}

int delay(int ms) /* delay, uses clock chip */
{
	int c;
	c=time_msec_count;
	while(ms>0)
	{
		if(time_msec_count>c)ms-=time_msec_count-c;
			else ms-=(1000-c)+time_msec_count;
		c=time_msec_count;
	}
	return(0);
}

int Sys_TimeMS()
{
	return(time_msec_count+(time_seconds_count*1000));
}

int Sys_TimeDUS()
{
	static int lastms=0;
	int d;
	if(!lastms)lastms=time_msec_count;
	d=time_msec_count-lastms;
	lastms=time_msec_count;
	return(d*1000);
}
