package com.example.heathapp;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class mysqlTesting {
    public static void main(String[] args) {

        Connection conn1 = null;
        String result = " ";

        try {
            Class.forName("com.mysql.jdbc.Driver");
            String url1 = "jdbc:mysql://192.168.1.214/doctorapp";
            String user = "pi";
            String password = "27122001";

            conn1 = DriverManager.getConnection(url1, user, password);
            if (conn1 != null) {
                System.out.println("Connected to the database test1");
            }
            String sql = " select phone_number from user_information";
            PreparedStatement prest = conn1.prepareStatement(sql);
            ResultSet rs = prest.executeQuery();
            while(rs.next()) {
                result = rs.getString(1);
                System.out.println(result);

            }

        } catch (SQLException ex) {
            System.out.println("An error occurred. Maybe user/password is invalid");
            ex.printStackTrace();
        }  catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
