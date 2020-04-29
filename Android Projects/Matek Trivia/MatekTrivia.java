package com.example.android.matektrivia;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


import java.util.Random;

public class MatekTrivia extends AppCompatActivity {


    int kerdes=1;
    int pont=0;
    int i=0;

    String[] foKerdes = new String[]{"sin^2(x)+cos^2(x)=", "tg(x)=", "sin előjele 1. negyedben","sin előjele 2. negyedben","sin előjele 3. negyedben","sin előjele 4. negyedben",
            "cos előjele 1. negyedben","cos előjele 2. negyedben","cos előjele 3. negyedben","cos előjele 4. negyedben","tg/ctg előjele 1. negyedben","tg/ctg előjele 2. negyedben","tg/ctg előjele 3. negyedben","tg/ctg előjele 4. negyedben",
            "sin 0=","sin π/2=","sin π=", "sin 3π/2=", "sin 2π=","cos 0=","cos π/2=","cos π=", "cos 3π/2=", "cos 2π=",
            "sin(-x)=","cos(-x)=","tg(-x)=","ctg(-x)=","A sin es cos periódusa ?π","A tg/ctg periódusa ?π",
            "sin(a+b)=","sin(a-b)=","cos(a+b)=","cos(a-b)=","tg(a+b)=","tg(a-b)=","ctg(a+b)=","ctg(a-b)=",
            "sin2a=","A cos2a első formája=","A cos2a második formája=","A cos2a harmadik formája=","tg2a=","ctg2a=","sin3a/cos3a = sin/cos(?)",
            "A cos^2(a) felezési képlete=", "A sin^2(a) felezési képlete=","sina+sinb=","sina-sinb=","cosa+cosb=","cosa-cosb=","tga+tgb=","ctga+ctgb=",
            "sina*cosb=","sina*sinb=","cosa*cosb=","arcsin(-x)=","sin(arcsinx)=","arcsin(sinx)="};




    String[] foValasz = new String[]{"1","1/ctgx","+","+","-","-","+","-","-","+","+","-","+","-","0","1","0","-1","0","1","0","-1","0","1","-sinx","cosx","-tgx","-ctgx","2k","k",
            "sina*cosb+cosa*sinb","sina*cosb-cosa*sinb","cosa*cosb-sina*sinb","cosa*cosb-sina*sinb","(tga+tgb)/(1-tga*tgb)","(tga-tgb)/(1+tga*tgb)","(ctga*ctg-1)/(ctg+ctga)","ctga*ctgb+1)/(ctgb-ctga)",
            "2*sina*cosa","cos^a-sin^a","1-sin^2a","2cos^2a-1","(2tga)/(1-tg^2a)","(ctg^a-1)/(2ctga)","a+2a",
            "(1+cos2a)/2","(1-cos2a)/2","2*sin(a+b/2)*cos(a-b/2)","2*sin(a-b/2)*cos(a+b/2)","2*cos(a+b/2)*cos(a-b/2)","2*sin(a+b/2)+cos(b-a/2)","(sin(a+b))/(cosa*cosb)","(sin(b+a))/(sina*sinb)",
            "1/2*(sin(a+b)+sin(a-b))","1/2*(cos(a-b)-cos(a+b))","1/2*(cos(a-b)+cos(a+b))",
            "-arcsinx","x","x"};




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_matek_trivia);


         TextView kerdesTextview = (TextView) findViewById(R.id.keplet);
         TextView kerdesek=(TextView) findViewById(R.id.kerdessz);
         TextView pontszam=(TextView) findViewById(R.id.pontsz);




        kerdesek.setText(""+kerdes);
        pontszam.setText(""+pont);


        Random rand = new Random();
        i = rand.nextInt(57) + 1;
        kerdesTextview.setText(""+foKerdes[i]);

    }


    public String GetMessage() {
        EditText valami = (EditText) findViewById(R.id.valasz);
        String message = valami.getText().toString();
        return message;
    }


    public void ellenoriz()
    {
        TextView kerdesek=(TextView) findViewById(R.id.kerdessz);
        TextView pontszam=(TextView) findViewById(R.id.pontsz);
        TextView helyesvalasz=(TextView) findViewById(R.id.helyesvalasz);

        String valasz=GetMessage();
        if (valasz.contains(foValasz[i]))
        {
            pont++;
            pontszam.setText(""+pont);
            helyesvalasz.setTextColor(Color.GREEN);
            helyesvalasz.setText(""+"A válaszod helyes!");

        }
        else
        {
            helyesvalasz.setTextColor(Color.RED);
            helyesvalasz.setText(""+"A válaszod hibás"+"\n"+foKerdes[i]+foValasz[i]);
        }
        kerdes++;
        kerdesek.setText(""+kerdes);

    }

    public void tovabbiKerdes(View view) {
        TextView kerdesTextview = (TextView) findViewById(R.id.keplet);
        ellenoriz();
        Random rand = new Random();
        i = rand.nextInt(57) + 1;
       kerdesTextview.setText(""+foKerdes[i]);



    }

}