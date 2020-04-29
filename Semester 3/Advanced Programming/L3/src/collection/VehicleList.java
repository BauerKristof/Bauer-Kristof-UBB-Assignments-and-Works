/*Bauer Kristof
521
 */

package collection;

import core.Vehicle;

public class VehicleList{
   private int current;
   private Vehicle[] vehicles;

    public VehicleList(int n)
    {
        current=0;
        vehicles=new Vehicle[n];
    }

    public void addVehicle(Vehicle peldany)
    {
        if(current<vehicles.length)
        {
          vehicles[current]=peldany;
          current++;
        }
        else {
            throw new ArrayIndexOutOfBoundsException("HIBA:Index");
        }
    }

    public VehicleForwardIterator getForwardIterator()
    {
        return new VehicleForwardIterator();
    }

    public VehicleBackwardIterator getBackwardIterator()
    {
        return new VehicleBackwardIterator();
    }


    public class VehicleForwardIterator implements VehicleIterator {
        private int index;

        public VehicleForwardIterator()
        {
            index=0;
        }

        @Override
        public boolean hasMoreElements()
        {
            return index<current;
        }

        @Override
        public Vehicle nextElement()
        {
            return vehicles[index++];
        }
    }

    public class VehicleBackwardIterator implements VehicleIterator{
        private int index;

        public VehicleBackwardIterator()
        {
            index=current-1;
        }

        @Override
        public boolean hasMoreElements()
        {
            return index>=0;
        }

        @Override
        public Vehicle nextElement()
        {
            return vehicles[index--];
        }

    }
}
