import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;

public class ELF {

    static PrintStream out;

    static {
        try {
            out = new PrintStream(new File("ELF.out"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    double log2(double d) {
        return Math.log(d) / Math.log(2);
    }

//     void resolve2(Scanner sc) {
//         String line[] = sc.next().split("/");
//         double P, Q;

//         P = (double)Long.parseLong(line[0]);
//         Q = (double)Long.parseLong(line[1]);

//         // double a = log2(Q/P), b = log2(2*Q/P);
//         // out.println(a + " " + b) ;
//         // int result = (int)Math.ceil(a);

//         double a = log2(Q);
//         int result = (int)Math.round(a);
//         if (result > 40 || (result - a) > 0.01) {
//             out.println("impossible");
//         }
//         else {
//             // assert false;
//             assert (((long)Q)& ((long)Q-1)) == 0;
// //            assert result < b;
//             out.println(result);
//         }


    long gcd(long a, long b) {
        if (a < b) {
            long t = a;
            a = b;
            b = t;
        }
        if (b == 0) {
            return a;
        }
        else {
            return gcd(a%b, b);
        }
    }


    void resolve(Scanner sc) {
        assert gcd(6, 8) == 2;
        assert gcd(6, 12) == 6;
        String line[] = sc.next().split("/");
        long P, Q;

        P = (long)Long.parseLong(line[0]);
        Q = (long)Long.parseLong(line[1]);

        long x= gcd(P, Q);
        P /= x;
        Q /=x;
        double a = log2(Q);
        int result = (int)Math.round(a);
        if (result > 40 || Math.abs(result - a) > 0.0001) {
            out.println("impossible");
        }
        else {
            assert ((long)Math.pow(2, result) == Q);
             assert ((Q)& (Q-1)) == 0;

             double b = log2(P);
             result -= (int) Math.floor(b);
            out.println(result);
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("ELF.in"));
        int T = sc.nextInt();
        for (int caseIndex = 1; caseIndex <= T; caseIndex++) {
            out.printf("Case #%d: ", caseIndex);
            new ELF().resolve(sc);
            // out.println();
        }
    }
}