//                *** Description ***
// Mediator is a behavioral design pattern that lets
// you reduce dependencies between objects.
// The pattern restricts  direct communications between
// the objects and forces them to collaborate only via a
// mediator object.
// 
//              *** Key Participants ***
// Mediator: interface that defines the communication
// contract between the mediator and the colleagues.
// Concrete Mediator: class that implements the Mediator
// interface and manages communication between colleagues.
// It keeps references to colleagues and coordinates
// their interactions.
// Colleague: interface that defines the contract for
// colleagues.
// Concrete Colleague: these classes implement the
// Colleague interface and communicate with other
// colleagues through the Mediator.

public class Mediator {
    public static void main(String[] args) {
        ChatMediator chatMediator = new ChatRoom();
        User user1 = new ChatUser("John", chatMediator);
        User user2 = new ChatUser("Alice", chatMediator);
    
        user1.sendMessage("Hello, Alice!");
        user2.sendMessage("Hi, John!");
    }
}

// define the mediator interface
interface ChatMediator {
    void sendMessage(String message, User user);
}

// implement the concrete mediator
class ChatRoom implements ChatMediator {
    // should also store all users
    @Override
    public void sendMessage(String message, User user) {
        // logic to send message to all users in the chat room
        System.out.println(user.getName() + " sends message: " + message);
    }
}

// define the colleague interface
interface User {
    void sendMessage(String message);
    void receive(String message);
    String getName();
}

// implement the concrete colleague
class ChatUser implements User {
    // attributes
    private final String name;
    private final ChatMediator mediator;
    // constructor
    public ChatUser(String name, ChatMediator mediator) {
        this.name = name;
        this.mediator = mediator;
    }
    // interface methods
    @Override
    public void sendMessage(String message) {
        mediator.sendMessage(message, this);
    }
    @Override
    public void receive(String message) {
        System.out.println(name + " receives message: " + message);
    }
    @Override
    public String getName() {
        return name;
    }
}

