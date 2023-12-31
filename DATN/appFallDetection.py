import numpy as np
import pandas as pd
import pickle
import mysql.connector
import sys

# Access the passed argument
variable_from_php = sys.argv[1]
user_id = variable_from_php

# gender = 0
# height = 0
# weight = 0

x_pre = 0
y_pre = 0
z_pre = 0

def getUserHealth():
    mydb = mysql.connector.connect(
        host="192.168.1.214",
        user="pi",
        password="27122001",
        database="healthData"
    )

    mycursor = mydb.cursor()
    mycursor.execute(
        f"SELECT * FROM IOT_project WHERE user_id = {user_id} ORDER BY id DESC LIMIT 1")
    myresult = mycursor.fetchone()

    res = [0, 0, 0]  # );HRV, 1: SpO2, 2: Accelerometer
    res[0] = 95
    res[1] = 95
    rot_x = myresult[7]
    rot_y = myresult[8]
    rot_z = myresult[9]
    
    x = myresult[10]
    y = myresult[11]
    z = myresult[12]
    if (x < x_pre and y != y_pre and z != z_pre) and (rot_x > 2 or rot_y >2 or rot_z > 2) :
        res[2] = 1
    else:
        res[2] = 0
    x_pre = x
    y_pre = y
    z_pre = z
    return res
        
        

    
     


model = pickle.load(open('trained_modelfallDetection.pkl', 'rb'))
		

def predict():
    input_features = inputValue
    features_value = [np.array(input_features)]

    features_name = ["HRV", "SpO2", "Accelerometer"]

    df = pd.DataFrame(features_value, columns=features_name)
    output = model.predict(df)

    if output == 0:
        res_val = 'No Fall detected'
    elif output == 1:
        res_val = 'Definite fall'
    return res_val


userInfo = getUserHealth()
inputValue = [userInfo[0],userInfo[1],userInfo[2]]
text = predict()
print(inputValue)
print(text)