import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class War {

    static int N;
    static String[] naomi = new String[1000];
    static String[] ken = new String[1000];

    static int good() {
        // Arrays.sort(ken, 0, N, new Comparator<String>() {
        // @Override
        // public int compare(String a, String b) {
        // return -a.compareTo(b);
        // }
        // });
        // System.out.println("data1");
        // for (int i = 0; i < N; i++) {
        // System.out.println(naomi[i] + " " + ken[i]);
        // }
        int j = 0;
        int score = 0;
        for (int i = 0; i < N; i++) {

            for (; j < N; j++) {
                if (naomi[j].compareTo(ken[i]) > 0) {
                    score++;
                    j++;
                    break;
                }
            }
        }

        return score;
    }

    static int bad() {
        int j = 0;
        for (int i = 0; i < N; i++) {

            boolean found = false;
            for (; j < N; j++) {
                if (naomi[i].compareTo(ken[j]) < 0) {
                    j++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return N - i;
            }
        }
        return 0;
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
            N = sc.nextInt();
            for (int i = 0; i < N; i++) {
                naomi[i] = sc.next();
            }

            for (int i = 0; i < N; i++) {
                ken[i] = sc.next();
            }

            Arrays.sort(naomi, 0, N);
            Arrays.sort(ken, 0, N);
            System.out.printf("Case #%d: %d %d\n", ++caseIndex, good(), bad());
        }
    }
}