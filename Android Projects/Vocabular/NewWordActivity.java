package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


import java.io.OutputStreamWriter;

//TODO VISSZAUGORJON A MAINBE

public class NewWordActivity extends AppCompatActivity {
    private EditText ed1;
    private EditText ed2;
    private Button save;
    private String word="",meaning="";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity__new_word);
        ed1 = (EditText) findViewById(R.id.edit1);
        ed2 = (EditText) findViewById(R.id.edit2);
        save = (Button) findViewById(R.id.button);

        ed1.addTextChangedListener(loginTextWatcher);
        ed2.addTextChangedListener(loginTextWatcher);
    }

    public void saveContent(View view)
    {
        save.setEnabled(false);
        try
        {
            OutputStreamWriter fOutW = new OutputStreamWriter(openFileOutput("words.txt", Context.MODE_APPEND));
            OutputStreamWriter fOutM = new OutputStreamWriter(openFileOutput("meanings.txt", Context.MODE_APPEND));


            String finalString = word + "\n";
            fOutW.write(finalString);
            fOutW.close();
            finalString = meaning + "\n";
            fOutM.write(finalString);
            fOutM.close();

            Toast.makeText(getBaseContext(),"The word-meaning pair is saved",Toast.LENGTH_SHORT).show();
            Intent intent=new Intent(this, MainActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private TextWatcher loginTextWatcher = new TextWatcher() {
        @Override
        public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

        }

        @Override
        public void onTextChanged(CharSequence charSequence, int i, int i1, int i2)
        {
           word = ed2.getText().toString().trim();
           meaning = ed1.getText().toString().trim();

            save.setEnabled(!word.isEmpty() && !meaning.isEmpty());
        }

        @Override
        public void afterTextChanged(Editable editable) {

        }
    };


}