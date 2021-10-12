#ifdef SAFLAG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef FILE VFILE;

#else
#include <general.h>

#endif

#ifndef __SCMCC_H__
#define __SCMCC_H__

//typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned long elem;
#define ELEM_SZ	(sizeof(long))

#define TYPE_FIXNUM		0
//#define TYPE_LOCATIVE	1
//#define TYPE_LOCATIVE2	5
//1 free
#define TYPE_MISC		2	//3 bits type, next 5 bits-extended type, upper 24 bits-data
#define TYPE_OBJECT		3	//pointer to an object, objhead low 9 bits type
//4 free
//5 free
#define TYPE_OBJECTHEAD	6	//object head and longref are seperated by context
#define TYPE_LONGREF	6	//instead of using this to refer to "longref" objects, the longrefs can be hidden away.
#define TYPE_CONS		7

#define TYPE_SPECIAL	8

#define MISCT_VALUES	0	//misc type: misc values
#define MISCT_CHAR		((1<<3)|TYPE_MISC)
// #define MISCT_FRAMEREF	((2<<3)|TYPE_MISC)	//upper 24 bits index in frame, 12:12<->up:right
// #define MISCT_DISPREF	((3<<3)|TYPE_MISC)	//upper 24 bits index in frame, 12:12<->up:right
#define MISCT_OPCODE	((2<<3)|TYPE_MISC)		//middle 8 bits data, upper 16 bits opcode

#define MISC_FALSE		((1<<8)|TYPE_MISC)
#define MISC_TRUE		((2<<8)|TYPE_MISC)
#define MISC_NULL		((3<<8)|TYPE_MISC)
#define MISC_EOL		((4<<8)|TYPE_MISC)
#define MISC_UNDEFINED	((5<<8)|TYPE_MISC)	//used for internal error reporting
#define MISC_EOF		((6<<8)|TYPE_MISC)

#define MISC_MARK		((7<<8)|TYPE_MISC)	//stack mark
#define MISC_ADJ		((8<<8)|TYPE_MISC)	//adj value

#define OBJECT_VECTOR	((1<<3)|TYPE_OBJECTHEAD)
#define OBJECT_STRING	((2<<3)|TYPE_OBJECTHEAD)
#define OBJECT_SYMBOL	((3<<3)|TYPE_OBJECTHEAD)
#define OBJECT_BIGNUM	((4<<3)|TYPE_OBJECTHEAD)
#define OBJECT_STRUCT	((5<<3)|TYPE_OBJECTHEAD)

#define OBJECT_SLCLASS	((6<<3)|TYPE_OBJECTHEAD)
#define OBJECT_SLOBJ	((7<<3)|TYPE_OBJECTHEAD)
#define OBJECT_BOX		((8<<3)|TYPE_OBJECTHEAD)

#define OBJECT_FUNCTION	((16<<3)|TYPE_OBJECTHEAD)
#define OBJECT_TYPEX	((17<<3)|TYPE_OBJECTHEAD)	//object head, elem type, data...
#define OBJECT_SYNTAX	((18<<3)|TYPE_OBJECTHEAD)
#define OBJECT_LOCATIVE	((19<<3)|TYPE_OBJECTHEAD)

#define OBJECT_CDATA	((20<<3)|TYPE_OBJECTHEAD)	//c side structure, conservative gc

#define VECTOR_VARIABLE	0
#define VECTOR_ELEMENT	1
#define VECTOR_F32		2
#define VECTOR_F64		3
#define VECTOR_U8		4
#define VECTOR_U16		5
#define VECTOR_U32		6
#define VECTOR_U64		7
#define VECTOR_S8		8
#define VECTOR_S16		9
#define VECTOR_S32		10
#define VECTOR_S64		11

#define VECTOR_CLOSURE	32 //env_n env_d ip
#define VECTOR_MACRO	33 //similar to closure, but a macro (unused)
#define VECTOR_ENV		34 //environment, env_n env_d, may be modified or whatever
#define VECTOR_ENVOBJ	35 //object
#define VECTOR_CONTEXT	36 //interpreter context/thread
#define VECTOR_MINIFRAG	37 //minicode fragment, env_n env_d ip

#define VECTOR_SYNSYN	46
#define VECTOR_SYNREF	47

