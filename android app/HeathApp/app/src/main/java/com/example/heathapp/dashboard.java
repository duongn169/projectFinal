package com.example.heathapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.button.MaterialButton;
import com.google.android.material.navigation.NavigationView;
import com.vishnusivadas.advanced_httpurlconnection.PutData;

import javax.net.ssl.HandshakeCompletedListener;

public class dashboard extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private Handler handler;
    private Runnable statusUpdater;
    TextView status, hr, spo2, bodyTemp, ambTemp, humidity;


    final Context context = this;
    MaterialButton btnLogout;
    String rPhone = MainActivity.globalPhoneNumber;
    String rIP = MainActivity.globalIPAddress;


    private DrawerLayout drawer;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dashboard);


        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawer = findViewById(R.id.drawer_layout);
        NavigationView navigationView = findViewById(R.id.navigationView);
        navigationView.setNavigationItemSelectedListener((NavigationView.OnNavigationItemSelectedListener) this);


        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);

        drawer.addDrawerListener(toggle);
        toggle.syncState();



        hr = (TextView) findViewById(R.id.heartRate);
        spo2 = (TextView) findViewById(R.id.spo2);
        bodyTemp = (TextView) findViewById(R.id.BodyTemp);
        ambTemp = (TextView) findViewById(R.id.AmbTemp);
        humidity = (TextView) findViewById(R.id.humidity);

        btnLogout = findViewById(R.id.btnLogout);

        btnLogout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);
                finish();
            }
        });


        handler = new Handler();
        statusUpdater = new Runnable() {
            @Override
            public void run() {
                //updateStatus();
                //check global phoneNum

                updateHR();
                updateAmbTemp();
                updateBodyTemp();
                updateHumidity();
                updateSPO2();
                handler.postDelayed(this, 100);
            }
        };
        // Start updating the status TextView
        startStatusUpdate();

    }

    public void openDrawer(View view) {
        drawer.openDrawer(GravityCompat.START);
    }

    @Override
    public void onBackPressed() {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }


    private void startStatusUpdate() {
        handler.post(statusUpdater);
    }

    private void stopStatusUpdate() {
        handler.removeCallbacks(statusUpdater);
    }



    private void updateHR() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getHR.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                hr.setText(result);

            }
        }
    }

    private void updateSPO2() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;

        String url = "http://" + rIP + "/androidAppPHP/getSPO2.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                spo2.setText(result);
            }
        }
    }

    private void updateAmbTemp() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;

        String url = "http://" + rIP + "/androidAppPHP/getAmbTemp.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                ambTemp.setText(result);
            }
        }
    }

    private void updateBodyTemp() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;

        String url = "http://" + rIP + "/androidAppPHP/getBodyTemp.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                bodyTemp.setText(result);
            }
        }
    }

    private void updateHumidity() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;

        String url = "http://" + rIP + "/androidAppPHP/getHumidity.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                humidity.setText(result);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Stop updating the status TextView when the activity is destroyed
        stopStatusUpdate();
    }


    @SuppressLint("NonConstantResourceId")
    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        int id = item.getItemId();

        if (item.getItemId() == R.id.nav_dashboard) {
            // Handle Dashboard action
            Intent intent = new Intent(this, dashboard.class);
            startActivity(intent);
            Toast.makeText(this, "Dashboard Clicked", Toast.LENGTH_SHORT).show();
        } else if (item.getItemId() == R.id.nav_profile) {
            // Handle User Info action
            Intent intent = new Intent(this, profile.class);
            startActivity(intent);
            Toast.makeText(this, "User Info Clicked", Toast.LENGTH_SHORT).show();
        } else if (item.getItemId() == R.id.nav_send) {
            // Handle Edit User Info action
            Toast.makeText(this, "Edit User Info Clicked", Toast.LENGTH_SHORT).show();
        } else if (item.getItemId() == R.id.nav_logout) {
            // Handle Log Out action
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
            Toast.makeText(this, "Log Out Clicked", Toast.LENGTH_SHORT).show();
        }
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

}