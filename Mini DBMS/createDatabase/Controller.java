package createDatabase;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import sample.CommunicationHelper;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static javax.swing.JOptionPane.showMessageDialog;

public class Controller {

    @FXML
    private TextField getdbNameFiled;
    private List<String> lines = new ArrayList<String>();
    private CommunicationHelper ch = new CommunicationHelper();

    public Controller()
    {
            ch.setMsg("senddbs");
            String dbs = ch.receiveMsg();
            String[] dbslist = dbs.split("#");
            lines.addAll(Arrays.asList(dbslist));
    }

    public void createDataBase()
    {
       String szoveg=getdbNameFiled.getText();

       boolean talalt=false;

        for (String line : lines) {
            if (line.equals(szoveg)) {
                showMessageDialog(null, "This database name has been occupied. Try another one");
                talalt = true;
                break;
            }
        }

       if(!talalt)
       {
               ch.setMsg("create database "+szoveg);
               ch.sendMsg();
               lines.add(szoveg);
       }
    }

    public void backtoMainMenu(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../sample/sample.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }

    public void backToModify(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../modifyWindow/modifyWindow.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        //This line gets the Stage information
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }
}
