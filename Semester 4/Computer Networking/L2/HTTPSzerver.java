/*Nev:Bauer Kristof
Azonosito:bkim1790
Csoport:521
 */

import java.net.ServerSocket;
import java.net.Socket;

public class HTTPSzerver {

    public static void main(String argv[]) throws Exception {

        ServerSocket szerverSocket = new ServerSocket(8080);
        System.out.println("A szerver elindult a 8080-as porton");

            while (true) {
                Socket kliensSocket = szerverSocket.accept();
                Thread szal = new KliensThread(kliensSocket);
                szal.start();
            }
        }
}