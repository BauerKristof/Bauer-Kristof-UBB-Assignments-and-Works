package sample;

import java.util.ArrayList;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;

public class Controller {

    private String name;
    private int age;

    private Students students = new Students();

    @FXML
    private Label ageValueLabel;

    @FXML
    private Slider ageSlider;

    @FXML
    private TextField nameTextField;

    @FXML
    private TextField ageTextField;

    @FXML
    public void ageSliderHandler() {
        ageValueLabel.setText((int) ageSlider.getValue() + "");
    }

    @FXML
    public void addBtnClicked() {
        if (nameTextField.getText().isEmpty()) {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Hiba");
            alert.setHeaderText("Kötelezõ nevet megadni!");
            alert.setContentText("A név mezõbe kötelezõen meg kell add egy diák nevét!");
            alert.showAndWait();
        } else {
            age = Integer.parseInt(ageValueLabel.getText());
            name = nameTextField.getText();
            nameTextField.setText("");
            students.add(name, age);

            System.out.println("Hozzáadtam egy új diákot: " + name + ", életkor: " + age);
        }
    }

    @FXML
    public void listBtnClicked() {
        int age;

        try {
            age = Integer.parseInt(ageTextField.getText());
        } catch (NumberFormatException e) {
            age = -1;
        }

        if (age != -1 && age >= 10 && age <= 100) {
            ArrayList<String> names = students.getStudentsOfTheSameAge(age);

            if (!names.isEmpty()) {
                System.out.println("\nAzon diákok névsora, akik " + age + " évesek:");
                for (String name : names) {
                    System.out.println(name);
                }
            } else {
                Alert alert = new Alert(AlertType.ERROR);
                alert.setTitle("Hiba");
                alert.setHeaderText("Nem található diák!");
                alert.setContentText("Sajnos nem található megadott életkorú diák a listán.");
                alert.showAndWait();
            }
        } else {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Hiba");
            alert.setHeaderText("Érvénytelen bemenet!");
            alert.setContentText("Az életkor mezõbe csak 10-100 közötti számot írhatsz!");
            alert.showAndWait();
        }
    }

}