#define OBJECT_HEAD(c)		(*(elem *)((c)&(~7)))
#define OBJECT_TYPE(c)		(OBJECT_HEAD(c)&255)

#define ELEM_TYPE2(c) ((c)&3)
#define ELEM_TYPE3(c) ((c)&7)

#define ELEM_FROMCONS(c)	((elem)(c)|TYPE_CONS)
//#define ELEM_FROMXCONS(c)	((elem)(c)|TYPE_XCONS)
#define ELEM_FROMFIXNUM(c)	(((elem)(c)<<3)|TYPE_FIXNUM)
#define ELEM_FROMOBJECT(c)	((elem)(c)|TYPE_OBJECT)

//#define ELEM_FROMLOCATIVE(c)	((elem)(c)|TYPE_LOCATIVE)

#define ELEM_FROMCHAR(c)	(((elem)(c)<<8)|MISCT_CHAR)
#define ELEM_FROMFRAME(a,b)	(((elem)(((a)<<20)+((b)<<8)))|MISCT_FRAMEREF)
#define ELEM_FROMDISP(c)	(((elem)(c)<<8)|MISCT_DISPREF)

//#define ELEM_FROMSTRING(c)	((elem)(c)|TYPE_STRING)
//#define ELEM_FROMSYMBOL(c)	((elem)(c)|TYPE_SYMBOL)

#define ELEM_OBJIFY(c)			(((c)&(~7))|TYPE_OBJECT)
//#define ELEM_FROMSTRING(c)		ELEM_OBJIFY(TyFcn_Cons(OBJECT_STRING|(strlen(c)<<16), (elem)(c)))
#define ELEM_FROMSTRING(a)		(TyFcn_String(a))

//#define ELEM_FROMSYMBOL(c)		ELEM_OBJIFY(TyFcn_Cons(OBJECT_SYMBOL|(strlen(c)<<16), (elem)(c)))
//#define ELEM_FROMSYMBOL2(c)		ELEM_OBJIFY(TyFcn_Cons(OBJECT_SYMBOL|(strlen(c)<<16)|256, (elem)(c)))
#define ELEM_FROMSYMBOL(a)		(TyFcn_Symbol2(a, 0))
#define ELEM_FROMSYMBOL2(a)		(TyFcn_Symbol2(a, 1))

#define ELEM_TOCONS(c)		((elem *)((c)&(~7)))
#define ELEM_TOOBJECT(c)	((void *)((c)&(~7)))
//#define ELEM_TOLOCATIVE(c)	((elem *)((c)&(~3)))

#define ELEM_TOCHAR(c)		((int)(c)>>8)
#define ELEM_TOFIXNUM(c)	(ELEM_TOFIXNUMi(c))

//#define ELEM_TOSTRING(c)	((char *)((c)&(~7)))
//#define ELEM_TOSYMBOL(c)	((char *)((c)&(~7)))
//#define ELEM_TOSTRING(c)	((char *)TyFcn_Cdr(c))
//#define ELEM_TOSYMBOL(c)	((char *)TyFcn_Cdr(c))
#define ELEM_TOSYMBOL(c)	(TyFcn_UnString(c))
#define ELEM_TOSTRING(c)	(TyFcn_UnString(c))
#define ELEM_TOSTRING16(c)	(TyFcn_UnString16(c))

#define ELEM_DUMMY(c)		(((c)<<3)|TYPE_ONJECTHEAD)

#define ELEM_CONSP(c)		(ELEM_TYPE3(c)==TYPE_CONS)
#define ELEM_FIXNUMP(c)		(ELEM_TYPE2(c)==TYPE_FIXNUM)
#define ELEM_OBJECTP(c)		(ELEM_TYPE3(c)==TYPE_OBJECT)
//#define ELEM_LOCATIVEP(c)	(ELEM_TYPE2(c)==TYPE_LOCATIVE)
#define ELEM_LONGREFP(c)	(ELEM_TYPE3(c)==TYPE_LONGREF)

//#define ELEM_STRINGP(c)		(ELEM_TYPE(c)==TYPE_STRING)
//#define ELEM_SYMBOLP(c)		(ELEM_TYPE(c)==TYPE_SYMBOL)

