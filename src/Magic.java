import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Magic {
    static Set<Integer> readRow(Scanner sc) {
        int r = sc.nextInt();
        Set<Integer> result = new HashSet<Integer>();
        for (int i = 1; i <= 4; i++) {
            if (i == r) {
                result.add(sc.nextInt());
                result.add(sc.nextInt());
                result.add(sc.nextInt());
                result.add(sc.nextInt());
            } else {
                sc.nextInt();
                sc.nextInt();
                sc.nextInt();
                sc.nextInt();
            }
        }
        return result;
    }

    static Set<Integer> intersect(Set<Integer> set1, Set<Integer> set2) {
        Set<Integer> result = new HashSet<Integer>();
        for (Integer t : set1) {
            if (set2.contains(t)) {
                result.add(t);
            }
        }
        return result;
    }
    public static void main(String[] args) throws FileNotFoundException {
        // Scanner sc = new Scanner(System.in);
        Scanner sc = new Scanner(new File("/Users/pingany/workspace/CodeJam/test/magic.txt"));

        int caseIndex = 0;
        int nCase = sc.nextInt();
        while (nCase-- > 0) {
            Set<Integer> set1 = readRow(sc);
            Set<Integer> set2 = readRow(sc);

            Set<Integer> result = intersect(set1, set2);
            System.out.printf("Case #%d: ", ++caseIndex);
            if (result.size() == 0) {
                System.out.println("Volunteer cheated!");
            } else if (result.size() > 1) {
                System.out.println("Bad magician!");
            } else {
                System.out.println(result.toArray()[0]);
            }
        }
    }
}