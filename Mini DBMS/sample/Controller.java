package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.fxml.FXML;
import javafx.stage.Stage;

import java.io.File;

public class Controller {
    @FXML
    private Button BcreateDB=new Button();

    @FXML
    public void createTable(ActionEvent event)
    {
        try {

            Parent tableViewParent = FXMLLoader.load(getClass().getResource("/createTable/createTable.fxml"));
            Scene tableViewScene = new Scene(tableViewParent);
            //This line gets the Stage information
            Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();

            window.setScene(tableViewScene);
            window.show();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    @FXML
    public void createDatabase(ActionEvent event)
    {
        try{
        File projectDir = new File("C:\\ABKR");
        File curDatabases = new File("C:\\ABKR\\dbs.txt");

        if ((!projectDir.exists()) || (!projectDir.isDirectory())) {

            projectDir.mkdir();
            curDatabases.createNewFile();

        }   //letrehozza a Main ABKR filet ha nem letezik

            Parent tableViewParent = FXMLLoader.load(getClass().getResource("/createDatabase/createDatabase.fxml"));
            Scene tableViewScene = new Scene(tableViewParent);

            //This line gets the Stage information
            Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

            window.setScene(tableViewScene);
            window.show();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }

    }

    @FXML
    public void allModifications(ActionEvent event)
    {
        try {

            Parent tableViewParent = FXMLLoader.load(getClass().getResource("/modifyWindow/modifyWindow.fxml"));
            Scene tableViewScene = new Scene(tableViewParent);
            //This line gets the Stage information
            Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();

            window.setScene(tableViewScene);
            window.show();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    @FXML
    public void loadinsertDB(ActionEvent event) {
        try {

            Parent tableViewParent = FXMLLoader.load(getClass().getResource("/insertWindow/insertWindow.fxml"));
            Scene tableViewScene = new Scene(tableViewParent);
            //This line gets the Stage information
            Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();

            window.setScene(tableViewScene);
            window.show();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

    public void loadDeleteDB(ActionEvent event)
    {
        try {

            Parent tableViewParent = FXMLLoader.load(getClass().getResource("/deleteWindow/deleteWindow.fxml"));
            Scene tableViewScene = new Scene(tableViewParent);
            //This line gets the Stage information
            Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();

            window.setScene(tableViewScene);
            window.show();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }

}
