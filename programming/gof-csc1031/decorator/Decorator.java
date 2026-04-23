//           *** Description ***
// Decorator is a structural design pattern that
// lets you attach new behaviors to objects by
// placing these objects inside special wrapper
// objects that contain the behaviors
// ("add features at runtime like layers").

public class Decorator {
    public static void main(String[] args) {
        Coffee coffee = new SimpleCoffee();

        coffee = new SugarDecorator(coffee);
        coffee = new MilkDecorator(coffee);

        System.out.println(coffee.getDescription());
        System.out.println(coffee.cost());
    }
}

// component interface
interface Coffee {
    String getDescription();
    double cost();
}

// concrete component
class SimpleCoffee implements Coffee {
    @Override
    public String getDescription() {
        return "Simple Coffee";
    }

    @Override
    public double cost() {
        return 5.0;
    }
}

// decorator base class
abstract class CoffeeDecorator implements Coffee {
    protected Coffee coffee;

    public CoffeeDecorator(Coffee coffee) {
        this.coffee = java.util.Objects.requireNonNull(coffee, "coffee cannot be null");
    }

    @Override
    public String getDescription() {
        return coffee.getDescription();
    }

    @Override
    public double cost() {
        return coffee.cost();
    }
}

// concrete decorators
class MilkDecorator extends CoffeeDecorator {
    public MilkDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getDescription() {
        return coffee.getDescription() + ", Milk";
    }

    @Override
    public double cost() {
        return coffee.cost() + 2.0;
    }
}

class SugarDecorator extends CoffeeDecorator {
    public SugarDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getDescription() {
        return coffee.getDescription() + ", Sugar";
    }
    
    @Override
    public double cost() {
        return coffee.cost() + 1.0;
    }
}