#define ELEM_VECTORP(c)		(ELEM_OBJTYPEPi(c, OBJECT_VECTOR))
#define ELEM_FUNCTIONP(c)	(ELEM_OBJTYPEPi(c, OBJECT_FUNCTION))
#define ELEM_BOXP(c)		(ELEM_OBJTYPEPi(c, OBJECT_BOX))
#define ELEM_SLOBJP(c)		(ELEM_OBJTYPEPi(c, OBJECT_SLOBJ))
#define ELEM_SYNTAXP(c)		(ELEM_OBJTYPEPi(c, OBJECT_SYNTAX))
#define ELEM_STRINGP(c)		(ELEM_OBJTYPEPi(c, OBJECT_STRING))
#define ELEM_SYMBOLP(c)		(ELEM_OBJTYPEPi(c, OBJECT_SYMBOL))

#define ELEM_BIGNUMP(c)		(ELEM_OBJTYPEPi(c, OBJECT_BIGNUM))
#define ELEM_TYPEXP(c)		(ELEM_OBJTYPEPi(c, OBJECT_TYPEX))

//#define ELEM_CLOSUREP(c)	(ELEM_OBJTYPEPi(c, OBJECT_CLOSURE))
#define ELEM_CLOSUREP(c)	(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_CLOSURE))==MISC_TRUE)
#define ELEM_MACROP(c)		(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_MACRO))==MISC_TRUE)
#define ELEM_ENVP(c)		(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_ENV))==MISC_TRUE)
#define ELEM_ENVOBJP(c)		(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_ENVOBJ))==MISC_TRUE)
#define ELEM_CONTEXTP(c)	(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_CONTEXT))==MISC_TRUE)
#define ELEM_MINIFRAGP(c)	(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_MINIFRAG))==MISC_TRUE)

#define ELEM_SYNREFP(c)		(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_SYNREF))==MISC_TRUE)
#define ELEM_SYNSYNP(c)		(TyFcn_VectorIs(c, ELEM_FROMFIXNUM(VECTOR_SYNSYN))==MISC_TRUE)

#define ELEM_FLONUMP(c)		(TyFcn_BignumIs(c, ELEM_FROMFIXNUM(VECTOR_F64))==MISC_TRUE)
#define ELEM_FROMFLONUM(c)	(TyMath_FromDouble(c))
#define ELEM_TOFLONUM(c)	(TyMath_ToDouble(c))

#define OBJ_PEEK(x, y)		(ELEM_TOCONS(x)[y])
#define OBJ_POKE(x, y, z)	(ELEM_TOCONS(x)[y]=z)
//#define ELEM_SETLOCATIVE(a, b)	(*(elem *)((a)&(~3))=(b))


#define	ELEM_SYMKEYWORDP(c)	(ELEM_SYMBOLP(c) && OBJ_PEEK(c, 0)&(1<<31))
#define	ELEM_SYMHYGENICP(c)	(ELEM_SYMBOLP(c) && OBJ_PEEK(c, 0)&(1<<30))
#define	ELEM_SYMNORMALP(c)	(ELEM_SYMBOLP(c) && !(OBJ_PEEK(c, 0)&(1<<31)) && !(OBJ_PEEK(c, 0)&(1<<30)))
//#define	ELEM_SYMKEYWORDP(c)	(0)

#define ELEM_CHARP(c)		(((c)&255)==MISCT_CHAR)
#define ELEM_FRAMEP(c)		(((c)&255)==MISCT_FRAMEREF)
#define ELEM_OPCODEP(c)		(((c)&255)==MISCT_OPCODE)

#define ELEM_FROMBOOL(c)	((!(c))?MISC_FALSE:MISC_TRUE)
#define ELEM_TOBOOL(c)		(((c)==MISC_FALSE)?0:-1)

#define SCMCC_ASSERT(p, q)	if(!(p))sa_error(q)
#define SCMCC_ASSERT2(p, q)	if(!(p))q

#define ELEM_EOLP(c)		((c)==MISC_EOL)
#define ELEM_NULLP(c)		((c)==MISC_NULL)
#define ELEM_UNDEFP(c)		((c)==MISC_UNDEFINED)

#define SYM(a)			(TyFcn_Symbol(a))
#define STRING(a)		(TyFcn_String(a))
#define SYMC(a)			(SYMCi(a))
#define SYMG(a, b)		(SYMGi(&(a), b))

