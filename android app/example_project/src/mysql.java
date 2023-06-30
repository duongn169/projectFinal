import java.sql.Connection;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class mysql {
    public static void main(String[] args) {
        String url = "jdbc:mysql://192.168.2.7:3306/healthData";
        String username = "pi";
        String password = "27122001";
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");

            Connection connection = DriverManager.getConnection(url, username, password);
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("select * from Patient1");


            while (resultSet.next()){
                System.out.println(resultSet.getInt(1) + " " + resultSet.getInt(2));
            }
            connection.close();
        }
        catch (Exception e){
            System.out.println(e);
        }

    }
}
