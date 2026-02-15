// Originator

public class Editor {
    private String content;

    public void write(String text) {
        content = text;
    }

    public String getContent() {
        return content;
    }

    // save state
    public EditorMemento save() {
        return new EditorMemento(content);
    }

    // restore state
    public void restore(EditorMemento memento) {
        content = memento.getContent();
    }
}
