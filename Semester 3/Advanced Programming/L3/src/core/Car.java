/*Bauer Kristof
521
 */
package core;

public class Car implements Vehicle {
   private String type;
   private int age;

    public Car(String type, int age)
    {
        this.type=type;
        this.age=age;
    }


    public String toString()
    {
    return "Kocsi"+" " +type+" "+age+"\n";
    }

    public void numberOfWheels()
    {
        System.out.println("Az autonak 4 kereke van");
    }



}
