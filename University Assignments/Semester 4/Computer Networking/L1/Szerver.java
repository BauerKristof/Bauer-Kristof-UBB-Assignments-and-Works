/*Nev:Bauer Kristof
Felhasznalo:bkim1790
Csoport:521
 */

import java.io.*;
import java.net.*;


class Szerver {



    public Szerver(int port) {
        try {
           /* szerverSocket = new ServerSocket(port);
            connectionSocket = szerverSocket.accept();

            kliensSocketUzenet = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
            valaszSocketUzenet = new DataOutputStream(connectionSocket.getOutputStream());



            while(true)
            {
                    beolvasottUzenet = kliensSocketUzenet.readLine();
                    System.out.println("Received: " + beolvasottUzenet);
                    kuldendoUzenet = beolvasottUzenet.toUpperCase() + '\n';
                    valaszSocketUzenet.writeBytes(kuldendoUzenet);
                    valaszSocketUzenet.flush();
            }*/

             ServerSocket szerverSocket= new ServerSocket(port);
             Socket connectionSocket;
             BufferedReader kliensSocketUzenet;
             DataOutputStream valaszSocketUzenet;
             String beolvasottUzenet = "";
             String kuldendoUzenet = "";

            while (!beolvasottUzenet.equals("exit")) {
                 connectionSocket = szerverSocket.accept();
                kliensSocketUzenet =
                        new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                valaszSocketUzenet = new DataOutputStream(connectionSocket.getOutputStream());

                beolvasottUzenet = kliensSocketUzenet.readLine();
                System.out.println("Kliens üzenete: " + beolvasottUzenet);
                kuldendoUzenet = beolvasottUzenet.toUpperCase() + '\n';
                valaszSocketUzenet.writeBytes(kuldendoUzenet);
            }
        }
        catch (IOException e)
        {
            System.out.println(e);
        }
    }

    public static void main(String args[])
    {
        Szerver szerver = new Szerver(5000);
    }

}