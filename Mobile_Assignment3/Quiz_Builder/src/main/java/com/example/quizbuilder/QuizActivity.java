package com.example.quizbuilder;

import androidx.annotation.ColorRes;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

public class QuizActivity extends AppCompatActivity {

    String correctAnswer = "";
    String yourName = "";
    int Score= 0;

    String Question, Answer;
    int QuizCounter = 1;
    int lineCounter = 0;
    int counter = 0;

    ArrayList<Object>question = new ArrayList<Object>();
    ArrayList<Object>answer = new ArrayList<Object>();
    Map<String,String> map = new HashMap<String,String>();

    private TextView QuestionTextView;
    private Button Answer1Button;
    private Button Answer2Button;
    private Button Answer3Button;
    private Button Answer4Button;
    private Button nextBtn;
    private LinearLayout linearLayoutQuiz;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_quiz);

        QuestionTextView = (TextView) findViewById(R.id.QuestionTextView);

        //Buttons
        Answer1Button = (Button) findViewById(R.id.Answer1Button);
        Answer2Button = (Button) findViewById(R.id.Answer2Button);
        Answer3Button = (Button) findViewById(R.id.Answer3Button);
        Answer4Button = (Button) findViewById(R.id.Answer4Button);
        nextBtn = (Button) findViewById(R.id.nextBtn);

        linearLayoutQuiz = (LinearLayout) findViewById(R.id.linearLayoutQuiz);

        Button buttons[] = {Answer1Button, Answer2Button, Answer3Button, Answer4Button};


        Bundle name = getIntent().getExtras();
        if (name != null) {
            yourName = name.getString("name");

        }
        ReadDelimitedFile();
        DisplayQAndA();

        Answer1Button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (Answer1Button.getText() == correctAnswer){
                    Answer1Button.setBackgroundColor(Color.GREEN);
                    Score++;
                }
                else{
                    Answer1Button.setBackgroundColor(Color.RED);
                }
            }
        });

        Answer2Button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (Answer2Button.getText() == correctAnswer){
                    Answer2Button.setBackgroundColor(Color.GREEN);
                    Score++;

                }
                else{
                    Answer2Button.setBackgroundColor(Color.RED);
                }
            }
        });

        Answer3Button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (Answer3Button.getText() == correctAnswer){
                    Answer3Button.setBackgroundColor(Color.GREEN);
                    Score++;
                }
                else{
                    Answer3Button.setBackgroundColor(Color.RED);

                }
            }
        });

        Answer4Button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (Answer4Button.getText() == correctAnswer){
                    Answer4Button.setBackgroundColor(Color.GREEN);
                    Score++;
                }
                else{
                    Answer4Button.setBackgroundColor(Color.RED);
                }
            }
        });

        nextBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                defaultOptionsView(buttons);
                DisplayQAndA();
                QuizCounter++;

                if (question.isEmpty()){
                    OpenScoreActivity();
                }
            }
        });
    }

    public void ReadDelimitedFile() {

        String eachLine = null;
        BufferedReader br = null;
        try {
            InputStream is = getResources().openRawResource(R.raw.assignment2_delimitedtext);
            br = new BufferedReader(new InputStreamReader(is));
            System.out.println("File in RAW is open");
            StringBuffer stringBuffer = new StringBuffer();

            while ((eachLine = br.readLine()) != null) {
                parseData(eachLine);
                lineCounter++;
            }
            is.close();
            System.out.println("File in RAW is closed");
        } catch (IOException e) {
            e.printStackTrace();
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    private void parseData(String string){

        int counter = 0;

        Scanner lineScanner = new Scanner(string);
        lineScanner.useDelimiter(",");
        while(lineScanner.hasNext()){

            Question = lineScanner.next();
            question.add(Question);

            Answer = lineScanner.next();
            answer.add(Answer);

            map.put(Question, Answer);

            System.out.println("This is the question: " + question + " This is the answer: " + answer);
        }
        lineScanner.close();

    }
    //https://knpcode.com/java-programs/how-to-read-delimited-file-in-java/

    public void DisplayQAndA(){
        //int counter = 0;

        long seed = System.nanoTime();
        Collections.shuffle(question, new Random(seed));
        //https://stackoverflow.com/questions/4228975/how-to-randomize-two-arraylists-in-the-same-fashion

        String questionAtIndex = question.get(0).toString();
        QuestionTextView.setText(questionAtIndex);

        correctAnswer = map.get(questionAtIndex);

        Button buttons[] = {Answer1Button, Answer2Button, Answer3Button, Answer4Button};

        Collections.shuffle(Arrays.asList(buttons), new Random(seed));
        System.out.println(correctAnswer);

        (Arrays.asList(buttons).get(0)).setText(correctAnswer);
        System.out.println(Arrays.asList(buttons).get(0));

        String incorrect;
        Collections.shuffle(answer, new Random(seed));

        for (int i=1; i<4;i++){
            incorrect = answer.get(i).toString();

            if (incorrect == correctAnswer){
                (Arrays.asList(buttons).get(i)).setText(answer.get(5).toString());
            }
            else {
                (Arrays.asList(buttons).get(i)).setText(incorrect);
            }

        }
        question.remove((question.get(counter)).toString());
    }

    private void defaultOptionsView(Button[] buttons){
            for (int i=0; i < buttons.length; i++){
                buttons[i].setBackgroundColor(Color.parseColor("#FF6200EE"));
            }

    }

    public void OpenScoreActivity(){
        Intent lastIntent = new Intent(this, YourScore.class);
        Bundle extras = new Bundle();

        extras.putInt("key", Score);
        extras.putString("name", yourName);

        lastIntent.putExtra("name", yourName);
        lastIntent.putExtra("key", Score);
        startActivity(lastIntent);
    }
}