// Memento pattern saves and restores an object's state without breaking encapsulation.
// Roles: Originator, Memento (immutable snapshot), Caretaker (history).
// Used for undo/redo and rollback.

public class Main {
    public static void main(String[] args) {
        Editor editor = new Editor();
        History history = new History();

        editor.write("Version 1");
        history.save(editor);

        editor.write("Version 2");
        history.save(editor);

        editor.write("Version 3");

        System.out.println(editor.getContent());

        history.undo(editor);
        System.out.println(editor.getContent());
        
        history.undo(editor);
        System.out.println(editor.getContent());
    }
}
