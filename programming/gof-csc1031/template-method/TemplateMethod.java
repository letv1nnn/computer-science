//                    *** Description ***
// Template Method is a behavioral design pattern that defines
// the skeleton of an algorithm in the superclass but lets subclasses
// override specific steps of the algorithm without changing its structure.

public class TemplateMethod {
    public static void main(String[] args) {}
}

// The abstract class defines a template method that contains a
// skeleton of some algorithm composed of calls, usually to
// abstract primitive operations. Concrete subclasses implement
// these operations, but leave the template method itself
// intact.
abstract class GameAI {
    // The template method defines the skeleton of an algorithm.
    public void turn() {
        collectResources();
        buildStructures();
        buildUnits();
        attack();
    }

    public abstract void collectResources()
    public abstract void buildStructures()
    public abstract void buildUnits()
    public abstract void attack()
}

// Concrete classes have to implement all abstract operations of
// the base class but they must not override the template method
// itself.
class OrcsAI extends GameAI {
    @Override
    public void collectResources() {
        System.out.println("OrcsAI collects resources");
    }
    @Override
    public void buildStructures() {
        System.out.println("OrcsAI builds structures");
    }
    @Override
    public void buildUnits() {
        System.out.println("OrcsAI builds units");
    }
    @Override
    public void attack() {
        System.out.println("OrcsAI attacks");
    }
}

class MonstersAI extends GameAI {
    @Override
    public void collectResources() {
        System.out.println("MonstersAI collects resources");
    }
    @Override
    public void buildStructures() {
        System.out.println("MonstersAI builds structures");
    }
    @Override
    public void buildUnits() {
        System.out.println("MonstersAI builds units");
    }
    @Override
    public void attack() {
        System.out.println("MonstersAI attacks");
    }
}
