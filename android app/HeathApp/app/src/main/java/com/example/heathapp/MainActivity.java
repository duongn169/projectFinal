package com.example.heathapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.button.MaterialButton;
import com.google.android.material.textfield.TextInputEditText;
import com.vishnusivadas.advanced_httpurlconnection.PutData;


import  java.sql.*;

public class MainActivity extends AppCompatActivity {
    EditText etPhoneNumber, etPassword, etIP;
    MaterialButton btnLogin, btnSignup;

    //Variable to share variable between file
    public static String globalPhoneNumber;
    public static String globalIPAddress;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etPhoneNumber = (EditText) findViewById(R.id.phonenumber);
        etPassword = (EditText) findViewById(R.id.password);
        etIP = (EditText) findViewById(R.id.ip);

        btnLogin = findViewById(R.id.loginbtn);
        btnSignup = findViewById(R.id.signupbtn);

        btnSignup.setOnClickListener((new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), signup_activity.class);
                startActivity(intent);
                finish();
            }
        }));

        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String phoneNumber, password;
                phoneNumber = String.valueOf(etPhoneNumber.getText());
                password = String.valueOf(etPassword.getText());
                globalPhoneNumber = phoneNumber;
                globalIPAddress = String.valueOf(etIP.getText());

                if(!phoneNumber.equals("") && !password.equals("")){
                    //Start ProgressBar first (Set visibility VISIBLE)
                    Handler handler = new Handler(Looper.getMainLooper());
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            //Starting Write and Read data with URL
                            //Creating array for parameters
                            String[] field = new String[2];
                            field[0] = "phone_number";
                            field[1] = "password";
                            //Creating array for data
                            String[] data = new String[2];
                            data[0] = phoneNumber;
                            data[1] = password;

                            String ipAddress = String.valueOf(etIP.getText()); // Replace with your desired IP address
                            String url = "http://" + ipAddress + "/androidAppPHP/login.php";
                            PutData putData = new PutData(url, "POST", field, data);

                            if (putData.startPut()) {
                                if (putData.onComplete()) {
                                    String result = putData.getResult();
                                    String ret = "<html><body>" + phoneNumber + password + "Login successfully</body></html>";
                                    if(result.equals(ret)){
                                        Toast.makeText(getApplicationContext(), "Login Successful", Toast.LENGTH_SHORT).show();
                                        Intent intent = new Intent(getApplicationContext(), dashboard.class);
                                        startActivity(intent);
                                        finish();
                                    }
                                    else{
                                        Toast.makeText(getApplicationContext(), result, Toast.LENGTH_SHORT).show();
                                    }

                                }
                            }




                        }
                    });

                }
                else {
                    Toast.makeText(getApplicationContext(), "All field required!", Toast.LENGTH_SHORT).show();
                }

            }
        });


    }


}