#ifndef MT_H

#define MT_H

#define N 624
#define M 397


#include <stdio.h>

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s);

void init_genrand_return(unsigned long s, int*mti_l, unsigned long mt_l[N]);

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length);

void init_by_array_return(unsigned long init_key[], int key_length, int * mti_l, unsigned long mt_l[N]);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32_seed(int *mti_l ,unsigned long mt_l[N]);

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void);

/* generates a random number on [0,1]-real-interval */
double genrand_real1_seed(int *mti_l ,unsigned long mt_l[N]);

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void);


/* generates a random number on [0,1)-real-interval */
double genrand_real2(void);

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void);

#endif /* MT_H */