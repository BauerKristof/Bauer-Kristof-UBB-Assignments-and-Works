package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class fullText extends AppCompatActivity {

    private TextView wholeText;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_full_text);
        String text=getIntent().getStringExtra("selected_text");
        wholeText = (TextView) findViewById(R.id.inserttext);
        wholeText.setText(text);

    }

}
