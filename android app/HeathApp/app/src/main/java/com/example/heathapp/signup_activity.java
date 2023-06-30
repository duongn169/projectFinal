package com.example.heathapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.material.button.MaterialButton;
import com.vishnusivadas.advanced_httpurlconnection.PutData;

public class signup_activity extends AppCompatActivity {
    EditText etPhoneNumber, etFullName, etPassword,etConfirmPassword, etGender, etAge, etAddress;
    MaterialButton btnSignup, backToLogin;

    String rIP = MainActivity.globalIPAddress;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);

        etPhoneNumber = (EditText) findViewById(R.id.phonenumber);
        etFullName = (EditText) findViewById(R.id.fullName);
        etPassword = (EditText) findViewById(R.id.sPassword);
        etConfirmPassword = (EditText) findViewById(R.id.confirmPassword);
        etGender = (EditText) findViewById(R.id.gender);
        etAge = (EditText) findViewById(R.id.age);
        etAddress = (EditText) findViewById(R.id.address);

        btnSignup = findViewById(R.id.signupbtn);
        backToLogin = findViewById(R.id.backToLogin);

        backToLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);
                finish();
            }
        });

        btnSignup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String phoneNumber, fullName, gender, age, address, password, confirmPassword;

                phoneNumber = String.valueOf(etPhoneNumber.getText());
                fullName = String.valueOf(etFullName.getText());
                gender = String.valueOf(etGender.getText());
                age = String.valueOf(etAge.getText());
                address = String.valueOf(etAddress.getText());
                password = String.valueOf(etPassword.getText());
                confirmPassword = String.valueOf(etConfirmPassword.getText());

                if(!phoneNumber.equals("") && !password.equals("") && !fullName.equals("") && !gender.equals("") && !age.equals("") && !address.equals("")&& !confirmPassword.equals("")){
                    //Start ProgressBar first (Set visibility VISIBLE)
                    if(!password.equals(confirmPassword)){
                        Toast.makeText(getApplicationContext(), "Password not matched", Toast.LENGTH_SHORT).show();
                    }
                    else{
                        Handler handler = new Handler(Looper.getMainLooper());
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                //Starting Write and Read data with URL
                                //Creating array for parameters
                                String[] field = new String[6];
                                field[0] = "phone_number";
                                field[1] = "fullname";
                                field[2] = "address";
                                field[3] = "password";
                                field[4] = "age";
                                field[5] = "gender";
                                //Creating array for data
                                String[] data = new String[6];
                                data[0] = phoneNumber;
                                data[1] = fullName;
                                data[2] = address;
                                data[3] = password;
                                data[4] = age;
                                data[5] = gender;

                                String url = "http://" + rIP + "/androidAppPHP/signup.php";
                                PutData putData = new PutData(url, "POST", field, data);

                                if (putData.startPut()) {
                                    if (putData.onComplete()) {
                                        String result = putData.getResult();
                                        String ret = "<html><body>Signup successfully</body></html>";

                                        if(result.equals(ret)){
                                            Toast.makeText(getApplicationContext(), "Signup Successful", Toast.LENGTH_SHORT).show();
                                        }
                                        else{
                                            Toast.makeText(getApplicationContext(), result, Toast.LENGTH_SHORT).show();

                                        }
                                        //End ProgressBar (Set visibility to GONE)

                                    }
                                }
                                //End Write and Read data with URL
                            }
                        });
                    }


                }
                else {
                    Toast.makeText(getApplicationContext(), "All field required!", Toast.LENGTH_SHORT).show();
                }

            }

        });
    }
}