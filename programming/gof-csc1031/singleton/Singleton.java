// Singleton pattern solves the problem of ensuring there's
// only instance of a class globally.

public class Singleton {
    // attributes
    private static Singleton instance;

    // private constructor to prevent instantiation
    private Singleton() {}

    // method to provide access to the single instance
    public static Singleton getInstance() {
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }

    public void showMessage() {
        System.out.println("Hello from the Singleton!");
    }
}


