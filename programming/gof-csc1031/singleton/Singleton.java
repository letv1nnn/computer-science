//           *** Description ***
// Singleton is a creational design pattern
// that solves the problem of ensuring there's
// only instance of a class globally.

public class Singleton {
    public static void main(String[] args) {
        Singleton s1 = Singleton.getInstance();
        Singleton s2 = Singleton.getInstance();
        assert s1 == s2: "Singleton instance are not the same";
    }

    // attributes
    private static Singleton instance;
    // constructor
    private Singleton() {}
    // method to provide access to the single instance
    public static Singleton getInstance() {
        if (instance == null)
            instance = new Singleton();
        return instance;
    }
}
