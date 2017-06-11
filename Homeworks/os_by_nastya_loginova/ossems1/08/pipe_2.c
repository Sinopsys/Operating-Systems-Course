/
// ST1: LOCK L1; read; UNLOCK L2
// ST2: LOCK L2; write; UNLOCK L3 (initial state)
//
// ST3: LOCK L3; read; UNLOCK L4
// ST4: LOCK L4; write; UNLOCK L1
//
 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <semaphore.h>
 
int main(void)
{
        void *map = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        struct locks {
                             sem_t l1;
                             sem_t l2;
                             sem_t l3;
                             sem_t l4;
                     } *locks = (struct locks *)map;
        int pipes[2];
        int rc, ft = 1;
        char c;
 
        assert(map != MAP_FAILED);
        rc = pipe(pipes);
        assert(rc != -1);
 
        sem_init(&locks->l1, 1, 0);
        sem_init(&locks->l2, 1, 1);
        sem_init(&locks->l3, 1, 0);
        sem_init(&locks->l4, 1, 0);
 
        rc = fork();
        assert(rc != -1);
 
if (rc) {
        while (1) {
            c = '0';
            rc = write(pipes[1], &c, 1);
            assert(rc == 1);
            sem_post(&locks->l3);
 
            sem_wait(&locks->l1);
            rc = read(pipes[0], &c, 1);
            assert(rc == 1);
            assert(c == '1');
        }
    } else {
        while (1) {
            sem_wait(&locks->l3);
            rc = read(pipes[0], &c, 1);
            assert(rc == 1);
            assert(c == '0');
 
            c = '1';
            rc = write(pipes[1], &c, 1);
            assert(rc == 1);
            sem_post(&locks->l1);
        }
    }
       return 0;
}

