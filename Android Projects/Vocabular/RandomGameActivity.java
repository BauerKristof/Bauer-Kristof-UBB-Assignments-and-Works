package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
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
import java.util.Random;

//TODO: NEM NYOMHAT ADDIG AZ OK-RA AMIG NEM VALASZTOTTA KI HOGY WORD VAGY MEANING
//TODO:WORD MEANING ELCSUSZAS


public class RandomGameActivity extends AppCompatActivity {

    private Button wordButton,meaningButton;
    private TextView title,theword,themeaning,showtext,yourguess,editanswer;
    private EditText guess;
    private int randomNumb,option=0;

    private ArrayList<String> szavak = new ArrayList<String>();
    private ArrayList<String> ertelmek = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_random_game);
        wordButton=(Button)findViewById(R.id.wordbutton);
        meaningButton=(Button)findViewById(R.id.meaningbutton);
        title=(TextView)findViewById(R.id.title);
        theword=(TextView)findViewById(R.id.theword);
        themeaning=(TextView)findViewById(R.id.themeaning);
        showtext=(TextView)findViewById(R.id.showtext);
        yourguess=(TextView)findViewById(R.id.yourguess);
        guess = (EditText) findViewById(R.id.guess);
        editanswer=(TextView)findViewById(R.id.idkid);
        getFileContents();
        showWord(wordButton);





    }


    public void finalDecision(View view)
    {
        String answer=guess.getText().toString().trim();

        if(option==1)
      {
          if(answer.compareToIgnoreCase(ertelmek.get(randomNumb)) == 0)
          {
            editanswer.setTextColor(Color.GREEN);
            editanswer.setText("Hooray! Your answer is correct!");

          }
          else
          {
              editanswer.setTextColor(Color.RED);
              editanswer.setText("Your answer is not correct!\n"+"The right answer is:" + ertelmek.get(randomNumb));

          }
          showWord(view);
      }
      else
        {
            if(answer.compareToIgnoreCase(szavak.get(randomNumb)) == 0)
            {
                editanswer.setTextColor(Color.GREEN);
                editanswer.setText("Hooray! Your answer is correct!");
            }
            else
            {
                editanswer.setTextColor(Color.RED);
                editanswer.setText("Your answer is not correct!\n"+"The right answer is:" + szavak.get(randomNumb));
            }
            showMeaning(view);
        }
    }

    public void showWord(View view)
    {
        meaningButton.setBackgroundColor(Color.TRANSPARENT);
        wordButton.setBackgroundColor(Color.GREEN);
        themeaning.setVisibility(View.INVISIBLE);
        theword.setVisibility(View.VISIBLE);

        if(szavak.isEmpty())
        {
            showtext.setText("Your word list is empty currently. Add new words to play");
            showtext.setTextColor(Color.RED);
            showtext.setVisibility(View.VISIBLE);


        }
        else
        {
            option=1;
            Random r = new Random();
            randomNumb=r.nextInt(szavak.size());
            showtext.setText(szavak.get(randomNumb));
            showtext.setVisibility(View.VISIBLE);
            showtext.setVisibility(View.VISIBLE);

        }

    }

    public void showMeaning(View view)
    {
        wordButton.setBackgroundColor(Color.TRANSPARENT);
        meaningButton.setBackgroundColor(Color.GREEN);
        theword.setVisibility(View.INVISIBLE);
        themeaning.setVisibility(View.VISIBLE);

        if(ertelmek.isEmpty())
        {
            showtext.setText("Your meaning list is empty currently. Add new words to play");
            showtext.setTextColor(Color.RED);

        }
        else
        {
            option=2;
            Random r = new Random();
            randomNumb=r.nextInt(ertelmek.size());

            showtext.setText(ertelmek.get(randomNumb));
            showtext.setVisibility(View.VISIBLE);
        }

    }

    private void getFileContents()
    {
        szavak.clear();
        ertelmek.clear();

        FileInputStream fisw = null;
        FileInputStream fism = null;

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
    }
}
