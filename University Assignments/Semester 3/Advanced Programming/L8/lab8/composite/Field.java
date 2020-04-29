package lab8.composite;

import lab8.Plant;

import java.util.HashSet;
import java.util.Iterator;

public class Field implements Plant {
    private HashSet<Plant>  list;
    private Iterator<Plant> iterator;


    public Field()
    {
        list=new HashSet<>();
    }

    public void Add(Plant p) {
        list.add(p);
    }

    public void Remove(Plant p) {
        list.remove(p);
    }

    public double getOxigenAmountPerYear() {
        float value = 0;
        iterator = list.iterator();

        while (iterator.hasNext()) {
            value += iterator.next().getOxigenAmountPerYear();
        }

        return value;
    }

    @Override
    public int getLifeTime() {
        int max = 0;
        iterator = list.iterator();

        while (iterator.hasNext()) {
            int x = iterator.next().getLifeTime();
            if (x > max) {
                max = x;
            }
        }

        return max;
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
