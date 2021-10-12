#ifndef __MUD0_H__
#define __MUD0_H__

typedef struct UserInfo_s UserInfo;
typedef struct ItemInfo_s ItemInfo;
typedef struct Item_s Item;

struct UserInfo_s {
UserInfo *next;
Meta0_Con *con;	//players
char *user;	//name
char *targ;	//target of speech

int hp, thp;
int mp, tmp;
int gold;
Item *inv, *skills;

int astr;	//attack strength
int askil;	//attack skill, success if ((rand()%apr)<askil)

int (*talk)(UserInfo *self, UserInfo *usr, char *msg);	//npcs
int (*engage)(UserInfo *self, UserInfo *usr);
int (*disengage)(UserInfo *self, UserInfo *usr);
int (*damage)(UserInfo *self, UserInfo *usr);
int (*die)(UserInfo *self, UserInfo *usr);
};

struct Item_s {
Item *next;
ItemInfo *type;
int cnt;	//inv: item count, skill: use level
};

struct ItemInfo_s {
ItemInfo *next;
char *name;
char *desc;
int cost;

//skills/spells are meta-items
int cmp;	//cost manna points
int ahr;	//attack hit rating (str*ahr)=ahp
int apr;	//attack probability
};

UserInfo *users;

#endif
