package sample;

import java.net.*;
import java.io.*;
import java.util.Arrays;


public class server_wip{

    static MongoHelper mh = new MongoHelper();

    public void send(PrintWriter p,String s){
        p.println(s);
        p.flush();
    }

    private static String readDB(){
        StringBuilder lines= new StringBuilder();
        try {
            File curDatabases = new File("C:\\ABKR\\dbs.txt");
            BufferedReader abc = new BufferedReader(new FileReader(curDatabases));
            String line;
            while ((line = abc.readLine()) != null) {
                lines.append(line).append("#");
            }
            abc.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
        return lines.toString();
    }

    private static String readTables(String db){
        StringBuilder lines= new StringBuilder();
        try {
            File curTables = new File("C:\\ABKR\\"+db+"\\tables.txt");
            BufferedReader abc = new BufferedReader(new FileReader(curTables));
            String line;
            while ((line = abc.readLine()) != null) {
                lines.append(line).append("#");
            }
            abc.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
        return lines.toString();
    }

    private static String readFields(String info){ //table#db
        StringBuilder lines= new StringBuilder();
        try {
            String[] data = info.split("#");
            String tableNameString = data[0];
            String dbNameString = data[1];
            File curDatabases = new File("C:\\ABKR\\" + dbNameString + "\\" + tableNameString + ".txt");

            FileReader fr = new FileReader(curDatabases);
            BufferedReader abc = new BufferedReader(fr);
            String line;

            while ((line = abc.readLine()) != null) {
                lines.append(line).append("#");
            }
            abc.close();
            fr.close();
        }catch (Exception e){
            System.out.println(e);
        }
        return lines.toString();
    }

    private static boolean deleteDirectory(File file) { //rekurziv letorlese a directorynak
        File[] flist = null;

        if(file == null){
            return false;
        }

        if (file.isFile()) {
            return file.delete();
        }

        if (!file.isDirectory()) {
            return false;
        }

        flist = file.listFiles();
        if (flist != null && flist.length > 0) {
            for (File f : flist) {
                if (!deleteDirectory(f)) {
                    return false;
                }
            }
        }

        return file.delete();
    }

    public static void createDB(String name){
        XMLParser parser = new XMLParser();
        if (parser.create(name) == 0){
            System.out.println("Successfully created database(xml)");
        }
        else{
            System.out.println("Failed to create database(xml)");
        }
        try {
            File file = new File("C:\\ABKR\\dbs.txt");
            FileWriter fr = new FileWriter(file, true);
            BufferedWriter br = new BufferedWriter(fr);
            br.write(name + '\n'); //beiktatk AB-k koze
            br.close();
            fr.close();

            File newDB = new File("C:\\ABKR\\" + name);
            newDB.mkdir();
            File createTable = new File("C:\\ABKR\\" + name + "\\tables.txt");
            createTable.createNewFile();

        }catch(Exception e){
            System.out.println("Exception in creating db");
        }

    }

    public static void createTable(String table_diez_db){
        String[] data = table_diez_db.split("#");
        String tableName = data[0];
        String dbName = data[1];

        XMLParser parser = new XMLParser();
        String path = "C:\\ABKR\\"+dbName+"\\"+dbName+".xml";
        if (parser.addTable(tableName,path) == 0){
            System.out.println("Successfully created table(xml)");
        }
        else{
            System.out.println("Failed to create table(xml)");
        }
        try {

            File file = new File("C:\\ABKR\\" + dbName + "\\tables.txt");
            FileWriter fr = new FileWriter(file, true);
            BufferedWriter br = new BufferedWriter(fr);
            br.write(tableName + '\n'); //beiktatk Tabelek-k koze
            br.close();
            fr.close();

            File theTable = new File("C:\\ABKR\\" + dbName + "\\" + tableName + ".txt");
            theTable.createNewFile();
        }catch (Exception e){
            System.out.println("Exception in creating table");
        }
    }

    public static void dropDB(String name){
        File pathToBeDeleted = new File("C:\\ABKR\\"+name);
        boolean result = deleteDirectory(pathToBeDeleted);

        try {
            File databaseTextFile = new File("C:\\ABKR\\dbs.txt");
            File temp = File.createTempFile("dbstemp", ".txt", databaseTextFile.getParentFile());
            String charset = "UTF-8";
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(databaseTextFile), charset));
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(new FileOutputStream(temp), charset));

            String currentLine;

            while((currentLine = reader.readLine()) != null) {
                String trimmedLine = currentLine.trim();
                if(trimmedLine.equals(name)) continue;
                writer.write(currentLine + System.getProperty("line.separator"));
            }
            writer.close();
            reader.close();

            databaseTextFile.delete();
            temp.renameTo(databaseTextFile);
        }
        catch (IOException e)
        {
            System.out.println(e);
        }
    }

    public static void dropTable(String table_diez_db){

        String[] data = table_diez_db.split("#");
        String tableNameToRemove = data[0];
        String selectedDBName = data[1];

        XMLParser parser = new XMLParser();
        String path = "C:\\ABKR\\"+selectedDBName+"\\"+selectedDBName+".xml";
        if (parser.dropTable(tableNameToRemove,path) == 0){
            System.out.println("Successfully dropped table(xml)");
        }
        else{
            System.out.println("Failed to drop table(xml)");
        }


        try {
            //Removeolja a tabla text filet
            File tabletoBeDeleted = new File("C:\\ABKR\\" + selectedDBName + "\\" + tableNameToRemove + ".txt");
            tabletoBeDeleted.delete();
        }
        catch (Exception e) {
            System.out.println("Error at delete the table: "+e);
        }



        try{

            //Removeol a tables.txt adatbazisbol a tablat
            File databaseTextFile = new File("C:\\ABKR\\"+selectedDBName+"\\tables.txt");
            File temp = File.createTempFile("tablestemp", ".txt", databaseTextFile.getParentFile());
            String charset = "UTF-8";
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(databaseTextFile), charset));
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(new FileOutputStream(temp), charset));

            String currentLine;

            while((currentLine = reader.readLine()) != null) {
                String trimmedLine = currentLine.trim();
                if(trimmedLine.equals(tableNameToRemove)) continue;
                writer.write(currentLine + System.getProperty("line.separator"));
            }
            writer.close();
            reader.close();

            databaseTextFile.delete();
            temp.renameTo(databaseTextFile);
        }
        catch (IOException e)
        {
            System.out.println("Error at delete the table from tables.txt database: "+e);
        }
    }

    public static void addField(String fieldInfo){ //fname#type#tablename#dbname
        String[] data = fieldInfo.split("#");
        String fieldNameString = data[0];
        String fieldTypeString = data[1];
        String tableNameString = data[2];
        String dbNameString = data[3];
        String keyRestriction = data[4];
        String referencedTable = "";

        if (keyRestriction.equals("FK(ForeignKey)")) {
             referencedTable = data[5];
             String forwardData = data[3]+"#"+data[2]+"#"+data[5];
             mh.addRef(forwardData);
        }


        try {
            File writeFieldInTable = new File("C:\\ABKR\\" + dbNameString + "\\" + tableNameString + ".txt");
            FileWriter fr = new FileWriter(writeFieldInTable, true);
            BufferedWriter br = new BufferedWriter(fr);

            if(keyRestriction == null)
            {
                br.write(fieldNameString + " " + fieldTypeString + '\n'); //beiktatk a tablak koze
            }
            else {

                if (keyRestriction.equals("PK(PrimaryKey)")) {

                    File table = new File("C:\\ABKR\\" + dbNameString + "\\" + tableNameString + ".txt");
                    FileReader fr2=new FileReader(table);
                    BufferedReader br2=new BufferedReader(fr2);
                    StringBuffer sb=new StringBuffer();
                    String line;
                    while((line=br2.readLine())!=null)
                    {
                        String[] linesplit = line.split(" ");
                        if ((linesplit.length >= 3)&&(linesplit[2].equals("PK"))) {
                            System.out.println("Did not insert field. There is already a primary key field!");
                            return;
                        }
                    }
                    fr2.close();
                    br2.close();


                    br.write(fieldNameString + " " + fieldTypeString + " " + "PK" + '\n'); //beiktatk a tablak koze
                } else if (keyRestriction.equals("FK(ForeignKey)")) {


                    mh.index(fieldInfo);
                    br.write(fieldNameString + " " + fieldTypeString + " " + "FK" + " "+referencedTable+'\n'); //beiktatk a tablak koze
                } else if(keyRestriction.equals("Index")){

                    mh.index(fieldInfo);
                    br.write(fieldNameString + " " + fieldTypeString + " " + "Index" + '\n'); //beiktatk a tablak koze
                } else if (keyRestriction.equals("None")) {
                    br.write(fieldNameString + " " + fieldTypeString + '\n'); //beiktatk a tablak koze
                }
            }
            br.close();
            fr.close();
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    public static void removeField(String fieldInfo){

        String[] data = fieldInfo.split("#");
        String fieldName = data[0];
        String tableNameString = data[1];
        String dbNameString = data[2];

        String[] fieldNameData=fieldName.split(" ");
        if (fieldNameData.length==4){ //ha fk
            mh.dropRef(fieldNameData[3]+"#"+dbNameString+"#"+tableNameString); //referenced table, db, referencing table
        }


        try{
            //Removeol a tabla txtjebol a fieldet
            String path="C:\\ABKR\\"+dbNameString+"\\"+tableNameString+".txt";
            // System.out.println("path= "+path);
            File fieldTextFile = new File(path);
            File temp = File.createTempFile("tablefieldtemp", ".txt", fieldTextFile.getParentFile());

            System.out.println("*"+temp.toString());
            System.out.println("*"+fieldTextFile.toString());
            System.out.println("*"+fieldTextFile.getParentFile().toString());

            String charset = "UTF-8";
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(fieldTextFile), charset));
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(new FileOutputStream(temp), charset));

            String currentLine;

            while((currentLine = reader.readLine()) != null) {
                String trimmedLine = currentLine.trim();
                if(trimmedLine.equals(fieldName.trim())) continue;
                writer.write(currentLine + System.getProperty("line.separator"));
            }
            writer.close();
            reader.close();

            if(fieldTextFile.delete()) System.out.println("sikeresen torolve"); else System.out.println("nem tudtam torolni");
            temp.renameTo(fieldTextFile);
        }
        catch (IOException e)
        {
            System.out.println("Error at delete the table from tables.txt database: "+e);
        }

    }

    public static int getPK(String tableInfo){ //tablename#dbname
        String[] data = tableInfo.split("#");
        String tableNameString = data[0];
        String dbNameString = data[1];

        try {
            File table = new File("C:\\ABKR\\" + dbNameString + "\\" + tableNameString + ".txt");
            FileReader fr=new FileReader(table);
            BufferedReader br=new BufferedReader(fr);
            //StringBuffer sb=new StringBuffer();
            String line;
            int lineNr=0;
            while((line=br.readLine())!=null)
            {

                String[] linesplit = line.split(" ");
                if ((linesplit.length >= 3)&&(linesplit[2].equals("PK"))) {
                            fr.close();
                            br.close();
                            return lineNr;
                        }

                lineNr+=1;
            }
            fr.close();
            br.close();
            return -1;
        } catch (IOException e) {
            System.out.println(e);
        }
        return -1;
    }


    public static void main(String[] args){
        try {
            ServerSocket ss = new ServerSocket(6969);
            serverwhile:
            while (true) {

                Socket s = ss.accept();
                System.out.println("Client connected");
                InputStreamReader in = new InputStreamReader(s.getInputStream());
                PrintWriter pr = new PrintWriter(s.getOutputStream());
                BufferedReader bf = new BufferedReader(in);

                String receive = bf.readLine();
                System.out.println("Client: " + receive +"<end>");

                String[] command = receive.split(" ");

                outerswitch:
                switch (command[0].toUpperCase()){
                    case "EXIT" :
                        break serverwhile;
                    case "CREATE":
                        switch(command[1].toUpperCase()){
                            case "DATABASE":
                                createDB(command[2]);
                                mh.createDB(command[2]);
                                break outerswitch;
                            case "TABLE":
                                createTable(command[2]);
                                mh.createCol(command[2]);
                                break outerswitch;
                        }
                        break;
                    case "SENDDBS":
                        String dbs = readDB();
                        pr.println(dbs);
                        pr.flush();
                        break;
                    case "SENDTABLES":
                        String tables = readTables(command[1]);
                        pr.println(tables);
                        pr.flush();
                        break;
                    case "SENDFIELDS":
                        String fields = readFields(command[1]);
                        pr.println(fields);
                        pr.flush();
                        break;
                    case "SENDPK":
                        Integer pkindex = getPK(command[1]);
                        String pki=pkindex.toString();
                        pr.println(pki);
                        pr.flush();
                        break;
                    case "DROP":
                        switch(command[1].toUpperCase()){
                            case "DATABASE":
                                dropDB(command[2]);
                                mh.dropDB(command[2]);
                                break outerswitch;
                            case "TABLE":
                                dropTable(command[2]);
                                mh.dropCol(command[2]);
                                break outerswitch;
                        }
                    case "ADDFIELD":
                        addField(command[1]);
                        break;
                    case "REMOVEFIELD":
                        if (command.length==5) {
                            removeField(command[1]+" "+command[2]+" "+command[3]+" "+command[4]);
                            mh.remove(command[1]+" "+command[2]+" "+command[3]+" "+command[4]);
                        }
                        else {
                            removeField(command[1] + " " + command[2]);
                            mh.remove(command[1] + " " + command[2]);
                        }
                        break;
                    case "INSERT":

                        mh.insert(command[1]);
                        break;

                    case "DELETE":
                        mh.delete(command[1]);
                        break;

                    case "UNIQUEVALIDATE":
                        String isValidU=mh.isUnique(command[1]);
                        pr.println(isValidU);
                        pr.flush();
                        break;

                    case "FKVALIDATE":
                        String isValidFK=mh.isReference(command[1]);
                        pr.println(isValidFK);
                        pr.flush();
                        break;

                        //todo: possible problems: table crossreference(pointless?) ; multiple fks in one table referencing the same other table.(pointless, but problematic)
                    case "CHECKREF":
                        String refResponse=mh.canDrop(command[1]);
                        pr.println(refResponse);
                        pr.flush();
                        break;
                }

            }
        }catch(Exception e){
            System.out.println(e);
        }


    }
}