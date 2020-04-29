package lab8.simple;

import lab8.Plant;

public class Grass implements Plant {

    public double getOxigenAmountPerYear() {
        return 25;
    }

    @Override
    public int getLifeTime() {
        return 5;
    }

    @Override
    public String getRepresentation() {
        return "G";
    }
}
