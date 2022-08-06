#include <stdio.h>
#include<math.h>

#define M_PI 3.14159265358979323846

int main() {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        double x1, x2, y1, y2, z1, z2;
        scanf("%lf %lf %lf %lf %lf %lf", &x1, &x2, &y1, &y2, &z1, &z2);
        double AB = x1 - y1;
        double AB_2 = x2 - y2;
        double AC = x1 - z1;
        double AC_2 = x2 - z2;
        double sk = (AB * AC + AB_2 * AC_2);
        double vek = (AB * AC_2 - AC * AB_2);

        printf("%0.20g\n", fabs(atan2(vek, sk)) * 180 / M_PI);
    }

}