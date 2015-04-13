import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Repeater {


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
            
            if (result == Integer.MAX_VALUE)
                System.out.printf("Case #%d: Fegla Won\n", ++caseIndex);
            else
                System.out.printf("Case #%d: %d\n", ++caseIndex, result);
        }
    }
}