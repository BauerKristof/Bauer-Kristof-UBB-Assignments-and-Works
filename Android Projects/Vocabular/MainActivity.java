package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    public static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void addNewWordActivity(View view) {
        Intent intent = new Intent(this, NewWordActivity.class);
        startActivity(intent);
    }

    public void addSearchActivity(View view) {
        Intent intent = new Intent(this, SearchActivity.class);
        startActivity(intent);
    }

    public void addCheckListActivity(View view) {
        Intent intent = new Intent(this, CheckListActivity.class);
        startActivity(intent);
    }

    public void RandomGameActivity(View view) {
        Intent intent = new Intent(this, RandomGameActivity.class);
        startActivity(intent);
    }
    public void Quit(View view) {
        finishAffinity();
        System.exit(0);
    }
    }
