import numpy as np
import pandas as pd
import pickle
import mysql.connector
import sys

# Access the passed argument
variable_from_php = sys.argv[1]
user_id = variable_from_php

gender = 0
height = 0
weight = 0


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

    res = [0, 0, 0]  # );gender, 1: height, 2: weight
    # res.append(int(myresult[2]))  #age
    res[1] = int(myresult[8])
    res[2] = int(myresult[9])

    if myresult[3].upper() == "MALE":
        # res.append(1)
        res[0] = 1
    elif myresult[3].upper() == "FEMALE":
        # res.append(0)
        res[0] = 0

    return res


model = pickle.load(open('trained_modelBMI.pkl', 'rb'))


def predict():
    input_features = inputValue
    features_value = [np.array(input_features)]

    features_name = ["Gender", "Height", "Weight"]

    df = pd.DataFrame(features_value, columns=features_name)
    output = model.predict(df)

    if output == 0:
        res_val = 'Extremely Weak'
    elif output == 1:
        res_val = 'Weak'
    elif output == 2:
        res_val = 'Normal'
    elif output == 3:
        res_val = 'Overweight'
    elif output == 4:
        res_val = 'Obesity'
    elif output == 5:
        res_val = 'Extreme Obesity'
    return res_val


userInfo = getUserInfor()


inputValue = [userInfo[0],userInfo[1],userInfo[2]]
text = predict()
print(text)
