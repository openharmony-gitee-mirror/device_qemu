/*
 * Copyright (c) 2021-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _Key_CACHE_H
#define _Key_CACHE_H

#include "los_compiler.h"
#include "los_list.h"
#include "fb_mem.h"

#define FNV1_32A_INIT ((UINT32)0x811c9dc5)
/*
 * 32 bit magic FNV-1 prime
 */
#define FNV_32_PRIME ((UINT32)0x01000193)

LITE_OS_SEC_ALW_INLINE STATIC INLINE UINT32 LOS_HashFNV32aBuf(const VOID *buf, size_t len, UINT32 hval)
{
    const UINT8 *hashbuf = (const UINT8 *)buf;

    /*
     * FNV-1a hash each octet in the buffer
     */
    while (len-- != 0) {
        /* xor the bottom with the current octet */
        hval ^= (UINT32)*hashbuf++;

        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        hval *= FNV_32_PRIME;
    }

    /* return our new hash value */
    return hval;
}

LITE_OS_SEC_ALW_INLINE STATIC INLINE UINT32 LOS_HashFNV32aStr(CHAR *str, UINT32 hval)
{
    UINT8 *s = (UINT8 *)str;

    /*
     * FNV-1a hash each octet in the buffer
     */
    while (*s) {
        /* xor the bottom with the current octet */
        hval ^= (UINT32)*s++;

        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        hval *= FNV_32_PRIME;
    }

    /* return our new hash value */
    return hval;
}

typedef LOS_DL_LIST LIST_HEAD;
typedef LOS_DL_LIST LIST_ENTRY;
#define LOSCFG_MAX_PATH_CACHE_SIZE 512

struct KeyCache {
    struct fb_mem *fbmem;          /* vnode points to the cache */
    LIST_ENTRY hashEntry;         /* list entry for buckets in the hash table */
    uint8_t nameLen;              /* length of Key component */
#ifdef LOSCFG_DEBUG_VERSION
    int hit;                      /* cache hit count */
#endif
    char name[0];                 /* Key component name */
};

int KeyCacheInit(void);
int KeyCacheFree(struct KeyCache *cache);
struct KeyCache *KeyCacheAlloc(struct fb_mem *fbmem, const char *name, uint8_t len);
int KeyCacheLookup(const char *name, int len, struct fb_mem **fbmem);
void FbMemKeyCacheFree(struct fb_mem *fbmem);
void KeyCacheMemoryDump(void);
void KeyCacheDump(void);
LIST_HEAD* GetKeyCacheList(void);
#ifdef LOSCFG_DEBUG_VERSION
void ResetKeyCacheHitInfo(int *hit, int *try);
#endif

#endif /* _Key_CACHE_H */
