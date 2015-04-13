import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ABK {

    static int A,B, K;
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
            A = sc.nextInt();
            B = sc.nextInt();
            K = sc.nextInt();
            int result = 0;
            for (int i = 0; i <A; i++) 
                for (int j = 0; j < B;j++) {
                    if ((i & j) < K) {
                        result++;
                    }
                }
            if (result == Integer.MAX_VALUE)
                System.out.printf("Case #%d: Fegla Won\n", ++caseIndex);
            else
                System.out.printf("Case #%d: %d\n", ++caseIndex, result);
        }
    }
}