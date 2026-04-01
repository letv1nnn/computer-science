//              *** Description ***
// Observer is a behavioral design pattern that lets
// you define a subscription mechanism to notify
// multiple objects about any events that happen
// to the object they are observing.
// Usefult when you wnat to esteblish a one-to-many
// relationship between objects.
// Widely used in "event-driven programming".
//
//              *** Components ***
// Subject: the object that holds the state and notifies
// the observer.
// Observer: objects that listen for state changes in
// the subject.
// ConcreteSubject: the class that implements the Subject
// interface.
// ConcreteObserver: the class that implements the
// Observer interface and responds to changes in the subject.

import java.util.ArrayList;
import java.util.List;

public class Observer {
    public static void main(String[] args) {
        WeatherStation weatherStation = new WeatherStation();

        // create two displays and register them as observers.
        WeatherDisplay display1 = new WeatherDisplay(), display2 = new WeatherDisplay();
        weatherStation.addObserver(display1);
        weatherStation.addObserver(display2);
    
        // simulate changes in weather data
        weatherStation.setMeasurements(25.5f, 65.0f);
        weatherStation.setMeasurements(27.3f, 70.0f);
    }
}

interface Subject {
    void addObserver(WeatherObserver observer);
    void removeObserver(WeatherObserver observer);
    void notifyObservers();
}

// the Observer defines and update() method that will
// be called by the Subject whenever there is a change.
interface WeatherObserver {
    void update(float temperature, float humidity);
}

// concrete subject (weather station)
class WeatherStation implements Subject {
    // attributes
    private List<WeatherObserver> observers;
    private float temperature, humidity;
    // constructor
    public WeatherStation() {
        this.observers = new ArrayList<>();
    }
    // methods
    @Override
    public void addObserver(WeatherObserver observer) {
        observers.add(observer);
    }
    @Override
    public void removeObserver(WeatherObserver observer) {
        observers.remove(observer);
    }
    @Override
    public void notifyObservers() {
        for (WeatherObserver observer : observers)
            observer.update(temperature, humidity);
    }
    public void setMeasurements(float temperature, float humidity) {
        this.temperature = temperature;
        this.humidity = humidity;
        notifyObservers();
    }
}

// concrete observer (display)
class WeatherDisplay implements WeatherObserver {
    // attributes
    private float temperature, humidity;
    // methods
    @Override
    public void update(float temperature, float humidity) {
        this.temperature = temperature;
        this.humidity = humidity;
        display();
    }
    public void display() {
        System.out.println("Current conditions: " + temperature + "C degrees and " + humidity + "% humidity");
    }
}





