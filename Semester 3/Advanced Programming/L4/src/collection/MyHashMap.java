/*Nev:Bauer Kristof
Csoport 521
 */

package collection;

import core.Car;

public class MyHashMap {
    private int denominator;
    private Entry[] bucket;

    private int hashFunction(int key)
    {
        return key%denominator;
    }

   public MyHashMap(int denominator)
    {
        this.denominator = denominator;
        bucket = new Entry[denominator];
    }

    public void put(int key, Car car) {
        int index = hashFunction(key);

        Entry newEntry = new Entry(key, car);
        newEntry.setNext(bucket[index]);
        bucket[index] = newEntry;
    }

    public Car get(int key) {
        int index = hashFunction(key);
        Entry entry = bucket[index];

        while (entry != null) {
            if (entry.getKey() == key) {
                return entry.getValue();
            }
            entry = entry.getNext();
        }

        return null;
    }

    public boolean containsKey(int key) {
        int index = hashFunction(key);
        Entry entry = bucket[index];

        while (entry != null) {
            if (entry.getKey() == key) {
                return true;
            }
            entry = entry.getNext();
        }

        return false;
    }
}
