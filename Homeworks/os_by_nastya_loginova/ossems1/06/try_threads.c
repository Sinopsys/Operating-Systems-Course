# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

int a;

a=0;
void * thread1 ()
{
a=a+1;
printf ("Hi from first thread (+1): %d\n", a);
}
void * thread2 ()
{
a=a+2;
printf ("Hi from second thread (+2): %d\n", a);

}

void * thread3 ()
{
a=a+6;
printf ("Hi from third thread (+6): %d\n", a);

}



int main()
{
int status;
pthread_t tid1, tid2, tid3;

pthread_create(&tid1, NULL, thread1, NULL);
pthread_create(&tid2, NULL, thread2, NULL);
pthread_create(&tid3, NULL, thread3, NULL);
pthread_join (tid1, NULL);
pthread_join (tid2, NULL);
pthread_join (tid3, NULL);
return 0;
}
