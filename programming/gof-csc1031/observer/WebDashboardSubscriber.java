public class WebDashboardSubscriber implements Subscriber {
    @Override
    public void update(String news) {
        System.out.println("Web dashboard updated: " + news);
    }
}