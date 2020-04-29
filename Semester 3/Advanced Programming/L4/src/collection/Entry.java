/*Nev:Bauer Kristof
Csoport 521
 */

package collection;

import core.Car;

public class Entry {
    private int key;
    private Car value;
    private Entry next;

    Entry(int key, Car value)
    {
        this.key=key;
        this.value=value;
    }

    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public Car getValue() {
        return value;
    }

    public void setValue(Car value) {
        this.value = value;
    }

    public Entry getNext() {
        return next;
    }

    public void setNext(Entry next) {
        this.next = next;
    }

}
