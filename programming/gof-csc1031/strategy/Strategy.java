//              *** Description ***
// Strategy is a behavioral design pattern that lets
// you define a family of algorithms, put each of them
// into a separate class, and make their objects interchangeable.

public class Strategy {
    public static void main(String[] args) {
        Navigator nav = new Navigator(new PublicTransportStrategy());
        nav.buildRoute(new Coordinate(-1.56, 42.33), new Coordinate(233.14, -23.42));
        nav.setStrategy(new WalkingStrategy());
        nav.buildRoute(new Coordinate(12.56, -48.13), new Coordinate(233.14, -23.42));
    }
}

// The strategy interface declares operations common to all
// supported versions of some algorithm. The context uses this
// interface to call the algorithm defined by the concrete
// strategies.
interface RouteStrategy {
    void buildRoute(Coordinate origin, Coordinate destination);
}

class Coordinate {
    public double x, y;
    public Coordinate(double x, double y) { this.x = x; this.y = y; }
    public double distance(Coordinate other) {
        java.util.Objects.requireNonNull(other, "other coordinate cannot be null");
        return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
    }
    @Override
    public String toString() { return "X: " + x + ", Y: " + y; }
}

// Concrete strategies implement the algorithm while following
// the base strategy interface. The interface makes them
// interchangeable in the context.
class RoadStrategy implements RouteStrategy {
    @Override
    public void buildRoute(Coordinate origin, Coordinate destination) {
        System.out.println("Building a road route (Origin: " + origin + ", Destination: " + destination + "): " + origin.distance(destination));
    }
}
class WalkingStrategy implements RouteStrategy {
    @Override
    public void buildRoute(Coordinate origin, Coordinate destination) {
        System.out.println("Building a walking route (Origin: " + origin + ", Destination: " + destination + "): " + origin.distance(destination));
    }
}
class PublicTransportStrategy implements RouteStrategy {
    @Override
    public void buildRoute(Coordinate origin, Coordinate destination) {
        System.out.println("Building a public transport route (Origin: " + origin + ", Destination: " + destination + "): " + origin.distance(destination));
    }
}

// The context defines the interface of interest to clients.
class Navigator {
    private RouteStrategy strategy;

    public Navigator(RouteStrategy strategy) {
        this.strategy = java.util.Objects.requireNonNull(strategy, "strategy cannot be null");
    }

    public void buildRoute(Coordinate origin, Coordinate destination) {
        strategy.buildRoute(origin, destination);
    }
    public void setStrategy(RouteStrategy strategy) {
        this.strategy = java.util.Objects.requireNonNull(strategy, "strategy cannot be null");
    }
}
