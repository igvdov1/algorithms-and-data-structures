#include <stdio.h>
#include <malloc.h>

int find_min(int **mas, int k, int n, int *list) {
    int min = 1111;
    int pos = -1;
    for (int i = 2; i < n + 2; i++) {
        if (mas[k][i] != 0 && mas[k][i] != 1111 && mas[k][i] < min && list[i - 2] != 1) {
            min = mas[k][i];
            pos = i;
        }
    }
    list[pos - 2] = 1;
    return pos;
}

int func_1(int **mas, int k, int n) {

}

int main() {
    FILE *IN;
    IN = freopen("input.txt", "r", stdin);
    int n, goal[2], **adj_list, c1, c2, c3, **dijk;
    fscanf(IN, "%d %d %d", &n, &goal[0], &goal[1]);
    dijk = (int **) malloc(sizeof(int *) * n);
    adj_list = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        adj_list[i] = (int *) malloc(sizeof(int) * n);
        dijk[i] = (int *) calloc(sizeof(int), (n + 2));
        for (int j = 0; j < n; j++) {
            adj_list[i][j] = 1111;
        }
    }
    for (int i = 0; i < n; i++) {
        adj_list[i][i] = 0;
    }
    while (fscanf(IN, "%d %d %d", &c1, &c2, &c3) != EOF) {
        adj_list[c1 - 1][c2 - 1] = c3;
        adj_list[c2 - 1][c1 - 1] = c3;
    }
    dijk[0][0] = goal[0];
    for (int i = 0; i < n; i++) {
        dijk[0][i + 2] = adj_list[goal[0] - 1][i];
    }
    int y = 1;
    int *list = (int *) calloc(sizeof(int), n);
    while (y < n) {

        int b = find_min(dijk, y - 1, n, list) - 2;

        if (b >= 0) {
            dijk[y][0] = b + 1;
            dijk[y][1] = dijk[y - 1][b + 2];
            for (int i = 2; i < n + 2; i++) {
                if (adj_list[b][i - 2] + dijk[y][1] < dijk[y - 1][i]) {
                    dijk[y][i] = adj_list[b][i - 2] + dijk[y][1];
                } else {
                    dijk[y][i] = dijk[y - 1][i];
                }

            }
        } else if (dijk[y - 1][goal[1] + 1] != 0 && dijk[y - 1][goal[1] + 1] != 1111) {
            printf("%d", dijk[y - 1][goal[1] + 1]);
            return 0;
        } else {
            printf("no");
            return 0;
        }
//        if (y == 1 || y == 2){
//            for(int i = 0; i < n; i++){
//                printf("%d ", list[i]);
//            }
//            printf("\n");
//        }
        y++;

    }

    printf("%d\n", dijk[n - 1][goal[1] + 1]);
//    for(int i = 0; i < n; i++){
//        for(int j = 0; j < n + 2; j++){
//            printf("%d ", dijk[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//    for(int i = 0; i < n; i++){
//        for(int j = 0; j<n; j++){
//            printf("%d ", adj_list[i][j]);
//        }
//        printf("\n");
//    }
}