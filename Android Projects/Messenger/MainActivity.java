package com.example.android.messenger;

import android.content.Intent;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


import com.example.android.messenger.TopPicks.TopPicks;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.SimpleDateFormat;


import java.util.Date;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Random;


public class MainActivity extends AppCompatActivity {
    private TextView date1, date1b, busLine, recievedText;
    private EditText typedText;
    public HashMap<String, Integer> myHashMap=new HashMap<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        date1 = (TextView) findViewById(R.id.fakeDate3);
        date1b = (TextView) findViewById(R.id.fakeDate3b);
        busLine = (TextView) findViewById(R.id.fakeLinia3);
        recievedText = (TextView) findViewById(R.id.fakeText3);
        typedText = (EditText) findViewById(R.id.textReciever);
        loadMap();
    }

    private void loadMap() {
        try {
            File toRead = new File(getFilesDir(),"fileone");
            FileInputStream fis = new FileInputStream(toRead);
            ObjectInputStream ois = new ObjectInputStream(fis);

            myHashMap = (HashMap<String, Integer>) ois.readObject();

            ois.close();
            fis.close();
            //print All data in MAP
            for (Map.Entry<String, Integer> m : myHashMap.entrySet()) {
                Log.v("m.getKey()", m.getKey());
                Log.v("m.Value:", m.getValue().toString());
            }
        } catch (Exception e) {
            Log.v("ERROR Beolvas: ",e.toString());

        }
    }

    protected void saveData()
    {
        try {
            File fileOne = new File(getFilesDir(),"fileone");
            FileOutputStream fos = new FileOutputStream(fileOne);
            ObjectOutputStream oos = new ObjectOutputStream(fos);

            oos.writeObject(myHashMap);
            oos.flush();
            oos.close();
            fos.close();

            for (Map.Entry<String,Integer> entry : myHashMap.entrySet()) {
                String key = entry.getKey();
                Integer value = entry.getValue();
                Log.v("getKey()", key);
                Log.v("Value:", value.toString());
                // do stuff
            }
        } catch (Exception e) {
            Log.v("ERROR Kiir: ",e.toString());
        }
    }
    @Override
    protected void onPause() {
        saveData();
        super.onPause();


    }

    public void sendMessage(View view) {
        String currentDate = new SimpleDateFormat("MM-dd ", Locale.getDefault()).format(new Date());
        String currentTime = new SimpleDateFormat("h:mm aaa", Locale.getDefault()).format(new Date());
        date1.setText(currentDate + currentTime);
        date1b.setText(currentDate + currentTime);

        String typedLinie = typedText.getText().toString().trim();
        busLine.setText(typedLinie);


        String hour = new SimpleDateFormat("HH", Locale.getDefault()).format(new Date());
        String min = new SimpleDateFormat("mm", Locale.getDefault()).format(new Date());
        String day = new SimpleDateFormat("dd", Locale.getDefault()).format(new Date());

        int additionalMin = Integer.parseInt(min) + 46;
        int additionalHour = Integer.parseInt(hour);
        int additionalDay = Integer.parseInt(day);

        if (additionalMin >= 60) {
            additionalHour++;
            additionalMin -= 60;
        }

        if (additionalHour >= 24) {
            additionalHour -= 24;
            additionalDay++;
        }

        min = Integer.toString(additionalMin);
        hour = Integer.toString(additionalHour);
        day = Integer.toString(additionalDay);

        String finalDateFormat = new SimpleDateFormat("/MM/yyyy", Locale.getDefault()).format(new Date());

        Random rn = new Random();
        int range = 999999 - 111111 + 1;
        int randomNum = rn.nextInt(range) + 111111;

        String returnMessage = "Biletul pentru linia " + typedLinie + " a fost activat. Valabil pana la " + hour + ":" + min + " in " + day + finalDateFormat + ". Cost total:0.60 EUR+Tva. Cod confirmare:" + randomNum;
        recievedText.setText(returnMessage);
        Toast.makeText(getBaseContext(), "The message has been sent!", Toast.LENGTH_SHORT).show();


       if(myHashMap.containsKey(typedLinie))
       {
           myHashMap.put(typedLinie, myHashMap.get(typedLinie) + 1);

       }
       else
        {
           myHashMap.put(typedLinie,1);
        }
    }

    public void topPicksActivity(View view)
    {
        Intent intent = new Intent(this, TopPicks.class);
        intent.putExtra("myHashMap", myHashMap);
        startActivity(intent);
    }

    public void exitButton(View view)
    {
        saveData();
        finish();

    }

}
