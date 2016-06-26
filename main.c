#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
#define SHMEM_SIZE 1048576
  key_t key = ftok("/tmp/mem.temp", 1);
  int shmid = shmget(key, SHMEM_SIZE, (IPC_CREAT | 0666));
  if(shmid == -1)
  {
    perror("Ошибка создания общей памяти: ");
    return -1;
  }

  char *shmem_ptr = shmat(shmid, NULL, 0);
  if(shmem_ptr == (char *) -1)
  {
    perror("Ошибка присоединения к общей памяти: ");
    return -1;
  }

  for(int i = 0; i < SHMEM_SIZE; i=i+1024)
  {
    shmem_ptr[i] = 42;
  }

  return 0;
}
