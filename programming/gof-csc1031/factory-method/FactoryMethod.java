//             *** Description ***
// Factory Method is a creational design pattern
// that provides an interface for creating objects
// in a superclass, but allows subclasses to alter
// the type of objects that will be created.

public class FactoryMethod {
    public static void main(String[] args) {
        CharacterFactory factory = new WarriorFactory();
        Character character = factory.createCharacter();
        character.attack();
        character.defend();
    }
}

interface Character {
    void attack();
    void defend();
}

class Warrior implements Character {
    @Override
    public void attack() {
        System.out.println("Warrior attacks with a sword!");
    }
    @Override
    public void defend() {
        System.out.println("Warrior defenfs with a shield!");
    }
}

class Wizzard implements Character {
    @Override
    public void attack() {
        System.out.println("Wizzard attacks with magic!");
    }
    @Override
    public void defend() {
        System.out.println("Wizzard defends with a spell!");
    }
}

abstract class CharacterFactory {
    // definition of a factory method for creating characters
    public abstract Character createCharacter();
}

class WarriorFactory extends CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Warrior();
    }
}

class WizzardFactory extends CharacterFactory {
    @Override
    public Character createCharacter() {
        return new Wizzard();
    }
}

