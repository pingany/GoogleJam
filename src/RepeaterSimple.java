import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class RepeaterSimple {
    static int result;
    static int N;
    static String[] ss = new String[100];

    static class E {
        char c;
        int n;
    }
    static class R {
        E[] e = new E[100];
        int n;
        int index = -1;

        void repeat() {
            e[index].n++;
        }

        void newChar(char c) {
            index++;
            e[index] = new E();
            e[index].c = c;
        }

        void end() {
            n = index + 1;

            // System.out.println("Hello");
            // for (int i = 0; i < n; i++) {
            //     System.out.println(e[i].c  +" " + e[i].n);
            // }
        }

        boolean ok(R r) {
            if (n != r.n) {
                return false;
            }
            for (int i =0 ; i< n; i++) {
                if (e[i].c != r.e[i].c) {
                    return false;
                }
            }
            return true;
        }
    }

    static R[] rs = new R[100];

    static void getR() {
        for (int i =0 ;i < N;i++) {
            rs[i] = getR(ss[i]);
        }
    }

    static R getR(String s) {
        R r = new R();

        char prev = 0;
        for (int i =0 , size = s.length(); i<size; i++) {
            if (s.charAt(i) == prev) {
                r.repeat();
            } else {
                prev = s.charAt(i);
                r.newChar(prev);
            }
        }
        r.end();
        return r;
    }

    static int compare2R(R r1, R r2) {
        if (!r1.ok(r2)) {
            return Integer.MAX_VALUE;
        }
        int x = 0;
        for (int i =0; i < r1.n; i++) {
            x += Math.abs(r1.e[i].n - r2.e[i].n);
        }
        return x;
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
            N  = sc.nextInt();
            Arrays.fill(ss, null);
            Arrays.fill(rs, null);
            for (int i =0 ; i < N; i++) {
                ss[i] = sc.next();
            }
            getR();
            result = compare2R(rs[0], rs[1]);
            if (result == Integer.MAX_VALUE)
                System.out.printf("Case #%d: Fegla Won\n", ++caseIndex);
            else
                System.out.printf("Case #%d: %d\n", ++caseIndex, result);
        }
    }
}