#include <general.h>
#include <gtk/gtk.h>

float frametime, realtime;
double Sys_Time();
int Sys_Sleep(int us);

GtkWidget *toolbar, *mainbox;
GtkWidget *filebox;

float lasttime, time, lastcleantime;

extern int core_init();
extern int reboot();

int main_loop_break, idle_loop_break;

int _argc;
char **_argv;

int test_thread(void *data)
{
	while(1)
	{
		kusleep(1000000);
		kprint(data);
	}
	return(0);
}

int main_idle_handler(gpointer data)
{
	time=Sys_Time();
//	if((time-lasttime)<0.01)
//	{
//		Sys_Sleep(1000); /* sleep 1ms */
//		continue;
//	}

	if(main_loop_break)gtk_main_quit();

	frametime=time-lasttime;
	lasttime=time;
	realtime=time;

	if((time-lastcleantime)>1)
	{
//			printf("client clean\n");
//			MM_Print();
		MMGC_Collect();
		lastcleantime=time;
	}

//		printf("frame: %f %f\n", time, frametime);

	Render_Frame();

	return(TRUE);
}

void file_ok_sel(GtkWidget *w, GtkFileSelection *fs)
{
	char *n, n2[256];
	ModelSeg *ms;

	n=gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
	strcpy(n2, "/sysroot");
	strcat(n2, n);

	ms=Model_LoadModel(n2);
	if(!ms)return;

	Model_EntityFromModel(0, ms);
}

int create_open_filebox(GtkWidget *w, void *d)
{
	filebox = gtk_file_selection_new ("Open File");

	gtk_signal_connect (GTK_OBJECT (filebox), "destroy",
		(GtkSignalFunc) gtk_widget_destroy, &filebox);

	gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filebox)->ok_button),
		"clicked", (GtkSignalFunc) file_ok_sel, filebox );

	/* Connect the cancel_button to destroy the widget */
	gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filebox)->cancel_button),
		"clicked", (GtkSignalFunc) gtk_widget_destroy,
		GTK_OBJECT (filebox));

	gtk_file_selection_set_filename (GTK_FILE_SELECTION(filebox),
		"/var/lib/eng0/base/models/");

	gtk_widget_show(filebox);
}

int create_toolbar()
{
	GtkWidget *table, *button;

	table = gtk_table_new (4, 2, TRUE);

//	gtk_container_add (GTK_CONTAINER (toolbar), table);
	gtk_box_pack_end (GTK_BOX (mainbox), table, TRUE, TRUE, 2);

	button = gtk_button_new_with_label ("button 1");

//	gtk_signal_connect (GTK_OBJECT (button), "clicked",
//		GTK_SIGNAL_FUNC (callback), (gpointer) "button 1");

	gtk_table_attach_defaults (GTK_TABLE(table), button, 0, 1, 0, 1);

	gtk_widget_show (button);

	gtk_widget_show (table);
}

int menu_quit(GtkWidget *w, void *d)
{
	main_loop_break=1;
}

int create_menu()
{
	GtkWidget *menu;
	GtkWidget *menu_bar;
	GtkWidget *root_menu;
	GtkWidget *menu_item;

	menu = gtk_menu_new ();

	menu_item = gtk_menu_item_new_with_label ("Open");
	gtk_menu_append (GTK_MENU (menu), menu_item);
	gtk_signal_connect_object (GTK_OBJECT (menu_item), "activate",
		GTK_SIGNAL_FUNC (create_open_filebox), NULL);
	gtk_widget_show (menu_item);

	menu_item = gtk_menu_item_new_with_label ("Save");
	gtk_menu_append (GTK_MENU (menu), menu_item);
//	gtk_signal_connect_object (GTK_OBJECT (menu_item), "activate",
//		GTK_SIGNAL_FUNC (menuitem_response), NULL);
	gtk_widget_show (menu_item);

	menu_item = gtk_menu_item_new_with_label ("Quit");
	gtk_menu_append (GTK_MENU (menu), menu_item);
	gtk_signal_connect_object (GTK_OBJECT (menu_item), "activate",
		GTK_SIGNAL_FUNC (menu_quit), NULL);
	gtk_widget_show (menu_item);

	root_menu = gtk_menu_item_new_with_label ("Root Menu");

	gtk_widget_show (root_menu);

	/* Now we specify that we want our newly created "menu" to be the menu
	* for the "root menu" */
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

	/* Create a menu-bar to hold the menus and add it to our main window */
	menu_bar = gtk_menu_bar_new ();
	gtk_box_pack_start (GTK_BOX (mainbox), menu_bar, FALSE, FALSE, 2);
	gtk_widget_show (menu_bar);

	gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), root_menu);
}

