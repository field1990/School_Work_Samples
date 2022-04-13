package com.example.quizbuilder;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

//import java.io.File;
//import java.util.Scanner;

public class MainActivity extends AppCompatActivity {

    private EditText editPersonName;
    private Button StartButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StartButton = (Button) findViewById(R.id.StartButton);
        editPersonName = (EditText) findViewById(R.id.editPersonName);

        StartButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String Name = editPersonName.getText().toString();
                boolean digitsOnly = TextUtils.isDigitsOnly(Name);

                if (digitsOnly) {
                    if (Name.length() == 0) {

                        Toast.makeText(StartButton.getContext(), "Please enter your name", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(StartButton.getContext(), "Please enter a valid name", Toast.LENGTH_SHORT).show();
                    }
                } else {

                    Bundle name = new Bundle();
                    name.putString("name", Name);
                    String yourName = "";
                    if (name != null) {
                        yourName = name.getString("name");
                    }
                    name.putString("name", yourName);

                    openQuizActivity();
                    finish();
                    //https://stackoverflow.com/questions/17853360/check-entered-value-is-number-or-not
                }
            }
        });
    }

    public void openQuizActivity() {
        Intent intent = new Intent(this, QuizActivity.class);
        Bundle name = new Bundle();
        name.putString("name", editPersonName.getText().toString());
        intent.putExtra("name", editPersonName.getText().toString());
        startActivity(intent);
        //https://www.youtube.com/watch?v=bgIUdb-7Rqo
    }
}


