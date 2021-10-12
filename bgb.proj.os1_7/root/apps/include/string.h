#ifndef __OS1_STRING_H__
#define __OS1_STRING_H__

int strlen(const char *s);
int strcpy(char *s1,const char *s2);
int strncpy(char *s1, const char *s2, int n);
int strcmp(const char *s1, const char *s2);
int stricmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int n);
int memcpy(void *dest, const void *src, int len);
char *memset(void *s, int c, int n);
char *strcat(char *s, char *s2);
int isalpha(char c);
int isdigit(char c);
int isalnum(char c);
int tolower(char c);
int atoi(char *s);
char *strdup(const char *s);
const char *strchr(const char *s, int c);

#endif
