/*Nev:Bauer Kristof
Azonosito:bkim1790
Csoport:521
 */

import java.io.*;
import java.net.Socket;


public class KliensThread extends Thread {

    private Socket kapcsolat;
    private long contentlength=0;



    public KliensThread(Socket kapcsolat){

        this.kapcsolat =kapcsolat;


        System.out.println();
        System.out.println("Elindult a kliens szal");
    }

    public void run()
    {

        try {
            this.kapcsolat.setSoTimeout(15 * 1000);

            while (true) {
                try {
                    BufferedReader parancs = new BufferedReader(new InputStreamReader(kapcsolat.getInputStream()));
                    DataOutputStream valasz = new DataOutputStream(kapcsolat.getOutputStream());

                    String keres = parancs.readLine();
                    if (keres != null) {
                        System.out.println("Szal:" + keres);

                        String adatok[] = keres.split(" ");
                        String fajlUtvonal = adatok[1].substring(1);
                        System.out.println("Fajlutvona: " + fajlUtvonal);


                        File file = new File(fajlUtvonal);

                        if (!file.exists()) {
                            System.out.println("Nincs ilyen file");
                            sendNotFound(valasz);
                            valasz.close();
                            return;
                        }

                        contentlength = file.length();

                        FileInputStream msgChannel = new FileInputStream(file);

                        sendHeader(valasz);
                        sendFile(valasz, file);
                        writeDatas(msgChannel, valasz);
                    }

                } catch (Exception e) {
                    System.out.println("HIBA:A fajlal kapcsolatos adatok hibasak!");
                    e.printStackTrace();
                }
            }
        }
        catch (Exception e)
        {
            //e.printStackTrace();
            try {
                kapcsolat.close(); //kitimeoutol
            }
            catch (Exception e2)
            {
                e2.printStackTrace();
            }
        }
    }


    private void sendHeader(DataOutputStream output) {
        PrintStream out = new PrintStream(output);
        out.println("HTTP/1.0 200 OK");
        out.println("MIME_version:1.0");
        out.println("Content-length:"+contentlength);
    }
    private void sendFile(DataOutputStream valaszStream, File file) throws IOException{

        String tipus = file.getName().substring(file.getName().lastIndexOf(".") + 1);
        System.out.println("Fajl tipua= "+tipus);

        if (tipus.equals("html")) {
            valaszStream.writeBytes("Content type:text/html\n\n");
        }

        if (tipus.equals("css")) {
            valaszStream.writeBytes("Content type:text/css\n\n");
        }

        if (tipus.equals("txt")) {
            valaszStream.writeBytes("Content type:plain/text\n\n");
        }

        if (tipus.equals("png")) {
            valaszStream.writeBytes("Content type:image/png\n\n");
        }

        if (tipus.equals("jpg")) {
            valaszStream.writeBytes("Content type:image/jpg\n\n");
        }
        if (tipus.equals("jpeg")) {
                valaszStream.writeBytes("Content type:image/jpeg\n\n");
        }
        if (tipus.equals("gif")) {
            valaszStream.writeBytes("Content type:image/gif\n\n");
        }

        if (tipus.equals("swf")) {
            valaszStream.writeBytes("Content type:application/x-shockwave-flash\n\n\n");
        }
        if (tipus.equals("avi")) {
                valaszStream.writeBytes("Content type:video/x-msvideo\n\n");
        }


    }

    private void sendNotFound(DataOutputStream output) {
        PrintStream out = new PrintStream(output);
        out.println("HTTP/1.0 404 Not Found");
        out.println("");
        out.println("Error 404:Not found");
    }

    private void writeDatas(FileInputStream msgChannel,DataOutputStream valaszStream) throws IOException
    {
        int size;
        byte[] data = new byte[5000];

        while ((size = msgChannel.read(data)) != -1) {
            valaszStream.write(data, 0, size);
        }

       // msgChannel.close();
       // valaszStream.close();
    }
}
