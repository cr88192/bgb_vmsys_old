/*
parse trees for sx and xml, intended to allow faster parsers for such data
than vm based parsers.
 */

#ifndef __NET_PARSE_H__
#define __NET_PARSE_H__

typedef struct NetParse_Attr_s NetParse_Attr;
typedef struct NetParse_Node_s NetParse_Node;

struct NetParse_Attr_s {
NetParse_Attr *next;
char *key;
char *value;
};

struct NetParse_Node_s {
NetParse_Node *next;
char *key;
char *text;
NetParse_Attr *attr;
NetParse_Node *first;
};

NetParse_Node *NetParse_NewNode();
NetParse_Node *NetParse_AddNodeEnd(NetParse_Node *first, NetParse_Node *node);
int NetParse_FreeAttr(NetParse_Attr *attr);
int NetParse_FreeNode(NetParse_Node *node);
NetParse_Node *NetParse_FindKey(NetParse_Node *first, char *key);

NetParse_Node *NetParse_SX_ParseExpr(char **s);
char *NetParse_SX_PrintExpr(char *s, NetParse_Node *exp);

NetParse_Node *NetParse_XML_ParseExpr(char **s);
char *NetParse_XML_PrintExpr(char *s, NetParse_Node *exp);

#endif
