package showInsertedWindow;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Controller{
    private ArrayList<String> fieldValues = new ArrayList<String>();
    private List<String> fieldNames = new ArrayList<String>();

    @FXML
    private ListView<String> listOfFields=new ListView<String>();

    @FXML
    private ListView<String> listOfValues=new ListView<String>();

    @FXML
    private Button closeButton;

    public Controller() {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/showInsertedWindow/showInsertedWindow.fxml"));
        loader.setControllerFactory(type -> {
            if (type == Controller.class) {
                return this ;
            } else {
                try {
                    return type.newInstance();
                } catch (RuntimeException e) {
                    throw e ;
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
            }
        });

        try {
            Parent root = loader.load();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            stage.show();

        }
        catch (Exception e)
        {
            System.out.println(e);
        }


    }


    public void setFields(List<String> fields)
    {
        fieldNames=fields;
        listOfFields.getItems().addAll(fieldNames);

    }
    public void setFieldValues(ArrayList<String> fieldValues) {
        this.fieldValues = fieldValues;
        listOfValues.getItems().addAll(fieldValues);

    }


    @FXML
    public void backToMain(ActionEvent event) throws IOException
    {
        Stage stage = (Stage) closeButton.getScene().getWindow();
        stage.close();
    }




}
