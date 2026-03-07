public class EmailSubscriber implements Subscriber {
    private String email;

    public EmailSubscriber(String email) {
        this.email = email;
    }

    public String getEmail() {
        return new String(email);
    }

    @Override
    public void update(String news) {
        System.out.println("Email to " + email + ": " + news);
    }
}