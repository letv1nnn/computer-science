public class GameConfig {
    private static GameConfig config;
    private String difficulty;
    private int volume;

    private GameConfig() {
        // default settings
        this.difficulty = "Normal";
        this.volume = 50;
    }

    public static GameConfig getInstance() {
        if (config == null) {
            config = new GameConfig();
        }
        return config;
    }

    public void setDifficulty(String difficulty) {
        this.difficulty = difficulty;
    }
    public void setVolume(int volume) {
        if (volume <= 100 && volume >= 0)
            this.volume = volume;
    }
    public String getDifficulty() {
        return new String(this.difficulty);
    }
    public int getVolume() {
        return this.volume;
    }
}