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
        double now = 1;

        if (s >= -1) {
            while (fabs(now) >= eps) {

                sum += now;

                n += 1;
                now *= s / n;
            }
            printf("%0.15g\n", sum);
        } else {
            s *= -1;
            while (fabs(now) >= eps) {

                sum += now;

                n += 1;
                now *= s / n;
            }
            printf("%0.15g\n", 1 / sum);
        }

    }

}
