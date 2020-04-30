package sample;

import com.mongodb.*;
import com.mongodb.MongoClient;
import com.mongodb.client.*;
import com.mongodb.client.model.Indexes;
import org.bson.Document;

public class MongoHelper {

    private MongoClientURI uri;
    private MongoClient mongoClient;

    public MongoHelper() {
        uri = new MongoClientURI(
                "mongodb+srv+deleteforsavetyreasonsretryWrites=true&w=majority");
        mongoClient = new MongoClient(uri);

    }

    public void createDB(String name) {
        MongoDatabase db = mongoClient.getDatabase(name);
        db.createCollection("ref");
    }

    public void dropDB(String name) {
        MongoDatabase db = mongoClient.getDatabase(name);
        db.drop();
    }

    public void createCol(String info) { //table#db
        String[] data = info.split("#");
        String tableName = data[0];
        String dbName = data[1];
        MongoDatabase db = mongoClient.getDatabase(dbName);
        db.createCollection(tableName);
    }

    public void dropCol(String info) {
        String[] data = info.split("#");
        String tableName = data[0];
        String dbName = data[1];
        MongoDatabase db = mongoClient.getDatabase(dbName);
        MongoCollection col = db.getCollection(tableName);
        col.drop();

        //referenciak droppolasa
        MongoCollection refCol=db.getCollection("ref"); //ez lehet nem teljesen okes
        for (Object o : refCol.find()) {
            Document temp = (Document) o;
            //System.out.println("stringed object: "+temp.toString());
            if (temp.toString().contains("="+tableName)){
                refCol.deleteOne(temp);
            }
            }

    }

    public void insert(String info) {
        String[] path = info.split("#");
        String tablename = path[0];
        String dbname = path[1];
        String[] vals = path[2].split("%");
        String[] names = path[3].split("%");
        MongoDatabase db = mongoClient.getDatabase(dbname);
        MongoCollection col = db.getCollection(tablename);
        Document doc = new Document();
        for (int i = 0; i < vals.length; i++) {
            doc = doc.append(names[i], vals[i]);
        }
        col.insertOne(doc);
    }

    public void remove(String info) {
        String[] data = info.split("#");
        String fieldname = data[0].split(" ")[0].trim();
        String tablename = data[1];
        String dbname = data[2];
        MongoDatabase db = mongoClient.getDatabase(dbname);
        MongoCollection col = db.getCollection(tablename);

        String fieldvalue = null;
        for (Object o : col.find()) {
            Document temp = (Document) o;
            fieldvalue = (String) temp.get(fieldname);
            if (fieldvalue != null) {
                break;
            }
            //System.out.println("value="+fieldvalue);
            //System.out.println(temp.toString());
        }

        Document doc = new Document().append(fieldname, fieldvalue);
        //System.out.println("Fieldname="+fieldname);
        col.updateMany(doc, new Document().append("$unset", new Document().append(fieldname, "")));


    }

    public void delete(String info) {
        String[] data = info.split("#");
        String fieldname = data[0];
        String tablename = data[1];
        String dbname = data[2];
        String value = data[3];
        String op = data[4];

        MongoDatabase db = mongoClient.getDatabase(dbname);
        MongoCollection col = db.getCollection(tablename);

        if (op.equals("=")) {
            //System.out.println("az equals agon vagyok");
            //System.out.println("az operatorom: "+op);

            Document del = new Document().append(fieldname, value);
            col.deleteMany(del);
        } else {
            //System.out.println("a nem equals agon vagyok");
            //System.out.println("az operatorom: "+op);
            Document upperdel = new Document().append("$ne", value);
            Document del = new Document().append(fieldname, upperdel);
            col.deleteMany(del);
        }
    }

    public void index(String fieldInfo) {
        String[] data = fieldInfo.split("#");
        String fieldNameString = data[0];
        String fieldTypeString = data[1];
        String tableNameString = data[2];
        String dbNameString = data[3];
        String keyRestriction = data[4];

        MongoDatabase db = mongoClient.getDatabase(dbNameString);
        MongoCollection col = db.getCollection(tableNameString);

        col.createIndex(Indexes.descending(fieldNameString));
    }

    public String isUnique(String info) {
        String[] data = info.split("#");
        String dbNameString = data[0];
        String tableNameString = data[1];
        String fieldNameString = data[2];
        String fieldValueString = data[3];

        MongoDatabase db = mongoClient.getDatabase(dbNameString);
        MongoCollection col = db.getCollection(tableNameString);

        for (Object o : col.find()) {
            Document temp = (Document) o;
            String val = (String) temp.get(fieldNameString);
            if (val.equals(fieldValueString)) {
                return "0";
            }
        }
        return "1";
    }

    public String isReference(String info) {
        String[] data = info.split("#");
        String dbNameString = data[0];
        //String tableNameString = data[1];
        //String fieldNameString = data[2];
        String fieldValueString = data[3];
        String referencedTable = data[4];

        MongoDatabase db = mongoClient.getDatabase(dbNameString);
        //MongoCollection col = db.getCollection(tableNameString);
        MongoCollection referenced = db.getCollection(referencedTable);


        for (Object o : referenced.find()) {
            Document temp = (Document) o;
            String val = temp.get("_id").toString();
            if (val.equals(fieldValueString)) {
                return "1";
            }
        }
        return "0";

    }

    public void addRef(String data) {
        String[] dataSplit = data.split("#");
        String dbName = dataSplit[0];
        String referencingTable = dataSplit[1];
        String referencedTable = dataSplit[2];

        MongoDatabase db = mongoClient.getDatabase(dbName);
        MongoCollection refCol = db.getCollection("ref");
        Document doc = new Document();
        doc.append(referencedTable, referencingTable);
        refCol.insertOne(doc);

    }

    public String canDrop(String data) {
        String[] dataSplit = data.split("#");
        String tableName = dataSplit[0];
        String dbName = dataSplit[1];

        MongoDatabase db = mongoClient.getDatabase(dbName);
        MongoCollection refCol = db.getCollection("ref");
        String response = "";

        for (Object o : refCol.find()) {
            Document temp = (Document) o;
            Object val = temp.get(tableName);
            if (val!=null) {
                response += (val.toString() + "#");
            }
        }
        if (response.equals("")) return "%canDrop%";
        return response;
    }

    public void dropRef(String data){
        //referenced table, db, referencing table
        String[] dataSplit = data.split("#");
        String referencedTable = dataSplit[0];
        String dbName = dataSplit[1];
        String referencingTable = dataSplit[2];

        MongoDatabase db = mongoClient.getDatabase(dbName);
        MongoCollection refCol = db.getCollection("ref");

        Document del = new Document().append(referencedTable, referencingTable);
        refCol.deleteOne(del); //deletemany?

    }
}



