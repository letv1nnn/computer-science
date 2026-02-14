public class Main {
    public static void main(String[] args) {
        System.out.println("Default Singleton Example:");
        Singleton s1 = Singleton.getInstance();
        Singleton s2 = Singleton.getInstance();
        System.out.println(s1 == s2);

        System.out.println("Leveraging Singleton for GameConfig:");
        GameConfig config = GameConfig.getInstance();
        System.out.println("Difficulty: " + config.getDifficulty());
        System.out.println("Volume: " + config.getVolume());

        config.setDifficulty("Hard");
        config.setVolume(75);

        GameConfig config2 = GameConfig.getInstance(); // Same Instance
        System.out.println("Difficulty: " + config.getDifficulty());
        System.out.println("Volume: " + config.getVolume());
    }
}