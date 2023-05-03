#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>
#define N 2
#define TRUE 1
#define FALSE 0
// Variáveis atômicas do algoritmo
atomic_int turn;
atomic_int interested[N];
// Variável contadora normal
int counter = 0;
void enter_region(int p) {
	int other;
	other = 1 - p;
	interested[p] = TRUE;
	turn = p;
	while(turn==p && interested[other] == TRUE);
}

void leave_region(int p) {
	interested[p] = FALSE;
}

int thread_function(void* thread_data)
{
	int *p = (int *)thread_data;
	for(int n = 0; n < 10000; ++n) {
		// pré-protocolo
		enter_region(*p);
		// seção crítica
		int temp = counter;
		temp = temp + 1;
		counter = temp;
		// pós-protocolo
		leave_region(*p);
	}
	return 0;
}

int main(void)
{
    thrd_t thread0, thread1;
    int t0 = 0, t1 = 1;
    thrd_create(&thread0, thread_function, &t0);
	thrd_create(&thread1, thread_function, &t1);
    // aguardar as threads
    thrd_join(thread0, NULL);
    thrd_join(thread1, NULL);
    printf("Valor do contador: %u\n", counter);
}
