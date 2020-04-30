package createTable;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import sample.CommunicationHelper;

import java.io.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;

import static javax.swing.JOptionPane.showMessageDialog;

public class Controller implements Initializable {
    private List<String> lines = new ArrayList<String>();
    @FXML
    private ListView<String> listofDatabases=new ListView<String>();
    @FXML
    private TextField tableNameField;
    private CommunicationHelper ch = new CommunicationHelper();


    @Override
    public void initialize(URL url,ResourceBundle rb)
    {
        listViewCheck();
    }

    public void listViewCheck()
    {
            ch.setMsg("senddbs");
            String dbs = ch.receiveMsg();
            String[] dbslist = dbs.split("#");
            lines.addAll(Arrays.asList(dbslist));
            listofDatabases.getItems().addAll(lines);
    }

    public void backToMainMenu(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../sample/sample.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }

    public void backtoModify(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../modifyWindow/modifyWindow.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        //This line gets the Stage information
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }

    public void createTable()
    {
            String tableName = tableNameField.getText();

            if (tableName.isEmpty()) {
                showMessageDialog(null, "The table name field is empty. Write something in it!");

            } else { //TODO: kellene checkolni azt hogy letezik-e mar ilyen tabla es ha igen felul akarja-e irni ?
                String dbName = listofDatabases.getSelectionModel().getSelectedItem();
                if(dbName == null)
                {
                    showMessageDialog(null, "Choose a database!");

                }
                else {
                    String send = tableName+"#"+dbName;
                    ch.setMsg("create table "+send);
                    ch.sendMsg();
                }
            }


    }
}
