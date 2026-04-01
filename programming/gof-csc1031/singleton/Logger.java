public class Logger {
    public static void main(String[] args) {
        Runnable task = () -> {
            Logger logger = Logger.getLogger();
            System.out.println(Thread.currentThread().getName() + " instance: " + logger);
            logger.log("Message from " + Thread.currentThread().getName());
        };        
        
        Thread t1 = new Thread(task, "Thread-1");
        Thread t2 = new Thread(task, "Thread-2");
        Thread t3 = new Thread(task, "Thread-3");
    
        t1.start();
        t2.start();
        t3.start();
    }

    // volatile ensures visibility across threads
    private static volatile Logger instance;
    // private constructor prevents instantiation
    private Logger() {}
    // global access point
    public static Logger getLogger() {
        if (instance == null) {
            synchronized (Logger.class) {
                if (instance == null)
                    instance = new Logger();
            }
        }
        return instance;
    }
    // logging method
    public void log(String message) {
        System.out.println("[LOG] " + message);
    }
}