#define FIXNUM(a)		ELEM_FROMFIXNUM(a)
#define TOINT(a)		ELEM_TOFIXNUM(a)
#define FLONUM(a)		ELEM_FROMFLONUM(a)
#define TOFLOAT(a)		ELEM_TOFLONUM(a)

#define CONS(a, b)			(TyFcn_Cons(a, b))
//#define XCONS(a, b)			(TyFcn_XCons(a, b))

//#define CAR(c)				(TyFcn_Car(c))
//#define CDR(c)				(TyFcn_Cdr(c))

#define CARF(c)				(((elem *)((c)&(~7)))[0])
#define CDRF(c)				(((elem *)((c)&(~7)))[1])
#define CAR(c)				(ELEM_CONSP(c)?CARF(c):sa_fatal("CAR: type check.\n"))
#define CDR(c)				(ELEM_CONSP(c)?CDRF(c):sa_fatal("CDR: type check.\n"))

#define CAAR(c)				(CAR(CAR(c)))
#define CAAAR(c)			(CAR(CAAR(c)))
#define CAAAAR(c)			(CAR(CAAAR(c)))

#define CADR(c)				(CAR(CDR(c)))
#define CDDR(c)				(CDR(CDR(c)))
#define CADDR(c)			(CAR(CDDR(c)))
#define CDDDR(c)			(CDR(CDDR(c)))
#define CADDDR(c)			(CAR(CDDDR(c)))
#define CDDDDR(c)			(CDR(CDDDR(c)))

#define UCDR(c)				(TyFcn_UnCons(c))

#define LENGTH(c)			(TOINT(TyFcn_ListLength(c)))

#define	VECTOR_REF(a, b)	(TyFcn_VectorRef(a, ELEM_FROMFIXNUM(b)))
#define	VECTOR_SET(a, b, c)	(TyFcn_VectorSet(a, ELEM_FROMFIXNUM(b), c))

#define VECTOR_NEW(a)		(TyFcn_NewVector(FIXNUM(a)))
#define VECTOR_LEN(a)		(ELEM_TOFIXNUM(TyFcn_VectorLength(a)))

#define ELEM_LOCATIVEP(c)		(ELEM_OBJTYPEPi(c, OBJECT_LOCATIVE))
#define ELEM_FROMLOCATIVE(c)	(TyFcn_NewLocative(c))
#define ELEM_TOLOCATIVE(c)		(TyFcn_GetLocativeAddr(c))
#define ELEM_SETLOCATIVE(a, b)	(TyFcn_GetLocativeAddr(a)[0]=(b))

static inline int ELEM_TOFIXNUMi(elem c)
{
	unsigned int t;
	t=(c>>3);
	if(t&0x10000000)(unsigned int)t|=0xE0000000; /* FIXME: assumes int 32bit */
	return(t);
}

static inline int ELEM_OBJTYPEPi(elem c, int type)
{
	elem *t;
	if(!ELEM_OBJECTP(c))return(0);
	t=ELEM_TOOBJECT(c);
	if((t[0]&255)!=type)return(0);
	return(1);
}

elem TyFcn_Symbol(char *s);

static inline elem SYMCi(char *s)
{
	static elem t=MISC_NULL;

	if(t==MISC_NULL)t=SYM(s);
	return(t);
}

static inline elem SYMGi(elem *var, char *s)
{
	if(*var==MISC_NULL)*var=SYM(s);
	return(*var);
}


typedef struct typexinfo_s {
struct typexinfo_s *next, *prev;
char *name;
elem (*apply)(elem obj, elem rest);
elem (*mark)(elem obj);
elem (*swizin)(elem obj);
elem (*swizout)(elem obj);
}typexinfo;


void *sa_alloc(int size);
int sa_error(char *s, ...);
int sa_print(char *s, ...);
void *sa_ralloc(int size);
void *sa_malloc(int size);
int sa_free(void *buf);

elem TyFcn_Cons(elem a, elem b);
//elem TyFcn_XCons(elem a, elem b);
elem TyFcn_String(char *s);
elem TyFcn_MakeString(elem k, elem c);
char *TyFcn_UnString(elem a);
short *TyFcn_UnString16(elem a);

