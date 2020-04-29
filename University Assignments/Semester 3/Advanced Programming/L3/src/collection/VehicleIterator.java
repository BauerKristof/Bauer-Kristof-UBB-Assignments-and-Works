package collection;

import core.Vehicle;

public interface VehicleIterator {
    public boolean hasMoreElements();
    public Vehicle nextElement();
}