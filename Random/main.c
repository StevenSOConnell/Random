//
//  main.c
//  Random
//
//  Created by Steve O'Connell on 9/12/17.
//  Copyright © 2017 Steve O'Connell. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//#include <Accelerate/Accelerate.h>
//#include <x86intrin.h>      // all
//#include <xmmintrin.h>      // SSE
#include <immintrin.h>      // all
//#include <avxintrin.h>      // AVX
//#include <avx2intrin.h>     // AVX-2
//#include <avx512fintrin.h>  // AVX-512

#ifdef __SSE__
#pragma message "sse"
#endif
#ifdef __AVX__
#pragma message "avx"
#endif
#ifdef __AVX2__
#pragma message "avx2"
#endif
#ifdef __AVX512F__
#pragma message "avx512f"	// forced compiler flags: -mavx512f (but crashes assert?!), not part of Xcode yet
#endif

#include <sys/sysctl.h>

static int gRandom;
static int gCount[32];

int Random(void);
void Count(int random);

/**
 main entry function
 @discussion	this is a multiple-line discussion that can last many lines
 				and much longer
 @param			[in] argc integer number of arguments
 @param			[in] argv const char * argument array
 @return		integer error code
 */
int main(
    int argc,
    const char * argv[])
{
	size_t length=0;
	int result=sysctlbyname("hw.optional.sse",NULL,&length,NULL,0);
	assert(length==sizeof(int));
	int sse=0;
	result=sysctlbyname("hw.optional.sse",&sse,&length,NULL,0);
	printf("sse=%d\n",sse);
	
	result=sysctlbyname("hw.optional.avx1_0",NULL,&length,NULL,0);
	assert(length==sizeof(int));
	int avx1=0;
	result=sysctlbyname("hw.optional.avx1_0",&avx1,&length,NULL,0);
	printf("avx1=%d\n",avx1);

	result=sysctlbyname("hw.optional.avx2_0",NULL,&length,NULL,0);
	assert(length==sizeof(int));
	int avx2=0;
	result=sysctlbyname("hw.optional.avx2_0",&avx2,&length,NULL,0);
	printf("avx2=%d\n",avx2);

	result=sysctlbyname("hw.optional.avx512f",NULL,&length,NULL,0);
	assert(length==sizeof(int));
	int avx512=0;
	result=sysctlbyname("hw.optional.avx512f",&avx512,&length,NULL,0);
	printf("avx512f=%d\n",avx512);

	gRandom=(int)random();
    
    int i;
    
    for(i=0;i<65536;i++) {
        int r=Random();
        printf("%12x ",r);
        if((i%8)==7) printf("\n");
        
        Count(r);
    }
    
    for(i=0;i<32;i++) {
        printf("bit %d: %d\n",i,gCount[i]);
    }
    
    return 0;
}

/**
 Generate random number

 @return int
 */
int Random()
{
    gRandom=gRandom*1664525+1013904223;
   
    return gRandom;
}

/**
 Count the number of bits set

 @param random int
 */
void Count(
    int random)
{
    assert(sizeof(int)*8 == sizeof(gCount)/sizeof(int));

    int i;
    
    for(i=0;i<32;i++) {
        if(random&(1<<i))
            gCount[i]++;
    }
}
