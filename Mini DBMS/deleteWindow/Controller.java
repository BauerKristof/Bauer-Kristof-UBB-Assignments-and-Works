package deleteWindow;

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
import javafx.stage.Stage;
import sample.CommunicationHelper;
import sample.TypeValidator;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;

import static javax.swing.JOptionPane.showMessageDialog;

public class Controller  implements Initializable {
    private List<String> databaseNameList = new ArrayList<String>();
    private List<String> tableNameList = new ArrayList<String>();
    private List<String> fieldNameList=new ArrayList<String>();
    private List<String> operatorList=new ArrayList<String>();

    private CommunicationHelper ch = new CommunicationHelper();
    private TypeValidator tw = new TypeValidator();


    @FXML
    TextField conditionValue;

    @FXML
    private ListView<String> listofDB =new ListView<String>();
    @FXML
    private ListView<String> listofTables=new ListView<String>();
    @FXML
    private ListView<String> listOfFields=new ListView<String>();
    @FXML
    private ListView<String> operators=new ListView<String>();


    @Override
    public void initialize(URL url, ResourceBundle rb) //
    {
        listViewCheck();
        loadOperatorList();
    }

    public void listViewCheck()
    {
        ch.setMsg("senddbs");
        String dbs = ch.receiveMsg();
        String[] dbslist = dbs.split("#");
        databaseNameList.addAll(Arrays.asList(dbslist));
        listofDB.getItems().addAll(databaseNameList);
    }

    @FXML
    public void loadOperatorList()
    {
        operatorList.add("=");
        operatorList.add("<>");

        operators.getItems().addAll(operatorList);
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

    @FXML
    public void deleteFromTable(){

        String databaseName = listofDB.getSelectionModel().getSelectedItem();
        String collectionName = listofTables.getSelectionModel().getSelectedItem();
        String fieldName = listOfFields.getSelectionModel().getSelectedItem();
        String operatorSelected= operators.getSelectionModel().getSelectedItem();



        if ((databaseName == null) || (collectionName == null) || (fieldName==null) || (operatorSelected==null)) {
            showMessageDialog(null, "One of the elements (database,table,field,operator) has not been selected or you have no fields to insert in. Try again!");
        }
        else {
            if (fieldNameList.get(0).isEmpty()) {
                showMessageDialog(null, "You have no elements in field section, add some and try again!");
            }
            else {
                String fieldValueString = conditionValue.getText();

                if (fieldValueString.isEmpty()) {
                    showMessageDialog(null, "The field is empty. Write a value in it!");
                } else {
                    String[] splitField = fieldName.trim().split(" ");
                    String fieldType = splitField[1];

                    if (fieldType.equals("Int") && tw.isInt(fieldValueString) == false) {
                        showMessageDialog(null, "Invalid Type. The requested is Integer");

                    }

                    if (fieldType.equals("Float") && tw.isFloat(fieldValueString) == false) {
                        showMessageDialog(null, "Invalid Type. The requested is Float");

                    }

                    if (fieldType.equals("String") && tw.isString(fieldValueString) == false) {
                        showMessageDialog(null, "Invalid Type. The requested is String");

                    }
                    if (fieldType.equals("Date") && tw.isDate(fieldValueString) == false) {
                        showMessageDialog(null, "Invalid Type. The requested is Date");
                    }

                    boolean equalsOperator=false;
                    if(operatorSelected.equals("="))
                    {
                        equalsOperator=true; //Megnezi hogy whereben = vagy != feltetel van
                    }

                    //TODO: Ide jon a mongoDB-s delete resze!
                    String operator="";
                    if(equalsOperator){
                        operator=operator.concat("=");
                    }else{
                        operator=operator.concat("<>");
                    }
                    String field=fieldName.split(" ")[0];
                    String sendmsg="DELETE ".concat(field+"#"+collectionName+"#"+databaseName+"#"+fieldValueString+"#"+operator);
                    ch.setMsg(sendmsg);
                    ch.sendMsg();

                }
            }
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

}
