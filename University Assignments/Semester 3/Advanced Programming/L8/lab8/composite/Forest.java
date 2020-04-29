package lab8.composite;

import lab8.Plant;

import java.util.ArrayList;

public class Forest implements Plant {
    private ArrayList<Plant> list;

    public Forest() {
        list = new ArrayList<>();
    }

    public void Add(Plant p) {
        list.add(p);
    }

    public void Remove(Plant p) {
        list.remove(p);
    }

    @Override
    public double getOxigenAmountPerYear() {
        float oxigen = 0;

        for (int i = 0; i < list.size(); i++) {
            oxigen += list.get(i).getOxigenAmountPerYear();
        }

        return oxigen;
    }

    @Override
    public int getLifeTime() {
        int lifetime = 0;
        int max = -1;

        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getLifeTime() > max)
                max = list.get(i).getLifeTime();
        }

        lifetime = max;
        return lifetime;
    }

    @Override
    public String getRepresentation() {
        String e = "{";

        for (Plant p : list) {
            e += p.getRepresentation() + ",";
        }
        e += "}";
        return e;
    }
}
