/*
Nev:Bauer Kristof
Csoport:521
 */


import core.Car;
import collection.CarList;


public class TestCarList {

    public static void main(String[] args) {
        Car auto1 = new Car("Ford", 2, 10);
        Car auto2 = new Car("Opel", 13, 20);
        Car auto3 = new Car("Ferrari", 14, 30);

        try {
            CarList lista = new CarList(2);
            lista.addCar(auto1);
            lista.addCar(auto2);
            lista.addCar(auto3);

            CarList.CarIterator i = lista.getIterator();
            while (i.hasMoreElements()) {
                System.out.println(i.nextElement());
            }
        } catch (ArrayIndexOutOfBoundsException error) {
            System.out.println(error);

        }
    }
}
