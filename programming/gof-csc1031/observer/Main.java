// Observer is a behavioral design pattern that lets you define a subscription
// mechanism to notify multiple objects about any events that happen to the object
// they’re observing.

public class Main {
    public static void main(String[] args) {
        NewsAgency agency = new NewsAgency();

        Subscriber emailSub = new EmailSubscriber("alice@example.com");
        Subscriber mobileSub = new MobileAppSubscriber("bob123");
        Subscriber webSub = new WebDashboardSubscriber();

        // Subscribers join
        agency.subscribe(emailSub);
        agency.subscribe(mobileSub);
        agency.subscribe(webSub);

        // News updates
        agency.addNews("Stock market hits record high!");
        agency.addNews("New Java version released!");
        agency.addNews("SpaceX launches new rocket!");

        // Unsubscribe a subscriber
        agency.unsubscribe(mobileSub);
        agency.addNews("Weather alert: Heavy rain tomorrow!");
    }
}
