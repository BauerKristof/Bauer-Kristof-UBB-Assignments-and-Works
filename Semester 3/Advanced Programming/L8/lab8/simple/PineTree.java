package lab8.simple;

import lab8.Plant;

public class PineTree implements Plant {

    public double getOxigenAmountPerYear() {
        return 75;
    }

    @Override
    public int getLifeTime() {
        return 300;
    }

    @Override
    public String getRepresentation() {
        return "P";
    }
}
