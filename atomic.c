#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>
 // Variável atômica inteira
atomic_int acnt;
// Variável inteira comum
// função de thread
int cnt;
int f(void* thr_data)
{
	for(int n = 0; n < 1000; ++n) {
		++cnt;
		++acnt;
    }
    return 0;
}
int main(void)
{
	thrd_t thr[10]; // 10 threads
	for(int n = 0; n < 10; ++n) // criar 10 threads
	 	thrd_create(&thr[n], f, NULL);
	for(int n = 0; n < 10; ++n) // aguardar as threads
		thrd_join(thr[n], NULL);
	printf("Contador atômico: %u\n", acnt);
	printf("Contador não atômico: %u\n", cnt);
	return 0;
}

