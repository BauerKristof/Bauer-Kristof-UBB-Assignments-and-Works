/*Bauer Kristof
521
 */

package core;

public class AirPlane implements Vehicle{
    private String type;
    private int age;
    private float length;

    public AirPlane(String type, int age, float length)
    {
        this.type=type;
        this.age=age;
        this.length=length;
    }

    public String toString()
    {
        return "Repulo"+" " +type+" "+age+" "+length+"\n";

    }

    public void numberOfWheels()
    {
        System.out.println("A repulogepnek 8 kereke van");
    }


}
