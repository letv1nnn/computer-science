public class ShapeFactory {
    public enum ShapeType {
        CIRCLE,
        RECTANGLE,
    }

    public static Shape getShape(ShapeType type) {
        return switch (type) {
            case CIRCLE -> new Circle();
            case RECTANGLE -> new Rectangle();
        };
    }
}