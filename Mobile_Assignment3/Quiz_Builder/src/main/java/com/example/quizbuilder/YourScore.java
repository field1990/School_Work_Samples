package com.example.quizbuilder;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class YourScore extends AppCompatActivity {

    private TextView FinalScore;
    private Button PlayAgainBtn;
    private TextView yourNameId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_your_score);

        FinalScore = (TextView) findViewById(R.id.FinalScore);
        yourNameId = (TextView) findViewById(R.id.yourNameId);
        PlayAgainBtn = (Button) findViewById(R.id.PlayAgainBtn);

        Bundle extras = getIntent().getExtras();
        int Score = 0;
        if (extras != null) {
            Score = extras.getInt("key");

        }

        Bundle name = getIntent().getExtras();
        String yourName = "";
        if (name != null) {
            yourName = name.getString("name");
        }

        yourNameId.setText(yourName);

        FinalScore.setText(Score + "/10");

        PlayAgainBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               newQuizBuilder();
            }
        });
    }

    public void newQuizBuilder(){
        Intent newQuiz = new Intent(this, QuizActivity.class);
        Bundle name = new Bundle();
        name.putString("name", yourNameId.getText().toString());

        startActivity(newQuiz);
    }
}