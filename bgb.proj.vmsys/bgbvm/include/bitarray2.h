int BitArray2_SetBit(byte *buf, int bit);
int BitArray2_ClearBit(byte *buf, int bit);
int BitArray2_GetBit(byte *buf, int bit);
int BitArray2_FindRun(byte *buf, int sz, int *span);
int BitArray2_FindShortestRun(byte *buf, int sz, int *span);
int BitArray2_SetRun(byte *buf, int *span);
int BitArray2_ClearRun(byte *buf, int *span);
int BitArray2_Used(byte *buf, int sz);
int BitArray2_AllocBit(byte *buf, int sz);
int BitArray2_AllocClosestBit(byte *buf, int sz, int bit);