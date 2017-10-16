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

static int gRandom;
static int gCount[32];

int Random(void);
void Count(int random);

int main(
    int argc,
    const char * argv[])
{
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

// bit 0 toggles - not random
int Random()
{
    gRandom=gRandom*1664525+1013904223;
   
    return gRandom;
}

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
