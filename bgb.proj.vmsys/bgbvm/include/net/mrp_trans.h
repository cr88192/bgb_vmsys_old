#ifndef __MRPTRANS_H__
#define __MRPTRANS_H__

int MRPTrans_WriteUByte(VFILE *fd, int v);
int MRPTrans_WriteSByte(VFILE *fd, int v);
int MRPTrans_WriteUShort(VFILE *fd, int v);
int MRPTrans_WriteSShort(VFILE *fd, int v);
int MRPTrans_WriteULong(VFILE *fd, int v);
int MRPTrans_WriteSLong(VFILE *fd, int v);
int MRPTrans_WriteUInt(VFILE *fd, int v);
int MRPTrans_WriteSInt(VFILE *fd, int v);
int MRPTrans_WriteFloat(VFILE *fd, float f);
int MRPTrans_WriteDouble(VFILE *fd, double f);
int MRPTrans_ReadULong(VFILE *fd);
int MRPTrans_ReadSLong(VFILE *fd);
int MRPTrans_WriteOpcode(VFILE *fd, int v);
byte *MRPTrans_WriteVLI(byte *s, int i);
int MRPTrans_WriteString(VFILE *fd, char *t);
int MRPTrans_WriteStringU2(VFILE *fd, u2 *t);
int MRPTrans_WriteData(VFILE *fd, byte *t, int len, int enc);
int MRPTrans_WriteSymbol(VFILE *fd, char *t);
int MRPTrans_WriteWidenum(VFILE *fd, u2 *t, int l);
int MRPTrans_WriteConst(VFILE *fd, int v);
int MRPTrans_WriteGuid(VFILE *fd, VGUID *guid);

#endif
