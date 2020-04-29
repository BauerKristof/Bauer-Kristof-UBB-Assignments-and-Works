package com.example.android.messenger.TopPicks;

import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;


import com.example.android.messenger.R;

import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Created by Kristof on 12/27/2019.
 */

public class TopPicks  extends AppCompatActivity{
    private HashMap<String,Integer> hashMap=new HashMap<>();
    private TextView bus0,used0,bus1,used1;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.toppicks_activity);
        bus0 = (TextView) findViewById(R.id.bus0);
        used0=(TextView) findViewById(R.id.used0);
        bus1 = (TextView) findViewById(R.id.bus1);
        used1=(TextView) findViewById(R.id.used1);

        Intent intent = getIntent();
         hashMap = (HashMap<String, Integer>)intent.getSerializableExtra("myHashMap");


        HashMap <String,Integer> sortedMap=sortByValue(hashMap);
        for (Map.Entry<String,Integer> entry : sortedMap.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            Log.v("key:",key);
            Log.v("value",value.toString());
        }

        Set<Map.Entry<String,Integer>> mapValues = sortedMap.entrySet();
        int maplength = mapValues.size();
        Map.Entry<String,Integer>[] test = new Map.Entry[maplength];
        mapValues.toArray(test);

        bus0.setText(test[maplength -1].getKey());
        used0.setText(test[maplength-1].getValue().toString());
        bus1.setText(test[maplength -2].getKey());
        used1.setText(test[maplength-2].getValue().toString());
    }

    public static HashMap<String, Integer> sortByValue(HashMap<String, Integer> hm)
    {
        List<Map.Entry<String, Integer> > list =
                new LinkedList<Map.Entry<String, Integer> >(hm.entrySet());

        Collections.sort(list, new Comparator<Map.Entry<String, Integer> >() {
            public int compare(Map.Entry<String, Integer> o1,
                               Map.Entry<String, Integer> o2)
            {
                return (o1.getValue()).compareTo(o2.getValue());
            }
        });

        HashMap<String, Integer> temp = new LinkedHashMap<String, Integer>();
        for (Map.Entry<String, Integer> aa : list) {
            temp.put(aa.getKey(), aa.getValue());
        }
        return temp;
    }

}