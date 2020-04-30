package sample;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import java.io.File;

public class XMLParser {
    //jelenleg az argumentum az adatbazis neve
    public int create(String arg){
        try{
            //dokumentumepitok es dokumentum inicializalasa
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.newDocument();

            //root(Database) element
            Element rootElement = doc.createElement("Database");
            doc.appendChild(rootElement);
            Attr attr = doc.createAttribute("DBName");
            attr.setValue(arg);
            rootElement.setAttributeNode(attr);

            //tables element
            Element tablesElement = doc.createElement("Tables");
            rootElement.appendChild(tablesElement);

            //xml fajl gyartasa (jelenleg C:\\ -re)
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);

            File xml_file_path=new File("C:\\ABKR\\"+arg);
            if (xml_file_path.mkdir()) System.out.println("Directory created");
            else System.out.println("Directory not created(exists?)");

            StreamResult result = new StreamResult("C:\\ABKR\\"+arg+"\\"+arg+".xml");
            transformer.transform(source, result);

            //konzolra vetites tesztelesre (kesobb hanyagolhato)
            StreamResult consoleResult = new StreamResult(System.out);
            transformer.transform(source, consoleResult);
        

        }catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public int addTable(String name,String filepath){
        try{
            File inputFile = new File(filepath);
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.parse(inputFile);
            Node db = doc.getFirstChild();
            Node tables = doc.getElementsByTagName("Tables").item(0);

            Element table = doc.createElement("Table");
            tables.appendChild(table);
            Attr attr = doc.createAttribute("TableName");
            attr.setValue(name);
            table.setAttributeNode(attr);

            //gyartas
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);

            StreamResult result = new StreamResult(filepath);
            transformer.transform(source, result);

            //konzolra vetites tesztelesre (kesobb hanyagolhato)
            StreamResult consoleResult = new StreamResult(System.out);
            transformer.transform(source, consoleResult);

        }catch (Exception e){
            e.printStackTrace();
        }
        return 0;
    }

    public int dropTable(String name,String filepath){
        try{
            File inputFile = new File(filepath);
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.parse(inputFile);


            NodeList tables = doc.getElementsByTagName("Table");

            for(int i=0;i<tables.getLength();i++){
               Node node = tables.item(i);
               Element elem = (Element) node;
               String tn = elem.getAttribute("TableName");
               if (tn.equals(name)) {
                    elem.getParentNode().removeChild(elem);
                }

            }


            //gyartas
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);

            StreamResult result = new StreamResult(filepath);
            transformer.transform(source, result);

            //konzolra vetites tesztelesre (kesobb hanyagolhato)
            StreamResult consoleResult = new StreamResult(System.out);
            transformer.transform(source, consoleResult);

        }catch (Exception e){
            e.printStackTrace();
        }
        return 0;
    }
}