/*Bauer Kristof
521
 */

import collection.VehicleList;
import core.AirPlane;
import core.Car;
import core.Vehicle;

public class TestVehicleList {

        public static void main(String[] args) {
            Car auto1 = new Car("Ford", 2);
            Car auto2 = new Car("Opel", 13);
            Car auto3 = new Car("Ferrari", 14);
            AirPlane repulo1=new AirPlane("Boeing",10,747);
            AirPlane repulo2=new AirPlane("MIG-27",50,30);


            try {
                VehicleList lista = new VehicleList(5);
                lista.addVehicle(auto1);
                lista.addVehicle(auto2);
                lista.addVehicle(auto3);
                lista.addVehicle(repulo1);
                lista.addVehicle(repulo2);

                VehicleList.VehicleForwardIterator i = lista.getForwardIterator();
                Vehicle jarmu;
                VehicleList.VehicleBackwardIterator j=lista.getBackwardIterator();
                while (i.hasMoreElements()) {
                    jarmu=i.nextElement();
                    System.out.println(jarmu);
                    jarmu.numberOfWheels();
                }

                System.out.println("Backward");
                while (j.hasMoreElements()) {
                    jarmu=j.nextElement();
                    System.out.println(jarmu);
                    jarmu.numberOfWheels();
                }

            } catch (ArrayIndexOutOfBoundsException error) {
                System.out.println(error);

            }
        }
}
