package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

//TODO VISSZAUGORJON A MAINBE
//EGYBEHOZNI A SZOVEGET

public class SearchActivity extends AppCompatActivity {

    private EditText ed1;
    private EditText ed2;
    private Button save;
    private String word = "", meaning = "";
    private TextView themeaning, theword,typedmeaning,typedword;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        ed1 = (EditText) findViewById(R.id.edit1);
        ed2 = (EditText) findViewById(R.id.edit2);
        save = (Button) findViewById(R.id.button);
        themeaning = (TextView) findViewById(R.id.themeaning);
        theword = (TextView) findViewById(R.id.theword);
        typedmeaning = (TextView) findViewById(R.id.typedmeaning);
        typedword= (TextView) findViewById(R.id.typedword);





    }

    public void searchForTheWord(View view) {
        FileInputStream fisw = null;
        FileInputStream fism = null;
        ArrayList<String> szavak = new ArrayList<String>();
        ArrayList<String> ertelmek = new ArrayList<String>();

        try {
            fisw = openFileInput("words.txt");
            fism = openFileInput("meanings.txt");

            InputStreamReader isrw = new InputStreamReader(fisw);
            InputStreamReader isrm = new InputStreamReader(fism);

            BufferedReader brw = new BufferedReader(isrw);
            BufferedReader brm = new BufferedReader(isrm);

            StringBuilder sbw = new StringBuilder();
            StringBuilder sbm = new StringBuilder();


            String beolvasszo, beolvasertelem;

            while ((beolvasszo = brw.readLine()) != null) {
                beolvasertelem = brm.readLine();
                szavak.add(beolvasszo.toString());
                ertelmek.add(beolvasertelem.toString());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fisw != null) {
                try {
                    fisw.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else if (fism != null) {
                try {
                    fism.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        word = ed2.getText().toString().trim();
        meaning = ed1.getText().toString().trim();


        if (!word.isEmpty()) {

            themeaning.setVisibility(View.VISIBLE);
            int i=0;


            while(i<szavak.size())
            {
                if(word.compareToIgnoreCase(szavak.get(i)) == 0)
                {

                typedword.setText(ertelmek.get(i));
                typedword.setVisibility(View.VISIBLE);
                break;
                }
                i++;
            }
            if(i>=szavak.size())
            {
                typedword.setText("Not found");
                typedword.setVisibility(View.VISIBLE);
            }


        }
        if (!meaning.isEmpty()) {

            theword.setVisibility(View.VISIBLE);
            int i=0;
            while(i<ertelmek.size())
            {
                if(meaning.compareToIgnoreCase(ertelmek.get(i)) == 0)
                {

                    typedmeaning.setText(szavak.get(i));
                    typedmeaning.setVisibility(View.VISIBLE);
                    break;
                }
                i++;
            }
            if(i>=ertelmek.size()) {
                typedmeaning.setText("Not found");
                typedmeaning.setVisibility(0);
            }

        }

    }
}