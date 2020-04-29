package lab8.simple;

import lab8.Plant;

public class OakTree implements Plant {

    public double getOxigenAmountPerYear() {
        return 90;
    }

    @Override
    public int getLifeTime() {
        return 250;
    }

    @Override
    public String getRepresentation() {
        return "O";
    }
}