package insertWindow;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.CommunicationHelper;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import sample.TypeValidator;

import static javax.swing.JOptionPane.showMessageDialog;

public class Controller  implements Initializable {
    private List<String> databaseNameList = new ArrayList<String>();
    private List<String> tableNameList = new ArrayList<String>();
    private List<String> fieldNameList=new ArrayList<String>();
    private CommunicationHelper ch = new CommunicationHelper();
    private TypeValidator tw = new TypeValidator();

    private List<String> fieldswithValues=new ArrayList<String>();


    private ArrayList<String> insertedFieldValue=new ArrayList<String>();


    @FXML
    TextField fieldValue;

    @FXML
    private ListView<String> listofDB =new ListView<String>();
    @FXML
    private ListView<String> listofTables=new ListView<String>();
    @FXML
    private ListView<String> listOfFields=new ListView<String>();

    @FXML ListView<String> listofFiledwithValues=new ListView<String>();

    @Override
    public void initialize(URL url, ResourceBundle rb) //
    {
        listViewCheck();
    }

    public void listViewCheck()
    {
        ch.setMsg("senddbs");
        String dbs = ch.receiveMsg();
        String[] dbslist = dbs.split("#");
        databaseNameList.addAll(Arrays.asList(dbslist));
        listofDB.getItems().addAll(databaseNameList);

        listofFiledwithValues.setMouseTransparent(true);

    }

    @FXML
    public void showTables(MouseEvent arg0) //
    {
        listofTables.getItems().clear();
        tableNameList.clear();

        String databaseClicked= listofDB.getSelectionModel().getSelectedItem();
        ch.setMsg("sendtables "+databaseClicked);
        String tables = ch.receiveMsg();

        String[] tableslist = tables.split("#");
        tableNameList.addAll(Arrays.asList(tableslist));

        listofTables.getItems().addAll(tableNameList);
    }


    public void showFields(MouseEvent arg0)
    {
        listOfFields.getItems().clear();
        fieldNameList.clear();
        insertedFieldValue.clear();

        String dbNameString = listofDB.getSelectionModel().getSelectedItem();
        String tableNameString = listofTables.getSelectionModel().getSelectedItem();

        if ((dbNameString == null) || (tableNameString == null)) {
            showMessageDialog(null, "One of the elements (database,table) has not been selected. Try again!");
        } else {

            String databaseClicked= listofDB.getSelectionModel().getSelectedItem();
            ch.setMsg("sendfields "+tableNameString+"#"+dbNameString);
            String fields = ch.receiveMsg();
            String[] fieldslist = fields.split("#");
            fieldNameList.addAll(Arrays.asList(fieldslist));
            listOfFields.getItems().addAll(fieldNameList);


            for(int i=0;i<fieldNameList.size();i++)
            {
                insertedFieldValue.add("null");
            }

            refreshFieldValues();

        }

    }

    @FXML
    public void addFieldValue(){

        String fieldValueString = fieldValue.getText();
        if(fieldValueString.isEmpty())
        {
            showMessageDialog(null, "The field is empty. Write a value in it!");
        }
        else {
            String fieldName = listOfFields.getSelectionModel().getSelectedItem();
            String[] splitField = fieldName.trim().split(" ");
            String fieldType = splitField[1];
            String fieldKeyType = splitField[2];

            if (fieldKeyType.equals("FK")) fieldType="String"; //todo:kicsit vilagosabban megoldani az fk tipusat ha kell. az objectid minding string.

            if(fieldType.equals("Int") && tw.isInt(fieldValueString) == false)
            {
                showMessageDialog(null, "Invalid Type. The requested is Integer");

            }

            if(fieldType.equals("Float") && tw.isFloat(fieldValueString) == false)
            {
                showMessageDialog(null, "Invalid Type. The requested is Float");

            }

            if(fieldType.equals("String") && tw.isString(fieldValueString) == false)
            {
                showMessageDialog(null, "Invalid Type. The requested is String");

            }
            if(fieldType.equals("Date") && tw.isDate(fieldValueString) == false)
            {
                showMessageDialog(null, "Invalid Type. The requested is Date");
            }

            String databaseName = listofDB.getSelectionModel().getSelectedItem();
            String collectionName = listofTables.getSelectionModel().getSelectedItem();
            String[] fieldData = fieldName.split(" ");
            if (fieldData.length >= 3){
                if (fieldData[2].equals("Index")){
                    ch.setMsg("uniqueValidate "+databaseName+"#"+collectionName+"#"+fieldData[0]+"#"+fieldValueString);
                    String valid = ch.receiveMsg();
                    if (valid.equals("0")){
                        showMessageDialog(null, "There is already a unique field with this value. Try again");
                        return;
                    }
                }
                else if (fieldData[2].equals("FK")){
                    ch.setMsg("FKValidate "+databaseName+"#"+collectionName+"#"+fieldData[0]+"#"+fieldValueString+"#"+fieldData[3]);
                    String valid = ch.receiveMsg();
                    if (valid.equals("0")){
                        showMessageDialog(null, "The value doesn't exits in the reference. Try again");
                        return;
                    }
                }
            }

            int indexField=fieldNameList.indexOf(fieldName);
            insertedFieldValue.set(indexField,fieldValueString);
            refreshFieldValues();
        }
    }

    private void refreshFieldValues()
    {
        if (fieldNameList.get(0).isEmpty() == false) {
            fieldswithValues.clear();
            listofFiledwithValues.getItems().clear();

            for (int i = 0; i < fieldNameList.size(); i++) {
                fieldswithValues.add(fieldNameList.get(i) + " - " + insertedFieldValue.get(i));
            }

            listofFiledwithValues.getItems().addAll(fieldswithValues);
        }


    }

    public void saveInsert(ActionEvent event) {
        String databaseName = listofDB.getSelectionModel().getSelectedItem();
        String collectionName = listofTables.getSelectionModel().getSelectedItem();
        String fieldName = listOfFields.getSelectionModel().getSelectedItem();

        if ((databaseName == null) || (collectionName == null) || (fieldName == null)) {
            showMessageDialog(null, "One of the elements (database,table) has not been selected or you have no fields to insert in. Try again!");
        } else {
            if (fieldNameList.get(0).isEmpty()) {
                showMessageDialog(null, "You have no elements in field section, add some and try again!");
            }

            /*TODO: Lekerni a primary keyt - feltolteni az adatokat mongoDB-be*/
            //fieldname listbe vannak benen a fieldek nevei, lekerdezni egy bizonyos indexen levo field nevet lasd 142

            showInsertedWindow.Controller c = new showInsertedWindow.Controller();
            c.setFieldValues(insertedFieldValue);
            c.setFields(fieldNameList);


            /*
            ch.setMsg("SENDPK "+collectionName+"#"+databaseName);
            String rec = ch.receiveMsg();
            int pkindex = Integer.parseInt(rec);

            String pkval = insertedFieldValue.get(pkindex);
            insertedFieldValue.remove(pkindex);
            fieldNameList.remove(pkindex);
            */

            String values="";
            for (String s : insertedFieldValue){
                values=values.concat(s+"%");
            }


            String names="";
            for (String s : fieldNameList){
                String[] temp = s.split(" ");
                names=names.concat(temp[0]+"%");
            }
            ch.setMsg("insert "+collectionName+"#"+databaseName+"#"+values+"#"+names);
            ch.sendMsg();
        }
    }

    @FXML
    public void backToMain(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../sample/sample.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        //This line gets the Stage information
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }

    public ArrayList<String> getFields()
    {
        return insertedFieldValue;
    }



}