elem TyFcn_Car(elem c);
elem TyFcn_Cdr(elem c);
elem TyFcn_CarM(elem c);
elem TyFcn_CdrM(elem c);
elem TyFcn_SetCar(elem c, elem a);
elem TyFcn_SetCdr(elem c, elem a);
elem TyFcn_NReverse(elem lst);
elem TyFcn_Reverse(elem lst);
elem TyFcn_ListCopy(elem a);
elem TyFcn_ListCopyRec(elem a);
elem TyFcn_NAppend(elem lst, elem a);
elem TyFcn_ListLength(elem lst);
elem TyFcn_ListGetEnd(elem lst);
elem TyFcn_ListRef(elem lst, elem idx);

elem TyFcn_NewLocative(elem *addr);
elem *TyFcn_GetLocativeAddr(elem loc);
elem TyFcn_SetLocativeAddr(elem loc, elem *addr);
elem TyFcn_LocativeNew(elem lower, elem upper, elem ty);
elem TyFcn_LocativeCopy(elem a);


elem TyFcn_ListToVector(elem lst);
elem TyFcn_CopyVector(elem a);
elem TyFcn_ResizeVector(elem a, elem nl);
elem TyFcn_NewVector(elem a);
elem TyFcn_VectorLength(elem a);
elem TyFcn_NewTypedVector(elem a, elem ty);
elem TyFcn_VectorIs(elem a, elem ty);
elem TyFcn_VectorRef(elem a, elem b);
elem TyFcn_VectorSet(elem a, elem b, elem c);
elem TyFcn_VectorRefM(elem a, elem b);
double TyFcn_VectorRefF(elem a, int b);

elem TyFcn_ObjectInListP(elem obj, elem lst);
elem TyFcn_ObjPeekElem(elem obj, elem num);
elem TyFcn_ObjPokeElem(elem obj, elem num, elem val);

elem TyFcn_Function(elem (*func)(), int pc);
elem TyFcn_Special(elem (*func)(), int pc);

elem TyFcn_StringE(elem a, elem b);
elem TyFcn_StringEP(elem a, elem b);
elem TyFcn_StringCiEP(elem a, elem b);

elem TyFcn_KeywordBase(elem sym);

elem TyFcn_MatchP(elem lit, elem a, elem b);
elem TyFcn_Match2P(elem lit, elem a, elem b);
elem TyFcn_MatchV(elem a, elem b);

int TyFcn_DumpElem(elem obj);
int TyFcn_DumpList(elem lst);
int TyFcn_DisplayElem(elem obj);

elem ScmParse_List(char **s, int ind);
elem ScmParse_Item(char **s, int ind);
elem ScmParse_Line(char **s, int sk);
elem ScmParseSK_Item(char **s, int ind);
elem ScmParseSK_Line(char **s);
char *ScmParseSK_EatWhite(char *s);
char *ScmParse_EatWhite(char *s);

int Interp_Init();
int Interp_Define(elem def, elem data);
int Interp_DefinePrimative(char *name, elem (*func)(), int pc);
int Interp_DefineSpecial(char *name, elem (*func)(), int pc);
elem Interp_Load(elem name);

elem Interp_EvalExpr(elem form);
//elem Interp_Eval(elem form);
elem Interp_Eval(elem form, elem env_n, elem env_d, elem dyn_n, elem dyn_d);
elem Interp_EvalTop(elem form);
elem Interp_EvalLast(elem form);

elem Interp_EvalString(char *s, elem binds);
elem Interp_EvalStringTop(char *s);

elem Interp_Thread(elem func);
int Interp_RunQuantum(int ms);
elem Interp_BlockThread(elem thread);
elem Interp_UnblockThread(elem thread);
elem Interp_RecieveThread();
elem Interp_SleepThread(elem s);

elem Namespace2_Define(elem *ntree, elem *dtree, elem sym, elem val);
elem Namespace2_Lookup(elem ntree, elem dtree, elem sym);
elem Namespace2_Assign(elem ntree, elem dtree, elem sym, elem value);
elem Namespace2_Trace(elem ntree, elem dtree, elem last, elem sym);
elem Namespace2_RetrieveTrace(elem ntree, elem dtree, elem last);
elem Namespace2_AssignTrace(elem ntree, elem dtree, elem last, elem value);
elem Namespace2_LocativeTrace(elem ntree, elem dtree, elem last);

double TyMath_ToDouble(elem a);
elem TyMath_FromDouble(double a);
elem TyMath_ToFlonum(elem a);


#endif
