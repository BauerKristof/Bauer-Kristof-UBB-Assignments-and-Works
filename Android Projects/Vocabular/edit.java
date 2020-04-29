package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.example.vocabular.Listener.SingleLineET;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

public class edit extends AppCompatActivity {

    private EditText insert;
    private String content;
    private boolean isword;
    private ArrayList<String> curList=new ArrayList<String>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit);
        insert=(EditText)findViewById(R.id.insert);
        insert.addTextChangedListener(new SingleLineET(insert));
        content=getIntent().getStringExtra("edit_text");
        isword=getIntent().getExtras().getBoolean("is_word");
        insert.setText(content);

    }

    public void saveContent(View view) {
        FileInputStream fis = null;

        //Get the file content
        try {
            if(isword) {
                fis = openFileInput("words.txt");
            }
            else {
                fis = openFileInput("meanings.txt");
            }
            InputStreamReader isr = new InputStreamReader(fis);
            BufferedReader br = new BufferedReader(isr);
            StringBuilder sb = new StringBuilder();
            String word;

            while ( (word = br.readLine()) != null)
            {
                sb.append(word).append("\n");
                curList.add(word);
            }

        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            if (fis != null)
            {
                try
                {
                    fis.close();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }

             }
        }


       //Change the file
        try
        {
            OutputStreamWriter fOut;
            if(isword) {
                 fOut = new OutputStreamWriter(openFileOutput("words.txt",MODE_PRIVATE));
            }
            else {
                fOut = new OutputStreamWriter(openFileOutput("meanings.txt", MODE_PRIVATE));
            }

            for(int i=0; i<curList.size();i++)
            {
                if(curList.get(i).equals(content))
                {
                    curList.set(i,insert.getText().toString());
                }
                fOut.write(curList.get(i)+"\n");
            }
            fOut.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        Toast.makeText(getBaseContext(),"The change was saved",Toast.LENGTH_SHORT).show();

        Intent intent=new Intent(this, CheckListActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

        intent.putExtra("edited_string",insert.getText().toString()+"\n");
        startActivity(intent);





    }

    public void reloadConent(View view) {
        insert.setText(content);
    }
}