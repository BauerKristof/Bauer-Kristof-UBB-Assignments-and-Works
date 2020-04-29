/*
Nev:Bauer Kristof
Csoport:521
Felhasznalo:bkim1790
*/

import java.io.*;
import java.net.*;
import java.util.*;
import java.text.*;

public class SMTP {
    public static void main(String args[]){
        Socket smtpSocket = null;
        DataOutputStream os = null;
        DataInputStream is = null;

        Date dDate = new Date();
        DateFormat dFormat = DateFormat.getDateInstance(DateFormat.FULL,Locale.US);

        try
        {
            smtpSocket = new Socket("localhost", 25);
            is = new DataInputStream(smtpSocket.getInputStream());
            os = new DataOutputStream(smtpSocket.getOutputStream());
            Scanner in = new Scanner(System.in);


            if(smtpSocket != null && os != null && is != null)
            {
                System.out.println("Connected to FakeSMTP");
                try
                {
                    System.out.println("Setting up the sender-reciver");
                    os.writeBytes("HELO\r\n");
                    os.writeBytes("MAIL From: <teszt@gmail.com>\r\n");
                    os.writeBytes("RCPT To: <forhim@gmail.com>\r\n");

                    System.out.println("What is your message for him?");
                    String messageToSend = in.nextLine();



                    System.out.println("\nSetting up the context");

                    os.writeBytes("DATA\r\n");
                    os.writeBytes("Date: " + dFormat.format(dDate) + "\r\n");
                    os.writeBytes("From: <teszt@gmail.com>\r\n");
                    os.writeBytes("To: <forhim@gmail.com>\r\n");
                    os.writeBytes("Subject: Teszt uzenet\r\n");
                    os.writeBytes("Message: "+messageToSend+"\r\n");
                    os.writeBytes("\r\n.\r\n");
                    os.writeBytes("QUIT\r\n");

                    String responseline;
                    while((responseline = is.readLine())!=null)
                    {
                        if(responseline.indexOf("Ok") != -1) {
                            System.out.println("Message recived");
                            break;
                        }
                    }
                } catch(Exception e) {
                System.out.println("ERROR: While sending the email");  }
            }
        } catch(Exception e) {
            System.out.println("ERROR: Wrong host");
        }
    }
}