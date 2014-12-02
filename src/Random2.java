import java.util.Random;

public class Random2 {
    public static void main(String[] args) {
        int n = 100;
        while (n-- > 0) {
            generateRandomsAtLeastOne(100, 7);
            System.out.println("");
        }
    }

    static void generateRandomsAtLeastOne(int x, int n) {
        while (n > 0) {
            int res = generateRandomAtLeastOne(x, n);
            System.out.print(" " + res);
            x -= res;
            n--;
        }
    }

    static int generateRandomAtLeastOne(int total, int n) {
        return generateRandom(total - n, n) + 1;
    }

    static int generateRandom(int total, int n) {
        if (total == 0) {
            return 0;
        }
        if (n == 1) {
            return total;
        }
        double randomData = new Random().nextGaussian();

        double avg = ((double) total) / n;
        double unit;
        if (randomData > 0) {
            unit = (total - avg) / (n - 1);
        } else {
            unit = (avg - 0) / 3;
        }
        int res = (int) (avg + randomData * unit);
        res = Math.max(0, Math.min(res, total));
        return res;
    }
}
