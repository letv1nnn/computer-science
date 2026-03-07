public class MobileAppSubscriber implements Subscriber {
    private String username;

    public MobileAppSubscriber(String username) {
        this.username = username;
    }

    public String getUsername() {
        return new String(username);
    }

    @Override
    public void update(String news) {
        System.out.println("Mobile app notification to " + username + ": " + news);
    }
}