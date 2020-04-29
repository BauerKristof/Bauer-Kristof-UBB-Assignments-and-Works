package com.example.vocabular;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.MenuItem;
import android.view.View;
import android.widget.PopupMenu;
import android.widget.TextView;
import android.widget.Toast;

import com.example.vocabular.Listener.ClickListener;
import com.example.vocabular.Listener.RecyclerTouchListener;
import com.example.vocabular.adapters.WordsRecycleAdapter;
import com.example.vocabular.util.VerticalSpacingItemDecorator;
import com.example.vocabular.words.WordListActivity;



import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

public class CheckListActivity extends AppCompatActivity implements PopupMenu.OnMenuItemClickListener {

    //ui comp
    private RecyclerView mRecyclerView;
    //vars
    private ArrayList<WordListActivity> mWords = new ArrayList<>();
    private WordsRecycleAdapter mWordsRecyclerAdapter;
    private boolean helperb=true;
    private TextView helper;
    private int pos;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_check_list);
        mRecyclerView = findViewById(R.id.recyclerView);


        initRecyclerView();
        insertFakeNoteS();
    }


    public void showPopup(View v) {
        PopupMenu popup = new PopupMenu(this, v);
        popup.setOnMenuItemClickListener(this);
        popup.inflate(R.menu.popup_menu);
        popup.show();
    }

    @Override
    public boolean onMenuItemClick(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.item1:
                Intent intent = new Intent(this, fullText.class);
                intent.putExtra("selected_text", helper.getText());
                startActivity(intent);
                return true;
            case R.id.item2:
                intent=new Intent(this, edit.class);
                intent.putExtra("edit_text", helper.getText());
                intent.putExtra("is_word",helperb);
                startActivity(intent);
                String content=getIntent().getStringExtra("edited_string");
                helper.setText(content);

                mWordsRecyclerAdapter.notifyDataSetChanged();
                return true;

                case R.id.item3:
                mWords.remove(pos);
                mWordsRecyclerAdapter.notifyItemRemoved(pos);
                    try
                    {
                        OutputStreamWriter fOutW,fOutM;
                            fOutW = new OutputStreamWriter(openFileOutput("words.txt",MODE_PRIVATE));
                            fOutM = new OutputStreamWriter(openFileOutput("meanings.txt", MODE_PRIVATE));

                        for(int i=0; i<mWords.size();i++)
                        {
                            fOutW.write(mWords.get(i).getWord()+"\n");
                            fOutM.write(mWords.get(i).getMeaning()+"\n");

                        }
                        fOutW.close();
                        fOutM.close();
                    }
                    catch (Exception e)
                    {
                        e.printStackTrace();
                    }

                Toast.makeText(this, "The word-meaning pair is deleted", Toast.LENGTH_SHORT).show();
                return true;
            default:
                return false;
        }
    }
        private void initRecyclerView()
        {
            LinearLayoutManager linearLayoutManager = new LinearLayoutManager(this);
            mRecyclerView.setLayoutManager(linearLayoutManager);
            VerticalSpacingItemDecorator itemDecorator = new VerticalSpacingItemDecorator(10);
            mRecyclerView.addItemDecoration(itemDecorator);
            mWordsRecyclerAdapter=new WordsRecycleAdapter(mWords);
            mRecyclerView.setAdapter(mWordsRecyclerAdapter);



            mRecyclerView.addOnItemTouchListener(new RecyclerTouchListener(this, mRecyclerView, new ClickListener()
            {
                @Override
                public void onClick(View view, final int position)
                {

                   final TextView word=(TextView) view.findViewById(R.id.word);
                   final TextView meaning=(TextView) view.findViewById(R.id.meaning);


                    word.setOnClickListener(new View.OnClickListener()
                    {
                        @Override
                        public void onClick(View v)
                        {
                            word.setEllipsize(TextUtils.TruncateAt.MARQUEE);
                            word.setMarqueeRepeatLimit(1);
                            word.setFocusable(true);
                            word.setFocusableInTouchMode(true);
                            word.setHorizontallyScrolling(true);

                        }
                    });

                    meaning.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view)
                        {
                            meaning.setEllipsize(TextUtils.TruncateAt.MARQUEE);
                            meaning.setMarqueeRepeatLimit(1);
                            meaning.setFocusable(true);
                            meaning.setFocusableInTouchMode(true);
                            meaning.setHorizontallyScrolling(true);
                        }
                    });
                }

                @Override
                public void onLongClick(View view, int position)
                {
                    pos=position;

                    final TextView word=(TextView) view.findViewById(R.id.word);
                    final TextView meaning=(TextView) view.findViewById(R.id.meaning);

                    word.setOnLongClickListener(new View.OnLongClickListener() {
                        @Override
                        public boolean onLongClick(View view) {
                            helper=word;
                            helperb=true;
                            showPopup(word);
                                return false;
                        }
                    });

                    meaning.setOnLongClickListener(new View.OnLongClickListener() {
                        @Override
                        public boolean onLongClick(View view) {
                            helper=meaning;
                            helperb=false;
                            showPopup(meaning);
                            return false;
                        }
                    });

                }
            }));

        }



        private void insertFakeNoteS()
        {
            FileInputStream fisw = null;
            FileInputStream fism=null;

            try {
                fisw = openFileInput("words.txt");
                fism = openFileInput("meanings.txt");

                InputStreamReader isrw = new InputStreamReader(fisw);
                InputStreamReader isrm=new InputStreamReader(fism);

                BufferedReader brw = new BufferedReader(isrw);
                BufferedReader brm = new BufferedReader(isrm);

                StringBuilder sbw = new StringBuilder();
                StringBuilder sbm = new StringBuilder();


                String word;
                String meaning;

                while ( (word = brw.readLine()) != null)
                {
                    meaning = brm.readLine();
                    sbw.append(word).append("\n");
                    sbm.append(meaning).append("\n");
                    WordListActivity szopar = new WordListActivity();
                    szopar.setWord(word);
                    szopar.setMeaning(meaning);
                    mWords.add(szopar);
                }

                mWordsRecyclerAdapter.notifyDataSetChanged();


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
                if (fisw != null)
                {
                    try
                    {
                        fisw.close();
                    }
                    catch (IOException e)
                    {
                        e.printStackTrace();
                    }
                }
                else if (fism != null)
                {
                    try {
                        fism.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
}
