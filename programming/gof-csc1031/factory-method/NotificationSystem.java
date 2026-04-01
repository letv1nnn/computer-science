import java.util.Map;
import java.util.HashMap;

public class NotificationSystem {
    public static void main(String[] args) {
        NotificationFactory factory = new NotificationFactory();
        
        Notification email = factory.createNotification(NotificationFactory.NotificationType.EMAIL);
        Notification sms = factory.createNotification(NotificationFactory.NotificationType.SMS);
        Notification push = factory.createNotification(NotificationFactory.NotificationType.PUSH);
    
        factory.registerNotification(email, "Hello ...\n\nKind regards,\n...");
        factory.registerNotification(sms, "where are you??");
        factory.registerNotification(push, "ultra vital\n...");
    
        Map<Notification, String> notificationsCopy = factory.getNotifications();
        
        for (Map.Entry<Notification, String> entry : notificationsCopy.entrySet()) {
            entry.getKey().send(entry.getValue());
        }
    }
}

class NotificationFactory {

    public enum NotificationType {
        EMAIL,
        PUSH,
        SMS
    }

    private Map<Notification, String> notifications = new HashMap<>();

    public Notification createNotification(NotificationType type) {
        return switch (type) {
            case EMAIL -> new EmailNotification();
            case PUSH -> new PushNotification();
            case SMS -> new SMSNotification();
        };
    }

    public void registerNotification(Notification notification, String message) {
        if (notification != null) {
            notifications.put(notification, message);
        }
    }

    public Map<Notification, String> getNotifications() {
        return new HashMap<>(notifications);
    }
}

interface Notification {
    void send(String message);
}

class EmailNotification implements Notification {
    @Override
    public void send(String message) {
        System.out.println("[EMAIL]: " + message);
    }
}

class SMSNotification implements Notification {
    @Override
    public void send(String message) {
        System.out.println("[SMS]: " + message);
    }
}

class PushNotification implements Notification {
    @Override
    public void send(String message) {
        System.out.println("[PUSH]: " + message);
    }
}
