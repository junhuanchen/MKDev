#ifndef POOL_STATIC_H
#define POOL_STATIC_H

#include "CH552.H"

typedef void *BlockStatic;

typedef struct pool_static
{
	UINT32 Usage, Len;
	UINT8 *Area;
}PoolStatic;

void PoolStaticInit( PoolStatic *Pool, UINT8 *Area, UINT32 Len )
{
	if ( Pool != NULL && Area != NULL && Len > 0 )
	{
		// memset(Area, 0, Len);// ³õÊ¼»¯
		Pool->Area = Area;
		Pool->Len = Len, Pool->Usage = 0;
	}
}

void PoolStaticCopy( PoolStatic * Target, PoolStatic * Source )
{
	if ( Target->Len >= Source->Len )
	{
		memcpy( Target->Area, Source->Area, Source->Len );
		Target->Usage = Source->Usage;
	}
}

BlockStatic PoolStaticNew( PoolStatic *Pool, UINT32 Size )
{
	BlockStatic Type = NULL;
	if ( Size && Pool->Usage + Size <= Pool->Len )
	{
		Type = Pool->Area + Pool->Usage;
		Pool->Usage += Size;
	}
	return Type;
}

__inline void PoolStaticDel( BlockStatic Data )
{
	// Do Not Need;
}

#ifdef UNIT_TEST

#include <stdio.h>
static void PoolStaticDump(PoolStatic *Self)
{
	printf("ScPool Dump: ");
	for (UINT32 i = 0; i < Self->Len; i++)
	{
		printf("%X ", Self->Area[i]);
	}
	putchar('\n');
}

static void UnitTestPoolStatic()
{
	UINT8 MemArea[32];
	PoolStatic Pool;
	PoolScInit(&Pool, MemArea, sizeof(MemArea));
	int * i = (int *)PoolStaticNew(&Pool, 4);
	*i = 0x12345678;
	int * j = (int *)PoolStaticNew(&Pool, 4);
	*j = 0x87654321;
	int * k = (int *)PoolStaticNew(&Pool, 4);
	*k = 0x90909090;
	printf("%f\n", (float)(Pool.Len - Pool.Usage) / Pool.Len * 100);
	PoolStaticDump(&Pool);
}
#endif

#endif // POOL_STATIC_H
