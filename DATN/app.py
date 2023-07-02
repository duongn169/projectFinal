import numpy as np
import pandas as pd
from flask import Flask, request, render_template
import pickle
import mysql.connector
import sys

# Access the passed argument
variable_from_php = sys.argv[1]
user_id = variable_from_php

age = 0
gender = 0
bpm = 0


def getUserInfor():
    mydb = mysql.connector.connect(
        host="192.168.1.214",
        user="pi",
        password="27122001",
        database="doctorapp"
    )

    mycursor = mydb.cursor()
    mycursor.execute(f"SELECT * FROM patients where id = {user_id}")
    myresult = mycursor.fetchone()

    res = [0, 0]
    # res.append(int(myresult[2]))  #age
    res[0] = int(myresult[2])

    if myresult[3].upper() == "MALE":
        # res.append(1)
        res[1] = 1
    elif myresult[3].upper() == "FEMALE":
        # res.append(0)
        res[1] = 0
    return res


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

    bpm1 = int(myresult[3])
    return bpm1


model = pickle.load(open('trained_model.pkl', 'rb'))


def predict():
    input_features = inputValue
    features_value = [np.array(input_features)]

    features_name = ["age", "sex", "cp", "trestbps",
                     "thalach",  "exang", "ca", "thal"]

    df = pd.DataFrame(features_value, columns=features_name)
    output = model.predict(df)

    if inputValue[4] > 160 and  output == 1:
        res_val = "** Heart is HIGH you should go to hospital **"
    elif inputValue[4] > 160 and  output == 0:
        res_val = "** Heart is HIGH you should relax **"
    elif inputValue[4] < 60 and  output == 1:
        res_val = "** Heart is LOW you you should go to hospital **" 
    elif inputValue[4] < 60 and  output == 0:
        res_val = "** Heart is LOW you should relax **"
    else:
        res_val = "no heart disease "

    return res_val


bpm = getUserHealth()
userInfo = getUserInfor()
age = userInfo[0]
gender = userInfo[1]

inputValue = [age, gender, 0, 0, bpm, 0, 0, 0]
text = predict()
print(inputValue)
