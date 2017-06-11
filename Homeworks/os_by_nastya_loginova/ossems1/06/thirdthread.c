#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread1(void *dummy)


/*
 *   Parameter void *dummy is used only for type compatibility, and will not be used
 *   at the function now. At the same reason the return value of function has type 
 *   void *, but it wiil be not used at this program.
 */

{

   pthread_t mythid1;
   
   mythid1 = pthread_self();

   a = a+2;

   printf("First child thread %u, Calculation result (+2) = %d\n", mythid1, a);

   return NULL;
}

void *mythread2(void *dummy)
{

   pthread_t mythid2;

   mythid2 = pthread_self();

   a = a+10;

   printf("Second child thread %u, Calculation result(+10) = %d\n", mythid2, a);

   return NULL;

}

int main()
{
   pthread_t thid1, thid2, mythid; 
   int       result;

   result = pthread_create( &thid1, (pthread_attr_t *)NULL, mythread1, NULL);
   
   if(result != 0){
      printf ("Error on thread create, return value = %d\n", result);
      exit(-1);
   }   
   
   printf("First child thread created, thid = %u\n", thid1);




  result = pthread_create( &thid2, (pthread_attr_t *)NULL, mythread2, NULL);
   
   if(result != 0){
      printf ("Error on thread create, return value = %d\n", result);
      exit(-1);
   }   
   
   printf("Second child thread created, thid = %u\n", thid2);


   mythid = pthread_self();
   
   a = a+100;
   
   printf("Parent thread %u, Calculation result(+100) = %d\n", mythid, a);

   pthread_join(thid1, (void **)NULL);
   pthread_join(thid2, (void **)NULL);
   return 0;
}
