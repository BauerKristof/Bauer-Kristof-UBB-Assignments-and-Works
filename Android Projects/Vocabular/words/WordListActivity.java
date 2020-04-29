package com.example.vocabular.words;

import android.util.Log;


public class WordListActivity  {
    private String word;
    private String meaning;


    public void showMenu(int position)
    {
        Log.v("Context=",""+position);
    }

    public WordListActivity(String word, String meaning) {
        this.word = word;
        this.meaning = meaning;
    }

    public WordListActivity() {

    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public String getMeaning() {
        return meaning;
    }

    public void setMeaning(String meaning) {
        this.meaning = meaning;
    }

    @Override
    public String toString() {
        return "WordListActivity{" +
                "word='" + word + '\'' +
                ", meaning='" + meaning + '\'' +
                '}';
    }
}
