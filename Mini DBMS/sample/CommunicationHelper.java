package sample;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class CommunicationHelper {
    private String host = "localhost";
    private int port=6969;
    private String msg="";
    private Socket s;

    public void setHost(String h){
        host=h;
    }

    public void setPort(int p){
        port=p;
    }

    public void setMsg(String m){
        msg=m;
    }

    public String getHost(){
        return host;
    }

    public int getPort(){
        return port;
    }

    public String getMsg(){
        return msg;
    }


    public void openSocket(){
        try {
            s = new Socket(host, port);
        }catch(Exception e){
            System.out.println("Error opening socket!");
        }
    }

    public void closeSocket(){
        try {
            s.close();
        }catch(Exception e){
            System.out.println("Error closing socket!");
        }
    }

    public void sendMsg(){
        openSocket();
        try {
            PrintWriter pr = new PrintWriter(s.getOutputStream());
            String send = msg;
            pr.println(send);
            //System.out.println("Client:" + send);
            pr.flush();
        }catch(Exception e){
            System.out.println("Error sending message!");
        }
        closeSocket();
    }

    public String receiveMsg() {
        openSocket();
        try {
            PrintWriter pr = new PrintWriter(s.getOutputStream());
            String send = msg;
            pr.println(send);
            pr.flush();
            InputStreamReader in = new InputStreamReader(s.getInputStream());
            BufferedReader bf = new BufferedReader(in);
            msg = bf.readLine();

        } catch (Exception e) {
            System.out.println("Error receiving message!");
        }
        closeSocket();
        return msg;
    }
}
