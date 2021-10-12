#ifndef __INTERPCTX_H__
#define __INTERPCTX_H__

#define HPIOP_APPLY		1
#define HPIOP_ARGUMENT		2
#define HPIOP_ASSIGN		3
#define HPIOP_BIND		4
#define HPIOP_BINDARGS		5
#define HPIOP_BINDVAR		6
#define HPIOP_BINDARGSVAR	7
#define HPIOP_BLOCK		8
#define HPIOP_CLOSE		9
#define HPIOP_CONSTANT		10
#define HPIOP_CONTI		11
#define HPIOP_CURRENTENV	12
#define HPIOP_FRAME		13
#define HPIOP_FUNC		14
#define HPIOP_HALT		15
#define HPIOP_INTSOFF		16
#define HPIOP_INTSON		17
#define HPIOP_NUATE		18
#define HPIOP_REFER		19
#define HPIOP_REFERSYNTAX	20
#define HPIOP_RETURN		21
#define HPIOP_SETRAX		22
#define HPIOP_SPLICE		23
#define HPIOP_TEST		24
#define HPIOP_XCHGRPAX		25
#define HPIOP_DUMPOPS		26
#define HPIOP_CONSTRAINT	27
#define HPIOP_ASSIGN2		28

typedef struct {
elem _head;
elem ax;	/* holds return value and misc data */
elem ax1;
elem ax2;
elem ax3;
elem ax4;
elem ax5;
elem ax6;
elem rax;	/* value return, used to pass locatives corresponding to the source of the value in ax */

elem ip;
elem sp;
elem rp;

elem ep_n, ep_d;
elem dyn_n, dyn_d;
elem sep_n, sep_d; /* syntactic environment, loaded into ep_* during macro expansion */
elem vax;	/* used for communication within the interpreter */
elem flags;	/* more communication, treated as int */
elem lrp;
}InterpCtx;

#define CTX_CONTI	8 //call/cc return
#define CTX_CLOSE	16 //closure, current-env

elem HpiInterp_RunLoop(InterpCtx *ctx);
InterpCtx *interp_context;
extern elem form_return, form_apply, form_halt, form_frame_apply_halt;

InterpCtx *HpiInterp_RunCtxSafe(elem form, InterpCtx *ctx);

#endif
