
public class FuzzyMatch {

    public static boolean fuzzyMatch(String text, String search) {
        if (search == null || search.length() == 0)
            return true;
        int pos = 0;
        for (int i = 0; i < search.length(); i++) {
            char c = search.charAt(i);
            pos = text.indexOf(c, pos);
            if (pos < 0) {
                return false;
            }
            pos += 1;
        }
        return true;
    }
    
}
