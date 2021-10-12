#include <scmcc.h>

typedef struct {
elem key;
elem value;
}Dict_Leaf;

typedef struct {
elem left;
int left_height;

elem divider; //not actually marked

elem right;
int right_height;
}Dict_Node;

typedef struct {
elem root;
}Dict_Top;

int Dict_EqualP(elem a, elem b)
{
	return(TyFcn_EqualP(a, b)==MISC_TRUE);
}

int Dict_LessP(elem a, elem b)
{
	if((ELEM_FIXNUMP(a) || ELEM_FLONUMP(a)) &&
		(ELEM_FIXNUMP(b) || ELEM_FLONUMP(b)))
		return(TOFLOAT(a)<TOFLOAT(b));
	if(ELEM_SYMBOLP(a) && ELEM_SYMBOLP(b))
		return(strcmp(ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b))<0);
	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))
		return(strcmp(ELEM_TOSTRING(a), ELEM_TOSTRING(b))<0);
	return(a<b);
}

int Dict_GreaterP(elem a, elem b)
{
	if((ELEM_FIXNUMP(a) || ELEM_FLONUMP(a)) &&
		(ELEM_FIXNUMP(b) || ELEM_FLONUMP(b)))
		return(TOFLOAT(a)>TOFLOAT(b));
	if(ELEM_SYMBOLP(a) && ELEM_SYMBOLP(b))
		return(strcmp(ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b))>0);
	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))
		return(strcmp(ELEM_TOSTRING(a), ELEM_TOSTRING(b))>0);
	return(a>b);
}

int Dict_LessEqualP(elem a, elem b)
{
	if((ELEM_FIXNUMP(a) || ELEM_FLONUMP(a)) &&
		(ELEM_FIXNUMP(b) || ELEM_FLONUMP(b)))
		return(TOFLOAT(a)<=TOFLOAT(b));
	if(ELEM_SYMBOLP(a) && ELEM_SYMBOLP(b))
		return(strcmp(ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b))<=0);
	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))
		return(strcmp(ELEM_TOSTRING(a), ELEM_TOSTRING(b))<=0);
	return(a<=b);
}

int Dict_GreaterEqualP(elem a, elem b)
{
	if((ELEM_FIXNUMP(a) || ELEM_FLONUMP(a)) &&
		(ELEM_FIXNUMP(b) || ELEM_FLONUMP(b)))
		return(TOFLOAT(a)>=TOFLOAT(b));
	if(ELEM_SYMBOLP(a) && ELEM_SYMBOLP(b))
		return(strcmp(ELEM_TOSYMBOL(a), ELEM_TOSYMBOL(b))>=0);
	if(ELEM_STRINGP(a) && ELEM_STRINGP(b))
		return(strcmp(ELEM_TOSTRING(a), ELEM_TOSTRING(b))>=0);
	return(a>=b);
}

int Dict_TreeHeight(elem t)
{
	Dict_Node *tmp;

	if(!TypeX_TypeP(t, "dict-node"))return(1);

	tmp=TypeX_Data(t);
	if(tmp->left_height==-1)
		tmp->left_height=Dict_TreeHeight(tmp->left);
	if(tmp->right_height==-1)
		tmp->right_height=Dict_TreeHeight(tmp->right);

	if(tmp->left_height>tmp->right_height)
		return(tmp->left_height);
		else return(tmp->right_height);
}

elem Dict_TreeMin(elem t)
{
	Dict_Node *n;
	Dict_Leaf *l;

	if(TypeX_TypeP(t, "dict-node"))
	{
		n=TypeX_Data(t);
		return(Dict_TreeMin(n->left));
	}

	if(TypeX_TypeP(t, "dict-leaf"))
	{
		l=TypeX_Data(t);
		return(l->key);
	}

	return(MISC_UNDEFINED);
}

elem Dict_TreeMax(elem t)
{
	Dict_Node *n;
	Dict_Leaf *l;

	if(TypeX_TypeP(t, "dict-node"))
	{
		n=TypeX_Data(t);
		return(Dict_TreeMax(n->right));
	}

	if(TypeX_TypeP(t, "dict-leaf"))
	{
		l=TypeX_Data(t);
		return(l->key);
	}

	return(MISC_UNDEFINED);
}

elem Dict_MakeNode(elem left, elem right)
{
	Dict_Node *tmp;

	tmp=TypeX_Alloc("dict-node", sizeof(Dict_Node));
	tmp->left=left;
	tmp->left_height=Dict_TreeHeight(tmp->left);

	tmp->right=right;
	tmp->right_height=Dict_TreeHeight(tmp->right);

	tmp->divider=Dict_TreeMax(tmp->left);

	return(MMGC3_GetReference(tmp));
}

elem Dict_MakeLeaf(elem key, elem value)
{
	Dict_Leaf *l;

	l=TypeX_Alloc("dict-leaf", sizeof(Dict_Leaf));
	l->key=key;
	l->value=value;

	return(MMGC3_GetReference(l));
}

