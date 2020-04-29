package com.example.vocabular.adapters;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.vocabular.R;
import com.example.vocabular.words.WordListActivity;

import java.util.ArrayList;

public class WordsRecycleAdapter extends RecyclerView.Adapter<WordsRecycleAdapter.ViewHolder> {
    private ArrayList<WordListActivity> mWords= new ArrayList<>();

    public WordsRecycleAdapter(ArrayList<WordListActivity> Words) {
        this.mWords = Words;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {

        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.layout_list_item, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        holder.word.setText(mWords.get(position).getWord());
        holder.meaning.setText(mWords.get(position).getMeaning());
    }

    @Override
    public int getItemCount() {
        return mWords.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
     TextView word,meaning;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            word=itemView.findViewById(R.id.word);
            meaning=itemView.findViewById(R.id.meaning);
        }
    }
}
