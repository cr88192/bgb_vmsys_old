#include <general.h>
#include <guile/gh.h>

SCM scr_prints(SCM s_str)
{
	char *s;
	if(SCM_IMP(s_str))return(SCM_BOOL_F);
	if(!SCM_STRINGP(s_str))return(SCM_BOOL_F);
	s=SCM_CHARS(s_str);
	Con_Printf(s);
	return(SCM_BOOL_T);
}

SCM scr_concmd(SCM s_str)
{
	char *s;
	if(SCM_IMP(s_str))return(SCM_BOOL_F);
	if(!SCM_STRINGP(s_str))return(SCM_BOOL_F);
	s=SCM_CHARS(s_str);
	Con_SubmitCommand(s);
	return(SCM_BOOL_T);
}

int Scr_Command(char *s)
{
	gh_eval_str(s);
}

int Scr_Init()
{
	gh_new_procedure("prints",			scr_prints,		1, 0, 0);
	gh_new_procedure("con-command",		scr_concmd,		1, 0, 0);

	gh_eval_file("bgbcad0.scm");
}
