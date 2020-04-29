/*
Nev:Bauer Kristof
Csoport:521
 */

package collection;

import core.Car;

public class CarList {
    private int current;
    private Car[] cars;

    public CarList(int n) {
        this.current=0;
        cars = new Car[n];
    }

    public void addCar(Car carOne) throws ArrayIndexOutOfBoundsException {
        if (current < this.cars.length) {
            cars[current] = carOne;
            current++;
        } else {
            throw new ArrayIndexOutOfBoundsException("HIBA:Index");
        }
    }

    public CarIterator getIterator() {
        return new CarIterator();
    }

    public class CarIterator {
        private int index;

        CarIterator() {
            index = 0;
        }

        public boolean hasMoreElements() {
            return index < current;
        }

        public Car nextElement() {
            return cars[index++];
        }

    }
}
