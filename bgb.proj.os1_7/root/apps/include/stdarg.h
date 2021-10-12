#ifndef __OS1_STDARG_H__
#define __OS1_STDARG_H__

#if 1
typedef long va_list;

#define va_start(lst, rt)	__va_start(&lst, &rt)
#define va_end(lst)		__va_end(lst)

#define va_arg(lst, ty)		((ty)__va_arg(&lst))

#else
#define va_list			void **
#define va_start(lst, s)	lst=(void **)&s
#define va_end(s)
#define va_arg(lst, t)		(*(t *)((lst)++))
#endif

#endif
