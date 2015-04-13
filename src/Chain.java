import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

public class Chain {

    static PrintStream out;

    static {
        try {
            out = new PrintStream(new File("Chain.out"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    boolean isSame(String a) {
        for (int i = 1; i < a.length(); i++) {
            if (a.charAt(i) != a.charAt(0)) {
                return false;
            }
        }
        return true;
    }

    char[] prev = new char[128];
    char[]  next = new char[128];
    int[]  sames = new int[128];
    boolean[] inChain = new boolean[128];
    boolean[] disallowed = new boolean[128];
    static long result = 0;
    String removeDup(String a) {
        byte[] as = a.getBytes();
        byte prev = 0;
        int i = 0;
    }

    boolean resolve(Scanner sc) {
        Arrays.fill(prev, (char)0);
        Arrays.fill(disallowed, false);
        Arrays.fill(next, (char)0);
        Arrays.fill(sames, 0);
        Arrays.fill(inChain, false);
        int N = sc.nextInt();
        for (int i1 = 0; i1 < N; i1++) {
            String a = sc.next();
            for (int i = 0; i < a.length(); i++) {
                if (disallowed[a.charAt(i)]) {
                    return false;
                }
            }
            if (isSame(a)) {
                sames[a.charAt(0)]++;
            } else {
                a  = removeDup(a);
                char s = a.charAt(0), e =  a.charAt(a.length() -1);
                for (int i = 1; i < a.length() - 1; i++) {
                    if (allowStar a[i] == s) {
                        continue;
                    } else {}
                }

                inChain[s] = inChain[e] = true;

                if (next[s] == 0) {
                    next[s] = e;
                } else {
                    return false;
                }

                if (prev[e] == 0) {
                    prev[e] = s;
                } else {
                    return false;
                }

            }

             result = 1;
             int type = 0;
            for (int i = 'a'; i <= 'z'; i++) {
                if (sames[i] > 0) {
                    pailie(sames[i]);
                    if (!inChain[i]) {
                        type++;
                    }
                }
                if (0 !=prev[i]) {
                    int len = getLen(prev[i]);
                    mul(len);
                    type++;
                }
            }
            pailie(type);
        }
        return true;
    } 

    void mul(int n) {
        result = (result * n ) % 1000000007L;
    }

    void pailie(int n) {
        for (int i = 2; i <= n; i++) {
            mul(i);
        }
    }

    int getLen(char from) {
        int len = 0;
        while (next[from] != 0) {
            len ++;
            from = next[from];
        }
        return len;
    }


    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("Chain.in"));
        int T = sc.nextInt();
        for (int caseIndex = 1; caseIndex <= T; caseIndex++) {
            out.printf("Case #%d: ", caseIndex);
            boolean x= new Chain().resolve(sc);
            if (x) {
                System.out.println(result);
            } else {
                System.out.print(0);
            }
            // out.println();
        }
    }
}