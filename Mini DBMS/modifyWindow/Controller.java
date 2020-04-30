package modifyWindow;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
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
    private List<String> databaseNameList = new ArrayList<String>();
    private List<String> tableNameList = new ArrayList<String>();
    private List<String> fieldTypesList=new ArrayList<String>();
    private List<String> fieldNameList=new ArrayList<String>();
    private List<String> keyTypeList=new ArrayList<String>();
    private List<String> referenceTabelList=new ArrayList<String>();
    private CommunicationHelper ch = new CommunicationHelper();

    private String selectedDBName;

    @FXML
    private TextField fieldName;


    @FXML
    private Button dropDBButton;
    @FXML
    private Button dropTableButton;
    @FXML
    private Button removeFieldButton;


    @FXML
    private ListView<String>  listofDB =new ListView<String>();
    @FXML
    private ListView<String> listofTables=new ListView<String>();
    @FXML
    private ListView<String> fieldnameTypesList=new ListView<String>();
    @FXML
    private ListView<String> listOfFields=new ListView<String>();
    @FXML
    private ListView<String> keySelectList=new ListView<String>();
    @FXML
    private ListView<String> listOfRefTables=new ListView<String>();



    @Override
    public void initialize(URL url, ResourceBundle rb) //
    {
        listViewCheck();
        addFieldTypes();
        addKeyTypes();
    }


    public void listViewCheck() //
    {
        ch.setMsg("senddbs");
        String dbs = ch.receiveMsg();
        String[] dbslist = dbs.split("#");
        databaseNameList.addAll(Arrays.asList(dbslist));
        listofDB.getItems().addAll(databaseNameList);

    }

    public void addFieldTypes() //
    {
        //todo:ezekre majd irni type checkereket. stringrol konnyu atalakitani barmire, de valid kell legyen.
        fieldTypesList.add("Int");
        fieldTypesList.add("String");
        fieldTypesList.add("Float");
        fieldTypesList.add("Date");

        fieldnameTypesList.getItems().addAll(fieldTypesList);
    }

    public void addKeyTypes()
    {
       // keyTypeList.add("PK(PrimaryKey)");
        keyTypeList.add("FK(ForeignKey)");
        keyTypeList.add("Index");
        keyTypeList.add("None");

        keySelectList.getItems().addAll(keyTypeList);

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

    @FXML
    public void dropDatabase() //
    {
        dropDBButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                final int selectedIdx = listofDB.getSelectionModel().getSelectedIndex();
                if (selectedIdx != -1) {
                    String dbNameToRemove = listofDB.getSelectionModel().getSelectedItem();
                    ch.setMsg("drop database "+dbNameToRemove);
                    ch.sendMsg();

                    final int newSelectedIdx =
                            (selectedIdx == listofDB.getItems().size() - 1)
                                    ? selectedIdx - 1
                                    : selectedIdx;

                    //Removeol a listviewbol
                    listofDB.getItems().remove(selectedIdx);
                    listofDB.getSelectionModel().select(newSelectedIdx);

                    //Removeol a listview nevet tarolo String Arraybol
                    databaseNameList.remove(selectedIdx);


                }
            }
        });
    }


    @FXML
    public void dropTable()
    {
        dropTableButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                final int selectedIdx = listofTables.getSelectionModel().getSelectedIndex();
                if (selectedIdx != -1) {
                    String tableNameToRemove = listofTables.getSelectionModel().getSelectedItem();

                    selectedDBName = listofDB.getSelectionModel().getSelectedItem();
                    ch.setMsg("checkref "+tableNameToRemove+"#"+selectedDBName);
                    String canDrop = ch.receiveMsg();
                    if (!canDrop.equals("%canDrop%")){
                        String[] refList = canDrop.split("#");
                        showMessageDialog(null, "Can not drop referenced table.\n References found in: "+ Arrays.toString(refList));
                        return;
                    }

                    ch.setMsg("drop table "+tableNameToRemove+"#"+selectedDBName);
                    ch.sendMsg();

                    final int newSelectedIdx =
                            (selectedIdx == listofTables.getItems().size() - 1)
                                    ? selectedIdx - 1
                                    : selectedIdx;

                    //Removeol a listviewbol
                    listofTables.getItems().remove(selectedIdx);
                    listofTables.getSelectionModel().select(newSelectedIdx);

                    //Removeol a listview nevet tarolo String Arraybol
                    tableNameList.remove(selectedIdx);


                }
            }
        });
    }

    @FXML
    public void addNewField() //TODO:Ha addolok egy fieldet ne kelljen megint a tablere clickelni hogy megjelentise a megnyitott filed mezok kozott
    {
        String fieldNameString = fieldName.getText();
        fieldNameString=fieldNameString.replace(" ","");

        if (fieldNameString.isEmpty()) {
            showMessageDialog(null, "The field is empty. Write something in it!");
        }
        else
        {
            String dbNameString=listofDB.getSelectionModel().getSelectedItem();
            String tableNameString=listofTables.getSelectionModel().getSelectedItem();
            String fieldTypeString=fieldnameTypesList.getSelectionModel().getSelectedItem();
            String keyRestriction=keySelectList.getSelectionModel().getSelectedItem();
            String referencedFKTable=null;

            if( (dbNameString==null) || (tableNameString==null) || (fieldNameString==null) || (fieldTypeString==null))
            {
                showMessageDialog(null, "One of the elements (database,table,type) has not been selected. Try again!");
            }
            else{
                if (keyRestriction.equals("FK(ForeignKey)"))  {
                    referencedFKTable=listOfRefTables.getSelectionModel().getSelectedItem();
                    if(referencedFKTable == null) {
                        showMessageDialog(null, "You have to select the table the FK references. Try again!");
                    }
                    else if (referencedFKTable.equals(tableNameString)){
                        showMessageDialog(null, "You can't reference the same table. Try again!");
                    }
                    else{
                        ch.setMsg("addfield "+fieldNameString+"#"+fieldTypeString+"#"+tableNameString+"#"+dbNameString+"#"+keyRestriction+"#"+referencedFKTable);
                        ch.sendMsg();
                    }
                }
                else {
                    ch.setMsg("addfield " + fieldNameString + "#" + fieldTypeString + "#" + tableNameString + "#" + dbNameString + "#" + keyRestriction + "#" + null);
                    ch.sendMsg();
                }

            }
        }

    }

    public void showFields(MouseEvent arg0)
    {
        listOfFields.getItems().clear();
        fieldNameList.clear();

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
            }

    }

    public void removeField() {


            removeFieldButton.setOnAction(new EventHandler<ActionEvent>() {
                @Override
                public void handle(ActionEvent event) {

                    String dbNameString = listofDB.getSelectionModel().getSelectedItem();
                    String tableNameString = listofTables.getSelectionModel().getSelectedItem();
                    String fieldName = listOfFields.getSelectionModel().getSelectedItem();

                    // System.out.println(dbNameString+" "+tableNameString+" "+fieldName);

                    if ((dbNameString == null) || (tableNameString == null) || (fieldName == null)) {
                        showMessageDialog(null, "One of the elements (database,table,field) has not been selected. Try again!");
                    }
                    else {
                        ch.setMsg("removefield " + fieldName + "#" + tableNameString + "#" + dbNameString);
                        ch.sendMsg();

                        final int selectedIdx = listOfFields.getSelectionModel().getSelectedIndex();
                        if (selectedIdx != -1) {

                            final int newSelectedIdx =
                                    (selectedIdx == listOfFields.getItems().size() - 1)
                                            ? selectedIdx - 1
                                            : selectedIdx;

                            //Removeol a listviewbol
                            listOfFields.getItems().remove(selectedIdx);
                            listOfFields.getSelectionModel().select(newSelectedIdx);

                            //Removeol a listview nevet tarolo String Arraybol
                            fieldNameList.remove(selectedIdx);

                        }
                    }
                }
            });


    }

    @FXML
    public void showFKTabel()
    {
        String keyRestriction=keySelectList.getSelectionModel().getSelectedItem();

        if (keyRestriction.equals("FK(ForeignKey)")) {
            String dbNameString = listofDB.getSelectionModel().getSelectedItem();
            String tableNameString = listofTables.getSelectionModel().getSelectedItem();

            if ((dbNameString == null) || (tableNameString == null)) {
                showMessageDialog(null, "One of the elements (database,table) has not been selected. Try again!");
            }
            else {

                listOfRefTables.getItems().clear();
                referenceTabelList.clear();

                String databaseClicked = listofDB.getSelectionModel().getSelectedItem();
                ch.setMsg("sendtables " + databaseClicked);
                String tables = ch.receiveMsg();

                String[] tableslist = tables.split("#");

                referenceTabelList.addAll(Arrays.asList(tableslist));

                listOfRefTables.getItems().addAll(referenceTabelList);
            }
        }
        else{
            String[] emptylist={" "};
            listOfRefTables.getItems().clear();
            referenceTabelList.clear();
            referenceTabelList.addAll(Arrays.asList(emptylist));
            listOfRefTables.getItems().addAll(referenceTabelList);
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
    @FXML
    public void createDatabaseTransfer(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../createDatabase/createDatabase.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        //This line gets the Stage information
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }

    @FXML
    public void createTabelTransfer(ActionEvent event) throws IOException
    {
        Parent tableViewParent = FXMLLoader.load(getClass().getResource("../createTable/createTable.fxml"));
        Scene tableViewScene = new Scene(tableViewParent);

        //This line gets the Stage information
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();

        window.setScene(tableViewScene);
        window.show();
    }
}