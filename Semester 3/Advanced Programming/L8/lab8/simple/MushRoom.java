package lab8.simple;

import lab8.Plant;

public class MushRoom implements Plant {

    public double getOxigenAmountPerYear() {
        return 8;
    }

    @Override
    public int getLifeTime() {
        return 20;
    }

    @Override
    public String getRepresentation() {
        return "M";
    }
}
