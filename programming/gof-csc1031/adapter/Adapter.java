//      *** Description ***
// The Adapter Pattern is a structural
// design patterm that allows two
// incompatible interfaces to work together.

public class Adapter {
    public static void main(String[] args) {
        IPhone16 phone = new IPhone16(new IPhone13To16Adapter());
        phone.onCharge();
    }
}

// target interface
interface IPhone {
    public void onCharge();
}

// adaptee class and the interface it's initially implements
interface Charger {
    public void charge();
}

class IPhone13Charger implements Charger {
    @Override
    public void charge() {
        System.out.println("charging with lightning charger");
    }
}

// adapter class that implements the target interface and
// internally uses an instance of the adaptee class
class IPhone13To16Adapter implements Charger {
    private IPhone13Charger iphone13Charger;

    public IPhone13To16Adapter() {
        iphone13Charger = new IPhone13Charger();
    }

    @Override
    public void charge() {
        iphone13Charger.charge();
    }
}


class IPhone16 implements IPhone {
    Charger IPhone13To16Adapter;

    public IPhone16(Charger IPhone13To16Adapter) {
        this.IPhone13To16Adapter = IPhone13To16Adapter;
    }

    @Override
    public void onCharge() {
        IPhone13To16Adapter.charge();
    }
}
