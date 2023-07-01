package com.example.heathapp;

import static com.example.heathapp.R.layout.user_information;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;

import com.google.android.material.navigation.NavigationView;
import com.vishnusivadas.advanced_httpurlconnection.PutData;


public class profile extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {

    private Handler handler;
    private Runnable statusUpdater;

    TextView phoneNumber, name, age, gender, address, height, weight, email, status;

    private DrawerLayout drawer;

    String rIP = MainActivity.globalIPAddress;
    String rPhone = MainActivity.globalPhoneNumber;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.user_information);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawer = findViewById(R.id.drawer_layout);
        NavigationView navigationView = findViewById(R.id.navigationView);
        navigationView.setNavigationItemSelectedListener((NavigationView.OnNavigationItemSelectedListener) this);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);

        drawer.addDrawerListener(toggle);
        toggle.syncState();


        phoneNumber = (TextView)findViewById(R.id.phonenumber);
        name = (TextView) findViewById(R.id.fullName);
        age = (TextView)  findViewById(R.id.age);
        address = (TextView) findViewById(R.id.address);
        height = (TextView) findViewById(R.id.height);
        weight = (TextView) findViewById(R.id.weight);
        email = (TextView) findViewById(R.id.email);
        gender = (TextView) findViewById(R.id.gender);



        handler = new Handler();
        statusUpdater = new Runnable() {
            @Override
            public void run() {
                updateName();
                updateAddress();
                updateAge();
                updateEmail();
                updateGender();
                updateHeight();
                updatePhone();
                updateWeight();
                handler.postDelayed(this, 100);
            }
        };

        // Start updating the status TextView
        startStatusUpdate();
    }

    private void startStatusUpdate() {
        handler.post(statusUpdater);
    }

    private void stopStatusUpdate() {
        handler.removeCallbacks(statusUpdater);
    }


    private void updateName() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getName.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                name.setText(result);

            }
        }
    }

    private void updatePhone() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getPhone.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                phoneNumber.setText(result);

            }
        }
    }

    private void updateAddress() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getAddress.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                address.setText(result);

            }
        }
    }
    private void updateAge() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getAge.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                age.setText(result);

            }
        }
    }

    private void updateGender() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getGender.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                gender.setText(result);

            }
        }
    }

    private void updateHeight() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getHeight.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                height.setText(result);

            }
        }
    }

    private void updateWeight() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getWeight.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                weight.setText(result);

            }
        }
    }

    private void updateEmail() {
        // Place your code here to update the status TextView
        // For example, you can modify the existing code to update the status text

        String[] field = new String[1];
        field[0] = "phone_number";


        String[] data = new String[1];
        data[0] = rPhone;


        String url = "http://" + rIP + "/androidAppPHP/getUSerInfor/getEmail.php";
        PutData putData = new PutData(url, "POST", field, data);
        if (putData.startPut()) {
            if (putData.onComplete()) {
                String result = putData.getResult();
                email.setText(result);

            }
        }
    }


    @Override
    public void onBackPressed() {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
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
