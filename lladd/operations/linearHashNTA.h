#ifndef __LINEAR_HASH_NTA_H
#define __LINEAR_HASH_NTA_H

typedef struct {
  long current_hashBucket;
  recordid current_recordid;
} lladd_hash_iterator;

/** Implementaiton of a linear hash table that makes use of nested top actions. */

recordid ThashCreate(int xid, int keySize, int valSize);
void ThashDelete(int xid, recordid hash);
/* @return 1 if the key was defined, 0 otherwise. */
int ThashInsert(int xid, recordid hash, const byte* key, int keySize, const byte* value, int valueSize);
/* @return 1 if the key was defined, 0 otherwise. */
int ThashRemove(int xid, recordid hash, const byte* key, int keySize);

/** @return size of the value associated with key, or -1 if key not found. 
                   (a return value of zero means the key is associated with an
		   empty value.) */
int ThashLookup(int xid, recordid hash, const byte* key, int keySize, byte ** value);
lladd_hash_iterator * ThashIterator(int xid, recordid hash);
int ThashIteratorNext(int xid, recordid hash, lladd_hash_iterator * it, byte ** key, byte** value);
void ThashIteratorFree(int xid, lladd_hash_iterator * it);

//Support 16 entries by default.
#define HASH_INIT_BITS 4
#define HASH_FILL_FACTOR 0.7

#endif // __LINEAR_HASH_NTA_H
