// Publisher (NewsAgency)
import java.util.ArrayList;
import java.util.List;

public class NewsAgency {
    private List<Subscriber> subscribers = new ArrayList<>();
    private String latestNews;

    public void subscribe(Subscriber s) {
        subscribers.add(s);
    }
    public void unsubscribe(Subscriber s) {
        subscribers.remove(s);
    }
    public void notifySubscribers() {
        for (Subscriber s : subscribers) {
            s.update(latestNews);
        }
    }
    public void addNews(String news) {
        System.out.println("\nNewsAgency: Breaking news - " + news);
        this.latestNews = news;
        notifySubscribers();
    }
}
