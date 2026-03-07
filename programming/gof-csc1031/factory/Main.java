// Factory Method is a creational design pattern that provides an interface for
// creating objects in a superclass, but allows subclasses to alter the type of objects
// that will be created.

public class Main {
    public static void main(String[] args) {
        Shape shape1 = ShapeFactory.getShape(ShapeFactory.ShapeType.CIRCLE);
        shape1.draw();

        Shape shape2 = ShapeFactory.getShape(ShapeFactory.ShapeType.RECTANGLE);
        shape2.draw();
    }
}