elem Dict_Lookup(elem pt, elem key)
{
	Dict_Node *n;
	Dict_Leaf *l;
	Dict_Top *h;

	if(TypeX_TypeP(pt, "dict-node"))
	{
		n=TypeX_Data(pt);
//		if(key<=n->divider)
		if(Dict_LessEqualP(key, n->divider))
			return(Dict_Lookup(n->left, key));
		return(Dict_Lookup(n->right, key));
	}

	if(TypeX_TypeP(pt, "dict-leaf"))
	{
		l=TypeX_Data(pt);
//		if(l->key!=key)
		if(!Dict_EqualP(key, l->key))
			return(MISC_UNDEFINED);
		return(l->value);
	}

	if(TypeX_TypeP(pt, "dict-top"))
	{
		h=TypeX_Data(pt);
		return(Dict_Lookup(h->root, key));
	}

	return(MISC_UNDEFINED);
}

elem Dict_Assign(elem pt, elem key, elem value)
{
	Dict_Node *n, *n2;
	Dict_Leaf *l;
	Dict_Top *h;
	elem t;

	if(TypeX_TypeP(pt, "dict-node"))
	{
		n=TypeX_Data(pt);
//		if(key<=n->divider)
		if(Dict_LessEqualP(key, n->divider))
		{
			n->left=Dict_Assign(n->left, key, value);
			n->left_height=Dict_TreeHeight(n->left);
			n->divider=Dict_TreeMax(n->left);
		}else
		{
			n->right=Dict_Assign(n->right, key, value);
			n->right_height=Dict_TreeHeight(n->right);
		}
		//balance
		if(n->left_height>(n->right_height+1))
		{
			n2=TypeX_Data(n->left);
			n->left=n2->left;
			n->right=Dict_MakeNode(n2->right, n->right);

			n->left_height=Dict_TreeHeight(n->left);
			n->divider=Dict_TreeMax(n->left);
			n->right_height=Dict_TreeHeight(n->right);
		}
		if((n->left_height+1)<n->right_height)
		{
			n2=TypeX_Data(n->right);
			n->left=Dict_MakeNode(n->left, n2->left);
			n->right=n2->right;

			n->left_height=Dict_TreeHeight(n->left);
			n->divider=Dict_TreeMax(n->left);
			n->right_height=Dict_TreeHeight(n->right);
		}
		return(pt);
	}

	if(TypeX_TypeP(pt, "dict-leaf"))
	{
		l=TypeX_Data(pt);
//		if(l->key!=key)
		if(!Dict_EqualP(key, l->key))
		{
//			if(key<l->key)
			if(Dict_LessP(key, l->key))
			{
				t=Dict_MakeNode(
					Dict_MakeLeaf(key, value), pt);
				return(t);
			}else
			{
				t=Dict_MakeNode(pt,
					Dict_MakeLeaf(key, value));
				return(t);
			}
		}
		l->value=value;
		return(pt);
	}

	if(TypeX_TypeP(pt, "dict-top"))
	{
		h=TypeX_Data(pt);
		h->root=Dict_Assign(h->root, key, value);
		return(pt);
	}

	t=Dict_MakeLeaf(key, value);
	return(t);
}

elem Dict_ApplyTop(elem obj, elem rest)
{
	elem t;
	if(rest==MISC_EOL)return(obj);

//	if(ELEM_STRINGP(CAR(rest)))
//		rest=CONS(TyFcn_HashString(CAR(rest)), CDR(rest));

	if(CDR(rest)==MISC_EOL)
	{
		t=Dict_Lookup(obj, CAR(rest));
		if(t==MISC_UNDEFINED)t=MISC_NULL;
		return(t);
	}

	Dict_Assign(obj, CAR(rest), CADR(rest));
	return(MISC_NULL);
}

elem Dict_MarkTop(elem obj)
{
	Dict_Top *h;

	h=TypeX_Data(obj);
	h->root=MMGC3_TracePush(h->root);

	return(MISC_NULL);
}

elem Dict_MarkLeaf(elem obj)
{
	Dict_Leaf *l;

	l=TypeX_Data(obj);
	l->key=MMGC3_TracePush(l->key);
	l->value=MMGC3_TracePush(l->value);

	return(MISC_NULL);
}

elem Dict_MarkNode(elem obj)
{
	Dict_Node *n;

	n=TypeX_Data(obj);
	n->left=MMGC3_TracePush(n->left);
	n->right=MMGC3_TracePush(n->right);

	return(MISC_NULL);
}


elem Dict_New()
{
	Dict_Top *h;

	h=TypeX_Alloc("dict-top", sizeof(Dict_Top));
	h->root=MISC_NULL;

	return(MMGC3_GetReference(h));
}

int Dict_Init()
{
	typexinfo *txi;

	txi=TypeX_GetInfo("dict-top");
	txi->apply=&Dict_ApplyTop;
//	txi->swizin=&Dict_SwizinTop;
//	txi->swizout=&Dict_SwizoutTop;
	txi->mark=&Dict_MarkTop;

	txi=TypeX_GetInfo("dict-node");
//	txi->apply=&Dict_ApplyLeaf;
//	txi->swizin=&Dict_SwizinLeaf;
//	txi->swizout=&Dict_SwizoutLeaf;
	txi->mark=&Dict_MarkNode;

	txi=TypeX_GetInfo("dict-leaf");
//	txi->apply=&Dict_ApplyLeaf;
//	txi->swizin=&Dict_SwizinLeaf;
//	txi->swizout=&Dict_SwizoutLeaf;
	txi->mark=&Dict_MarkLeaf;

	Interp_DefinePrimative("dict-new", &Dict_New, 0);

	return(0);
}
