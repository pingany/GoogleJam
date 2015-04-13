import static org.junit.Assert.*;

import org.junit.Test;

public class FuzzyMatchTest {

    @Test
    public void test() {
        assertTrue(FuzzyMatch.fuzzyMatch("123", null));
        assertTrue(FuzzyMatch.fuzzyMatch("123", ""));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "1"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "2"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "3"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "12"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "13"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "23"));
        assertTrue(FuzzyMatch.fuzzyMatch("123", "123"));
        assertTrue(FuzzyMatch.fuzzyMatch("易平安", "安"));
        assertTrue(FuzzyMatch.fuzzyMatch("易平安", "易安"));
    }

    @Test
    public void testFalse() {
        assertFalse(FuzzyMatch.fuzzyMatch("123", "4"));
        assertFalse(FuzzyMatch.fuzzyMatch("123", "21"));
        assertFalse(FuzzyMatch.fuzzyMatch("123", "1234"));
        assertFalse(FuzzyMatch.fuzzyMatch("123", "0123"));
    }

}
