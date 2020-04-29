/*
Nev:Bauer Kristof
Csoport:521
 */

package core;

public class Car extends Vehicle {
    private float performance;

    public Car(String type,int age, float performance)
    {
        super(type,age);
        this.performance=performance;
    }

    public float getPerformance() {
        return performance;
    }

    public void setPerformance(float performance) {
        this.performance = performance;
    }

    @Override
    public String toString(){
        return type +" "+age+" "+performance;
    }
}
