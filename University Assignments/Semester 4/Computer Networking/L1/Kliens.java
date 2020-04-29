/*Nev:Bauer Kristof
Felhasznalo:bkim1790
Csoport:521
 */

import java.io.*;
import java.net.*;

class Kliens {

    private Socket kliensoldaliSocket = null;
    private BufferedReader terminalSzoveg = null;
    private DataOutputStream elkuldendoUzenet;
    private BufferedReader kapottUzenet = null;

    public Kliens(String address, int port){
        try {
           System.out.println("Kliens letrehozva");
            kliensoldaliSocket = new Socket(address, port);
            System.out.println("Kliens csatlakozva a sockethez");
            terminalSzoveg = new BufferedReader(new InputStreamReader(System.in));
            elkuldendoUzenet = new DataOutputStream(kliensoldaliSocket.getOutputStream());
            kapottUzenet = new BufferedReader(new InputStreamReader(kliensoldaliSocket.getInputStream()));
        } catch (UnknownHostException u) {
            System.out.println(u);
        } catch (IOException i) {
            System.out.println(i);
        }

         try{

             String sentence = terminalSzoveg.readLine();
             elkuldendoUzenet.writeBytes(sentence + '\n');
             String modifiedSentence = kapottUzenet.readLine();
             System.out.println("Szerver uzenet: " + modifiedSentence);
             kliensoldaliSocket.close();
         }

         catch (IOException e)
         {
             System.out.println(e);
         }



    }

    public static void main(String argv[]){
        Kliens client = new Kliens("127.0.0.1", 5000);
    }
}