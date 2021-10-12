int pit_set(int chan,int freq)
{
	int div;
	div=1192180/freq;
	outportb(0x43,(chan<<6)+0x36);
	outportb(0x40+chan,div&0xFF);
	outportb(0x40+chan,(div>>8)&0xFF);
}