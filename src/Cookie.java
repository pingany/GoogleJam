import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Cookie {

    static double C, F, X, minValue = Double.MAX_VALUE;

    static double f(double s, double z) {
        for (;;) {
            minValue = Math.min(minValue,
                    Math.min(s + (X - C) / z, s + X / (z + F)));

            double t = s + C / (z + F);
            if (t < minValue) {
                // minValue = Math.min(minValue, f(t, z + F));
                s = t;
                z = z + F;
            } else {
                break;
            }
        }
        return minValue;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc;
        if (args != null && args.length > 0 && args[0].equals("-d")) {
            sc = new Scanner(new File(args[1]));
        } else {
            sc = new Scanner(System.in);
        }

        int caseIndex = 0;
        int nCase = sc.nextInt();
        while (nCase-- > 0) {
            C = sc.nextDouble();
            F = sc.nextDouble();
            X = sc.nextDouble();
            minValue = X / 2;
            System.out.printf("Case #%d: %.8f\n", ++caseIndex,
                    (X <= C ? minValue : f(C / 2, 2)));
        }
    }
}