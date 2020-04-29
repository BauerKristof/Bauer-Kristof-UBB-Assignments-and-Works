/*Nev:Bauer Kristof
Csoport 521
 */

package core;

public class Car {
    private String type;
    private int age;

    public Car(String type, int age)
    {
        this.age=age;
        this.type=type;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Tipus= "+type+" "+"Kora= "+age+"\n";
    }
}
