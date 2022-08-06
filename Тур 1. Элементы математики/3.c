#include <stdio.h>
#include<math.h>
int main() {
    double eps = pow(10, -15);
    int k;
    scanf("%d", &k);


    for (int i = 0; i < k; i++) {
        double sum = 0;
        double s;
        scanf("%lf", &s);
        int n = 0;
        double now = pow(s, 2 * n + 1);

        while (fabs(now) >= eps) {

            sum += now;
            now = now * (-1) * s * s / ((2 * n + 2) * (2 * n + 3));
            n += 1;

        }
        printf("%0.15lf\n", sum);
    }
}
