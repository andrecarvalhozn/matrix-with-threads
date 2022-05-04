#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int var_index_global = 0;

int sum = 0;

int mat_num;

void *f(void *args) {
    int *new_matrix = (int *)args;
    pthread_mutex_lock(&mutex);
    int var_local = var_index_global * mat_num;
    int *linha = &new_matrix[var_local];

    for (int i = 0; i < mat_num; i++) {
        sum += linha[i];
    }
    var_index_global++;
    pthread_mutex_unlock(&mutex);
    return args;
}

int main() {

    scanf("%d", &mat_num);
    pthread_t th[mat_num];

    int matrix[mat_num][mat_num];

    for (int i = 0; i < mat_num; i++) {
        for (int j = 0; j < mat_num; j++) {
            scanf(" %d", &matrix[i][j]);
        }
    }
    
    for (int i = 0; i < mat_num; i++) {
        if (pthread_create(&(th[i]), NULL, f, matrix)) {
            printf("Thread creation failed\n");
        }
    }

    for (int i = 0; i < mat_num; i++) {
        pthread_join(th[i], NULL);
    }

    printf("%d\n", sum);

    return 0;
}
