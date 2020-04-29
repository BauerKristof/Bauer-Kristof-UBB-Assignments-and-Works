package com.example.vocabular.Listener;

import android.text.TextWatcher;
import android.widget.EditText;
import android.text.Editable;


public class SingleLineET implements TextWatcher {
    EditText et;

    public SingleLineET(EditText et){
        this.et = et;
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after) {

    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count) {
        String converted = s.toString();
        if(converted.contains("\n")){
            converted = converted.replace("\n", "");
            et.setText(converted);
            et.setSelection(et.getText().length());

        }
    }

    @Override
    public void afterTextChanged(Editable s) {
    }
}