int main_guiloop(void *data)
{

	gtk_init (&_argc, &_argv);

	toolbar = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (toolbar), "BGBCAD Toolbar");

	gtk_signal_connect (GTK_OBJECT (toolbar), "destroy",
//		GTK_SIGNAL_FUNC (gtk_exit), NULL);
		GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	gtk_signal_connect (GTK_OBJECT (toolbar), "delete_event",
//		GTK_SIGNAL_FUNC (gtk_exit), NULL);
		GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	gtk_container_set_border_width (GTK_CONTAINER (toolbar), 0);
	gtk_widget_realize(toolbar);

	mainbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (toolbar), mainbox);
	gtk_widget_show (mainbox);

	create_menu();
	create_toolbar();

//	create_open_filebox();

	gtk_widget_show (toolbar);

//	MM_Init();
//	Con_Init();
//	Var_Init();
//	VPath_Init();
//	Entity_Init();

	Render_Init();

//	Scr_Init();

	lasttime=Sys_Time();
	lastcleantime=lasttime;

	gtk_timeout_add(20, (GtkFunction) main_idle_handler, NULL);

	gtk_main ();

	Con_Printf("main loop exited.\n");
//	fgetc(stdin);

	Window_DeInit();
}

int main_loop(void *data)
{
	static char cb[256];
	kthread *th1, *th2;

//	kthread_dumpthread(current_thread);

	kprint("main loop.\n");

//	MMGC_Collect();
//	MM2_InitLow2();

//	th1=kthread_spawn(0, &test_thread, "thread1\n");
//	kthread_start(th1, 16);
//	kthread_dumpthread(th1);

//	th2=kthread_spawn(0, &test_thread, "thread2\n");
//	kthread_start(th2, 16);
//	kthread_dumpthread(th2);

//	Interp_EvalStringTop("(load \"/floppy/init.scm\")");

//	kthread_dumpthread(current_thread);

	while(!main_loop_break)
	{
		kprint("/# ");
//		Rendercore_Frame();
		kgets(cb);
		Con_SubmitCommand(cb);
//		MM2_ObjAlloc(1024, 1);
//		MMGC_Collect();
//		Rendercore_Frame();
//		Heap0_Commit();
	}

	idle_loop_break=1;
//	while(1)sys_halt();
}

int main_inner()
{
	kthread *th1, *th2;

	kprint("shell init.\n");
	Cmd_Init();
//	Rendercore_Init();
//	Rendercore_Frame();
//	Compile_Init();

	Store_Init();

	kprint("init scheme.\n");

	Interp_Init();
//	kprint("M1\n");
	HpiComp_Init();
//	kprint("M2\n");
	HpiInterp_Init();
//	kprint("M3\n");

	Builtin_Init();
//	kprint("M4\n");

//	Storage_Init();

	th1=kthread_spawn(0, &main_loop, NULL);
	kthread_start(th1, PRIORITY_NORMAL);
//	kthread_dumpthread(th1);

	th2=kthread_spawn(0, &main_guiloop, NULL);
	kthread_start(th2, PRIORITY_NORMAL);

	kthread_set_priority(idle_thread, PRIORITY_IDLE);

	while(!idle_loop_break)sys_halt();

	kprint("KM1\n");
	Interp_DeInit();
	kprint("KM2\n");
	Store_DeInit();

//	while(1);
	reboot();
}

int main(int argc, char **argv)
{
	_argc=argc;
	_argv=argv;

	core_init();
	MMGC_Enter(&main_inner);
}

#if 0
int main_inner(int argc, char **argv)
{

	gtk_init (&argc, &argv);

	toolbar = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (toolbar), "BGBCAD Toolbar");

	gtk_signal_connect (GTK_OBJECT (toolbar), "destroy",
//		GTK_SIGNAL_FUNC (gtk_exit), NULL);
		GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	gtk_signal_connect (GTK_OBJECT (toolbar), "delete_event",
//		GTK_SIGNAL_FUNC (gtk_exit), NULL);
		GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	gtk_container_set_border_width (GTK_CONTAINER (toolbar), 0);
	gtk_widget_realize(toolbar);

	mainbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (toolbar), mainbox);
	gtk_widget_show (mainbox);

	create_menu();
	create_toolbar();

//	create_open_filebox();

	gtk_widget_show (toolbar);

	MM_Init();
	Con_Init();
	Var_Init();
	VPath_Init();
	Entity_Init();

	Render_Init();

	Scr_Init();

	lasttime=Sys_Time();
	lastcleantime=lasttime;

	gtk_timeout_add(20, (GtkFunction) main_idle_handler, NULL);

	gtk_main ();

	Con_Printf("main loop exited.\n");
//	fgetc(stdin);

	Window_DeInit();
}

int main(int argc, char **argv)
{
	gh_enter(argc, argv, main_inner);
	return(0);
}

#endif
