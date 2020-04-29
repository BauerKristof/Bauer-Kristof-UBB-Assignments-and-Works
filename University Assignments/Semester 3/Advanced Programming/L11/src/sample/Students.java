package sample;

import java.util.ArrayList;
import java.util.HashMap;

public class Students {

    private HashMap<Integer, ArrayList<String>> students;

    public Students() {
        students = new HashMap<>();
    }

    public void add(String name, int age) {
        ArrayList<String> names = students.get(age);

        if (names == null) {
            names = new ArrayList<String> ();
            students.put(age, names);
        }

        names.add(name);
    }

    public ArrayList<String> getStudentsOfTheSameAge(int age) {
        return students.get(age);
    }

}