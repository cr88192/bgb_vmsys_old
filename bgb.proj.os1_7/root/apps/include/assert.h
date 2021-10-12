#ifndef __OS1_ASSERT_H__
#define __OS1_ASSERT_H__

#ifdef NDEBUG
#define assert(exp) ((void)0)
#else
#define assert(exp) (exp)?((void)0):__assert(__FILE__, __LINE__, #exp)

static inline void __assert(char *file, int line, char *exp)
{
	fprintf("Assertion failed: %s, file %s, line %d\n", exp, file, line);
	abort();
}
#endif

#endif
