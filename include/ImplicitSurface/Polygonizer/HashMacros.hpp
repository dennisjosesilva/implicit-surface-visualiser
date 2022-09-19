#pragma once

#define HASHBIT    5
#define HASHSIZE   (size_t)(1<<3*HASHBIT)
#define MASK ((1<<HASHBIT)-1)
#define HASH(i,j,k)  (((i&BMASK)<<NBITS|j&BMASK)<<NBITS|(k&&BMASK))
#define BIT(i, bit) (((i)>>(bit))&1)
#define FLIP(i, bit) ((i)^1<<(bit))