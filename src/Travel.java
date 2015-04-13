import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Travel {

    static int M, N;
    static int order = 0;
    static String results;

    static String MAXS ="Z";
    static ArrayList<String> result = new ArrayList<String>();

    static class City {
        String zip;
        ArrayList<Integer> e = new ArrayList<Integer>();
        int order;
    }
    static City cs[] = new City[50];

    static boolean canAccess(int f, int t) {
        if (cs[t].order == 0 || cs[f].order == cs[t].order +1) {
            return true;
        }
        return false;
    }


    static String min(String x, String y) {
        return x.compareTo(y) < 0 ? x : y;
    }

    static String tos(List<String> ss) {
        StringBuilder sb = new StringBuilder();
        for (String s : ss) {
            sb.append(s);
        }
        return sb.toString();
    }

    static String go(int start) {
        boolean revert = false;
        if (cs[start].order == 0) {
            cs[start].order = ++order;
            result.add(cs[start].zip);
            revert = true;
        }
        if (start == startPoint && result.size() == N) {
            return tos(result); 
        }
        String x = MAXS;
        for (int b : cs[start].e) {
            if (canAccess(start, b)) {
                x = min(x, go(b));
            }
        }
        if (revert) {
            --order;
            result.remove(result.size() -1) ;
            cs[start].order = 0;
        }
        return x;
    }

    static int startPoint = 0;
    static void solve() {
        results = MAXS;
        for (int i =0 ; i < N;i++) {
            order = 0;
            startPoint = i;
            result.clear();
            results = min(results, go(i));
        }
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
            
            Arrays.fill(cs, null);
            N = sc.nextInt();
            M = sc.nextInt();

            for (int i = 0; i < N; i++) {
                cs[i] = new City();
                cs[i].zip = sc.next();
            }

            for (int i =0 ;i < M; i++) {
                int a = sc.nextInt()-1, b = sc.nextInt()-1;
                cs[a].e.add(b);
                cs[b].e.add(a);
            }

            solve();
                System.out.printf("Case #%d: %s\n", ++caseIndex, results);
        }
    }
}