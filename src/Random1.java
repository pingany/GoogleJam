import java.util.Random;

public class Random1 {
    public static void main(String[] args) {
        int n = 100;
        while (n-- > 0) {
            r2(100 - 7, 7);
            System.out.println("");
        }
    }

    static void r2(int x, int n) {
        int left = r(x, n);
        if (left != 0)
            r2(left, n - 1);
    }

    static int r(int x, int n) {
        if (n == 1) {
            System.out.print(" " + (x + 1));
            return 0;
        }
        // int []s1= new int[]{0, 2, 6, 8, 11, 14, 15, 14, 12, 9, 7, 2};
        // // int s[] = new int[s1.length]{0, 2,8,16,27,41,56,70,82,91,98,100};
        // int s[] = new int[s1.length/2];
        // int j = 0;
        // for (int i = 0; i < s1.length/2; i++) {
        // s[j] = (s1[i]+s1[s1.length-i-1]);
        // System.out.println(s[j]);
        // ++j;
        // }
        // return 0 ;
        int s[] = new int[] {
         5398, 5793, 6169, 6554, 6915, 7257, 7580, 7881, 8159, 8413,
         8643, 8849, 9032, 9192, 9332, 9452, 9554, 9641, 9713, 9772,
         9821, 9861, 9893, 9918, 9938, 9953, 9965, 9974, 9981, 10000 };
        double min = (x + 0.0) / n;
        double step = (x - min) / (s.length+10);
        double step2 = (min) / (s.length+10);

        int a = new Random().nextInt() % 5000;
        for (int i = 0; i < s.length; i++) {
            if (s[i] - 5000 >= Math.abs(a)) {
                int get = 0;
                if (a >= 0)
                    get = (int) (step * i + min);
                else
                    get = (int) (min - step2 * i);
                System.out.print(" " + (get + 1));
                return x - get;
            }
        }
        return 0;
    }
}
